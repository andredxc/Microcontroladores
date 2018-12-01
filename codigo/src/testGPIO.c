#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libgalileo2.h"

int main(){

    // IO2
    if(pputs("/sys/class/gpio/gpio13/value", "1") < 0){
        fprintf(stderr, "Error setting IO02\n");
    }
    // IO4
    if(pputs("/sys/class/gpio/gpio6/value", "1") < 0){
        fprintf(stderr, "Error setting IO04\n");
    }
    // IO7
    if(pputs("/sys/class/gpio/gpio38/value", "1") < 0){
        fprintf(stderr, "Error setting IO07\n");
    }

    return 0;
}
