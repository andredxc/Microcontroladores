#ifndef LIBGALILEO2_H
#define LIBGALILEO2_H

#ifdef __cplusplus
extern "C"
{
#endif

    extern int pputs(const char *path, const char *string);
    extern char* pgets(char* string, int size, const char* path);
    extern double readAdcVoltage(int adcNum);
    extern int setServoAngle(int pwmNum, int degAngle);

#ifdef __cplusplus
};
#endif

#endif
