#include "api.h"

int main(){

    float motorVoltage;
    int done;

    if(init() < 0){
        fprintf(stderr, "%s - Couldn't initialize api\n", __FUNCTION__);
        return -1;
    }

    done = 0;
    while(!done){

        fprintf(stderr, "Motor voltage: ");
        scanf("%f", &motorVoltage);
        if(setMotorVoltage(motorVoltage) < 0){
            fprintf(stderr, "Error calling setMotorVoltage\n");
            done = 1;
        }

        if(readElbow1()){
            fprintf(stderr, "ELB1 is high\n");
        }

        if(readElbow2()){
            fprintf(stderr, "ELB2 is high\n");
        }

        fprintf(stderr, "Current pos: %.2f\n", readEncoders());
    }

    finish();
    return 1;
}
