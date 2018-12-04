#include "api.h"

// IO 00 gpio11 as input(LFLAG_1)
// IO 01 gpio12 as input (DFLAG_1)
// IO 02 gpio13 as output (INDEX_1)
// IO 03 pwm1 as output (MOTOR)
// IO 04 gpio6 as output(EN_1)
// IO 05 gpio0 as input (ELB1)
// IO 06 gpio1 as input (ELB2)
// IO 07 gpio38 as output (ENABLE)
// IO 10 gpio10 as output (SS)
// IO 11 (MOSI)
// IO 12 (MISO)
// IO 13 (SCK)

// Inputs
# define LFLAG "/sys/class/gpio/gpio11/value"
# define DFLAG "/sys/class/gpio/gpio12/value"
# define ELB1 "/sys/class/gpio/gpio0/value"
# define ELB2 "/sys/class/gpio/gpio1/value"
// Outputs
# define INDEX "/sys/class/gpio/gpio13/value"
# define EN "/sys/class/gpio/gpio6/value"
# define ENABLE "/sys/class/gpio/gpio38/value"
// PWM
#define PWM_DUTYCYCLE "/sys/class/pwm/pwmchip0/pwm1/duty_cycle"
#define PWM_ENABLE "/sys/class/pwm/pwmchip0/pwm1/enable"
#define PWM_PERIOD "/sys/class/pwm/pwmchip0/device/pwm_period"

// Contains file descriptors for the pins used in the project
typedef struct fds{
    // Inputs
    int lflag, dflag, elb1, elb2;
    // Outputs
    int index, en, enable;
    // PWM
    int pwmDutyCycle, pwmEnable, pwmPeriod;
} FDS;

FDS _fd;

// -----------------------------------------------------------------------------
int init(){

    // LFLAG
    if((_fd.lflag = open(LFLAG, O_RDONLY)) < 0){
        fprintf(stderr, "%s - Error opening %s\n", __FUNCTION__, LFLAG);
        finish(); return -1;
    }
    // DFLAG
    if((_fd.dflag = open(DFLAG, O_RDONLY)) < 0){
        fprintf(stderr, "%s - Error opening %s\n", __FUNCTION__, DFLAG);
        finish(); return -1;
    }
    // ELB1
    if((_fd.elb1 = open(ELB1, O_RDONLY)) < 0){
        fprintf(stderr, "%s - Error opening %s\n", __FUNCTION__, ELB1);
        finish(); return -1;
    }
    // ELB2
    if((_fd.elb2 = open(ELB2, O_RDONLY)) < 0){
        fprintf(stderr, "%s - Error opening %s\n", __FUNCTION__, ELB2);
        finish(); return -1;
    }
    // INDEX
    if((_fd.index = open(INDEX, O_WRONLY)) < 0){
        fprintf(stderr, "%s - Error opening %s\n", __FUNCTION__, INDEX);
        finish(); return -1;
    }
    // EN
    if((_fd.en = open(EN, O_WRONLY)) < 0){
        fprintf(stderr, "%s - Error opening %s\n", __FUNCTION__, EN);
        finish(); return -1;
    }
    // ENABLE
    if((_fd.enable = open(ENABLE, O_WRONLY)) < 0){
        fprintf(stderr, "%s - Error opening %s\n", __FUNCTION__, ENABLE);
        finish(); return -1;
    }
    // PWM_DUTYCYCLE
    if((_fd.pwmDutyCycle = open(PWM_DUTYCYCLE, O_WRONLY)) < 0){
        fprintf(stderr, "%s - Error opening %s\n", __FUNCTION__, PWM_DUTYCYCLE);
        finish(); return -1;
    }
    // PWM_PERIOD
    if((_fd.pwmPeriod = open(PWM_PERIOD, O_WRONLY)) < 0){
        fprintf(stderr, "%s - Error opening %s\n", __FUNCTION__, PWM_PERIOD);
        finish(); return -1;
    }
    // PWM_ENABLE
    if((_fd.pwmEnable = open(PWM_ENABLE, O_WRONLY)) < 0){
        fprintf(stderr, "%s - Error opening %s\n", __FUNCTION__, PWM_ENABLE);
        finish(); return -1;
    }

    return 1;
}

// -----------------------------------------------------------------------------
void finish(){
    close(_fd.lflag);
    close(_fd.dflag);
    close(_fd.elb1);
    close(_fd.elb2);
    close(_fd.index);
    close(_fd.en);
    close(_fd.enable);
    close(_fd.pwmDutyCycle);
    close(_fd.pwmPeriod);
    close(_fd.pwmEnable);
}

// -----------------------------------------------------------------------------
void testPins(int numIterations, int interval){

    int count, pwmPeriod;

    pwmPeriod = 1000000;


    if(writeGPIO(_fd.pwmPeriod, pwmPeriod) < 0){
        fprintf(stderr, "%s - Error writing to pwmPeriod\n", __FUNCTION__);
    }
    if(writeGPIO(_fd.pwmEnable, 1) < 0){
        fprintf(stderr, "%s - Error writing to pwmEnable\n", __FUNCTION__);
    }

    count = 0;
    while(count < numIterations){

        fprintf(stderr, ".");
        // LFLAG
        if(readGPIO(_fd.lflag)){
            fprintf(stderr, "%s - LFLAG activated\n", __FUNCTION__);
        }
        // DFLAG
        if(readGPIO(_fd.dflag)){
            fprintf(stderr, "%s - DFLAG activated\n", __FUNCTION__);
        }
        // ELB1
        if(readGPIO(_fd.elb1)){
            fprintf(stderr, "%s - ELB1 activated\n", __FUNCTION__);
        }
        // ELB2
        if(readGPIO(_fd.elb2)){
            fprintf(stderr, "%s - ELB2 activated\n", __FUNCTION__);
        }
        // Outputs --------------------------------------------------------
        // INDEX
        if(writeGPIO(_fd.index, count%2) < 0){
            fprintf(stderr, "%s - Error writing to INDEX\n", __FUNCTION__);
        }
        // ENABLE
        if(writeGPIO(_fd.enable, count%2) < 0){
            fprintf(stderr, "%s - Error writing to ENABLE\n", __FUNCTION__);
        }
        // EN
        if(writeGPIO(_fd.en, count%2) < 0){
            fprintf(stderr, "%s - Error writing to EN\n", __FUNCTION__);
        }

        // PWM ------------------------------------------------------------
        if(writeGPIO(_fd.pwmDutyCycle, (int)((count%101)/100.0 * (float)pwmPeriod)) < 0){
            fprintf(stderr, "%s - Error writing to pwmDutyCycle\n", __FUNCTION__);
        }

        usleep(1000*interval);
        count++;
    }

    writeGPIO(_fd.pwmEnable, 0);
    writeGPIO(_fd.index, 0);
    writeGPIO(_fd.enable, 0);
    writeGPIO(_fd.en, 0);
}

// -----------------------------------------------------------------------------
int readGPIO(int fd){

    char buffer[10];

    lseek(fd, 0, SEEK_SET);
    if(read(fd, buffer, sizeof(buffer)) < 0){
        fprintf(stderr, "%s - Error reading from file\n", __FUNCTION__);
        return -1;
    }

    return atoi(buffer);
}

// -----------------------------------------------------------------------------
int writeGPIO(int fd, int data){

    int bytesWritten;
    char buffer[30];

    snprintf(buffer, sizeof(buffer), "%d", data);

    lseek(fd, 0, SEEK_SET);
    if((bytesWritten = write(fd, buffer, strlen(buffer))) < 0){
        fprintf(stderr, "%s - Error writing to file\n", __FUNCTION__);
        return -1;
    }

    return bytesWritten;
}
