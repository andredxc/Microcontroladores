#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libgalileo2.h"

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


int main(){

    int done, count;
    char buffer[30], outBuffer[10] = {"1"};

    pputs(PWM_PERIOD, "1000000");
    pputs(PWM_ENABLE, "1");

    done = 0;
    count = 0;
    while(!done){

        fprintf(stderr, ".\n");
        // Inputs ---------------------------------------------------------
        // LFLAG
        if(pgets(buffer, sizeof(buffer), LFLAG) < 0){
            fprintf(stderr, "Error reading %s\n", LFLAG);
        }
        if(atoi(buffer) == 1){
            fprintf(stderr, "LFLAG (IO 00) high\n");
        }
        // DFLAG
        if(pgets(buffer, sizeof(buffer), DFLAG) < 0){
            fprintf(stderr, "Error reading %s\n", DFLAG);
        }
        if(atoi(buffer) == 1){
            fprintf(stderr, "DFLAG (IO 01) high\n");
        }
        // ELB1
        if(pgets(buffer, sizeof(buffer), ELB1) < 0){
            fprintf(stderr, "Error reading %s\n", ELB1);
        }
        if(atoi(buffer) == 1){
            fprintf(stderr, "ELB1 (IO 05) high\n");
        }
        // ELB2
        if(pgets(buffer, sizeof(buffer), ELB2) < 0){
            fprintf(stderr, "Error reading %s\n", ELB2);
        }
        if(atoi(buffer) == 1){
            fprintf(stderr, "ELB2 (IO 06) high\n");
        }

        // Outputs ---------------------------------------------------------
        // INDEX
        if(pputs(INDEX, outBuffer) < 0){
            fprintf(stderr, "Error writing to %s\n", INDEX);
        }
        // ENABLE
        if(pputs(ENABLE, outBuffer) < 0){
            fprintf(stderr, "Error writing to %s\n", ENABLE);
        }
        // EN
        if(pputs(EN, outBuffer) < 0){
            fprintf(stderr, "Error writing to %s\n", EN);
        }

        // PWM ------------------------------------------------------------
        snprintf(buffer, sizeof(buffer), "%d\n", (int)(count/100.0 * 1000000.0));
        pputs(PWM_DUTYCYCLE, buffer);

        if(count >= 100){
            count = 0;
        }
        else{
            count += 5;
        }

        if(outBuffer[0] == '1'){
            outBuffer[0] = '0';
        }
        else{
            outBuffer[0] = '1';
        }

        usleep(500000);
    }

    return 1;

    /*
    int elb1_fd, elb2_fd;
    char elb1_buffer[10], elb2_buffer[10];

    // Elbow sensors
    elb1_fd = open(ELB1_VALUE, O_RDONLY);
    if(elb1_fd < 0){
        fprintf(stderr, "Error opening %s\n", ELB1_VALUE);
        close(elb1_fd);
        close(elb2_fd);
        return -1;
    }
    elb2_fd = open(ELB2_VALUE, O_RDONLY);
    if(elb2_fd < 0){
        fprintf(stderr, "Error opening %s\n", ELB2_VALUE);
        close(elb1_fd);
        close(elb2_fd);
        return -1;
    }

    // Read initial values from elbow sensors
    if(read(elb1_fd, elb1_buffer, sizeof(elb1_buffer)) < 0){
        fprintf(stderr, "Error reading from elb1_fd\n");
        close(elb1_fd);
        close(elb2_fd);
        return -1;
    }
    if(read(elb2_fd, elb2_buffer, sizeof(elb2_buffer))){
        fprintf(stderr, "Error reading from elb2_fd\n");
        close(elb1_fd);
        close(elb2_fd);
        return -1;
    }

    while(atoi(elb1_buffer) == 0 && atoi(elb2_buffer) == 0){
        // Arm has not reached end of course





        if(read(elb1_fd, elb1_buffer, sizeof(elb1_buffer)) < 0){
            fprintf(stderr, "Error reading from elb1_fd\n");
            close(elb1_fd);
            close(elb2_fd);
            return -1;
        }
        if(read(elb2_fd, elb2_buffer, sizeof(elb2_buffer))){
            fprintf(stderr, "Error reading from elb2_fd\n");
            close(elb1_fd);
            close(elb2_fd);
            return -1;
        }
        usleep(1000);
    }





    close(elb1_fd);
    close(elb2_fd);
    return 0;
    */
}
