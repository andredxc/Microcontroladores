#ifndef API_H
#define API_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#ifdef __cplusplus
extern "C"
{
#endif

    extern int init();
    extern void finish();
    extern void testPins(int numIterations, int interval);
    extern int readGPIO(int fd);
    extern int writeGPIO(int fd, int data);

#ifdef __cplusplus
};
#endif
#endif
