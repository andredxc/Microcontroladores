#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <linux/i2c-dev.h>
#include <i2cutil.h>
#include <jhdlcd.h>
#include <libgalileo2.h>
#include <errno.h>
#include <sys/ioctl.h>

// -----------------------------------------------------------------------------
char* pgets(char* string, int size, const char* path){

    int fd;

    fd = open(path, O_RDONLY);

    if(fd < 0){
        return NULL;
    }

    if(read(fd, string, size) < 0) {
        return NULL;
    }

    close(fd);
    return string;
}

// -----------------------------------------------------------------------------
int pputs(const char *path, const char *string){

    int fd;
    int n;

    fd = open(path, O_WRONLY);

    if(fd < 0){
        return -1;
    }

    n = write(fd, string, strlen(string));
    close(fd);
    return n;
}

// -----------------------------------------------------------------------------
double readAdcVoltage(int adcNum){

    /*
        NÃO FUNCIONA DIREITO
        A tensão lida fica constante depois de alguns segundos.
        Acho que por causa das constantes aberturas e fechamento dos arquivos do ADC
    */

    int fdVoltage;
    char buffer[20], adcVoltagePath[150], adcScalePath[150];
    double scale;

    snprintf(adcVoltagePath, sizeof(adcVoltagePath), "/sys/bus/iio/devices/iio:device%d/in_voltage%d_raw", adcNum, adcNum);
    snprintf(adcScalePath, sizeof(adcScalePath), "/sys/bus/iio/devices/iio:device%d/in_voltage%d_scale", adcNum, adcNum);

    fdVoltage = open(adcVoltagePath, O_RDONLY);

    if(fdVoltage < 0){
        printf("Error reading file %s\n", adcVoltagePath);
        return -1;
    }

    pgets(buffer, sizeof(buffer), adcScalePath);
    scale = atof(buffer)/1000.0;     // Scale used to convert voltage value to Volts
    lseek(fdVoltage, 0, SEEK_SET);
    read(fdVoltage, buffer, sizeof(buffer));

    close(fdVoltage);
    return scale*atof(buffer);
}

// -----------------------------------------------------------------------------
int setServoAngle(int fd_duty_cycle, int fd_period, int degAngle){

    // degAngle = angle in degrees between -90 and +90

    int duty_cycle;
    double radAngle;
    char buffer[100];

    // Period -> "/sys/class/pwm/pwmchip0/device/pwm_period"
    // Duty cycle -> "/sys/class/pwm/pwmchip0/pwm%d/duty_cycle"
    // Enable -> "/sys/class/pwm/pwmchip0/pwm%d/enable"

    radAngle = (float) degAngle * M_PI/180.0;

    if((radAngle > M_PI_2) || (radAngle < - M_PI_2))
    {
        fprintf(stderr, "%s - Angle %d is out of range\n", __FUNCTION__, degAngle);
        return -1;
    }

    duty_cycle = (radAngle/M_PI_2)*850000 + 1500000;

    snprintf(buffer, sizeof(buffer), "20000000");
    if(write(fd_period, buffer, strlen(buffer)) < 0){
        fprintf(stderr, "%s - Error writing period\n", __FUNCTION__);
        return -1;
    }

    snprintf(buffer, sizeof(buffer), "%d\n", duty_cycle);
    if(write(fd_duty_cycle, buffer, strlen(buffer)) < 0){
        fprintf(stderr, "%s - Error writing duty_cycle\n", __FUNCTION__);
        return -1;
    }

    return 1;
}

// -----------------------------------------------------------------------------
int i2c_write_reg(int fd, unsigned char reg, unsigned char data){

    unsigned char buf[] = {reg, data};

    return write(fd, buf, sizeof(buf));
}

// -----------------------------------------------------------------------------
int initLCD(){

    int fd;

    if((fd = open("/dev/i2c-0", O_WRONLY)) < 0) {
        fprintf(stderr, "%s - Error opening /dev/i2c-0\n", __FUNCTION__);
        return -1;
    }
    usleep(30000);	/* Wait for 30 ms after power on */

    /* LCD initialization */
    if(ioctl(fd,I2C_SLAVE,LCD_ADDR) < 0) {
        fprintf(stderr, "%s - Error on ioctl\n", __FUNCTION__);
        return -2;
    }

    i2c_write_reg(fd, LCD_C0, LCD_FUNCTIONSET | LCD_2LINE);
    usleep(40);  /* Wait for more than 39 us */

    i2c_write_reg(fd, LCD_C0, LCD_DISPLAYSWITCH | LCD_DISPLAYON |
            LCD_CURSOROFF | LCD_BLINKOFF);
    usleep(40);	/* Wait for more then 39 us */

    i2c_write_reg(fd, LCD_C0, LCD_SCREENCLEAR);
    usleep(1600);	/* Wait for more then 1.53 ms */

    i2c_write_reg(fd, LCD_C0, LCD_INPUTSET | LCD_ENTRYLEFT | LCD_DECREMENT);

    /* Backlight initialization */
    if(ioctl(fd, I2C_SLAVE, BL_ADDR) < 0){
        fprintf(stderr, "%s - Error on ioctl for backlight initialization\n", __FUNCTION__);
        return -3;
    }

    i2c_write_reg(fd, BL_MODE1, 0);
    i2c_write_reg(fd, BL_LEDOUT, BL_RED_GRPPWM | BL_GREEN_GRPPWM |
            BL_BLUE_GRPPWM);
    i2c_write_reg(fd, BL_MODE2, BL_DMBLNK);

    i2c_write_reg(fd, BL_RED, 0);
    i2c_write_reg(fd, BL_GREEN, 0);
    i2c_write_reg(fd, BL_BLUE, 0);

    return fd;
}

// -----------------------------------------------------------------------------
int setLCDBacklight(int fd, int red, int green, int blue){

    if(ioctl(fd,I2C_SLAVE,BL_ADDR) < 0){
        fprintf(stderr, "%s - Error on ioctl for backlight initialization\n", __FUNCTION__);
        return -1;
    }

    i2c_write_reg(fd, BL_MODE1, 0);
    i2c_write_reg(fd, BL_LEDOUT, BL_RED_GRPPWM | BL_GREEN_GRPPWM | BL_BLUE_GRPPWM);
    i2c_write_reg(fd, BL_MODE2, BL_DMBLNK);

    i2c_write_reg(fd, BL_RED, red);
    i2c_write_reg(fd, BL_GREEN, green);
    i2c_write_reg(fd, BL_BLUE, blue);

    return 1;
}

// -----------------------------------------------------------------------------
int writeLCD(int fd, int line, const char* string, int length){

    int i;

    if(ioctl(fd, I2C_SLAVE, LCD_ADDR) < 0) {
        fprintf(stderr, "%s - Erro on ioctl\n", __FUNCTION__);
        return -1;
    }

    if(line == 1){
        i2c_write_reg(fd, LCD_C0, LCD_DDRAMADDRSET | 0);
    }
    else if(line == 2){
        i2c_write_reg(fd, LCD_C0, LCD_DDRAMADDRSET | 0x40);
    }
    else{
        fprintf(stderr, "%s - Line must be 1 or 2\n", __FUNCTION__);
    }

    for(i = 0; i < length; i++){
        i2c_write_reg(fd, LCD_RS, string[i]);
    }

    return 1;
}

//------------------------------------------------------------------------------
int readButton(int fd){

    char buffer[10];

    lseek(fd, 0, SEEK_SET);
    if(read(fd, buffer, sizeof(buffer)) < 0){
        fprintf(stderr, "%s - Error reading button\n", __FUNCTION__);
        return -1;
    }

    return atoi(buffer);
}
