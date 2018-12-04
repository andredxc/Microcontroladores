#include "api.h"

int main(){

    if(init() < 0){
        fprintf(stderr, "%s - Couldn't initialize api\n", __FUNCTION__);
        return -1;
    }

    testPins(1000, 10);

    finish();

    return 1;
}
