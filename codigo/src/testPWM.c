#include "api.h"

int main(){

    float pwmValue;

    if(init() < 0){
        fprintf(stderr, "%s - Couldn't initialize api\n", __FUNCTION__);
        return -1;
    }

    pwmValue = 0;
    while(setPWM(pwmValue) >= 0){

        fprintf(stderr, "PWM intensity: ");
        scanf("%f", &pwmValue);
        fprintf(stderr, "Value: %f\n", pwmValue);
    }

    finish();
    return 1;
}
