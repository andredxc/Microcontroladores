#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libgalileo2.h"

#define PWM_LED_DUTYCYCLE "/sys/class/pwm/pwmchip0/pwm1/duty_cycle"
// #define PWM_LED_DUTYCYCLE "/dev/stdout"
#define PWM_LED_ENABLE "/sys/class/pwm/pwmchip0/pwm1/enable"
#define PWM_PERIOD "/sys/class/pwm/pwmchip0/device/pwm_period"

int main(){

    int count;
    char buffer[20];

    // 1KHz -> 1ms -> 1*10^6 ns -> 1000000 ns
    pputs(PWM_PERIOD, "1000000");
    pputs(PWM_LED_ENABLE, "1");

    count = 0;
    while(1){

        snprintf(buffer, sizeof(buffer), "%d\n", (int)(count/100.0 * 1000000.0));
        pputs(PWM_LED_DUTYCYCLE, buffer);

        if(count == 100){
            count = 0;
        }
        else{
            count++;
        }
        usleep(70000);
    }

    pputs(PWM_LED_ENABLE, "0");
    return 0;
}
