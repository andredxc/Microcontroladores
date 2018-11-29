#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libgalileo2.h"

int main(){

    pputs("/sys/class/gpio/gpio13", "1");
    pputs("/sys/class/gpio/gpio6", "1");
    pputs("/sys/class/gpio/gpio38", "1");

    return 0;
}
