#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <libgalileo2.h>

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
int setServoAngle(int pwmNum, int degAngle){

    int duty_cycle;
    double radAngle;
    char str[100], pwmPeriodPath[150], pwmDutyCyclePath[150], pwmEnablePath[150];

    snprintf(pwmPeriodPath, sizeof(pwmPeriodPath), "/sys/class/pwm/pwmchip0/device/pwm_period");
    snprintf(pwmDutyCyclePath, sizeof(pwmDutyCyclePath), "/sys/class/pwm/pwmchip0/pwm%d/duty_cycle", pwmNum);
    snprintf(pwmEnablePath, sizeof(pwmEnablePath), "/sys/class/pwm/pwmchip0/pwm%d/enable", pwmNum);

    radAngle = (float) degAngle * M_PI/180.0;

    if((radAngle > M_PI_2) || (radAngle < - M_PI_2))
    {
            fprintf(stderr, "%s - Angle %d is out of range\n", __FUNCTION__, degAngle);
            return -1;
    }

    duty_cycle = (radAngle/M_PI_2)*850000 + 1500000;

    pputs(pwmPeriodPath,"20000000");

    snprintf(str,sizeof str,"%d\n",duty_cycle);
    pputs(pwmDutyCyclePath,str);
    pputs(pwmEnablePath,"1");
    return 1;
}
