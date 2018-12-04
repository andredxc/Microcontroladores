#ifndef LIBGALILEO2_H
#define LIBGALILEO2_H

#ifdef __cplusplus
extern "C"
{
#endif

    extern int pputs(const char *path, const char *string);
    extern char* pgets(char* string, int size, const char* path);
    extern double readAdcVoltage(int adcNum);
    extern int setServoAngle(int fd_duty_cycle, int fd_period, int degAngle);
    extern int i2c_write_reg(int fd, unsigned char reg, unsigned char data);
    extern int initLCD();
    extern int setLCDBacklight(int fd, int red, int green, int blue);
    extern int writeLCD(int fd, int line, const char* string, int length);
    extern int readButton(int fd);

#ifdef __cplusplus
};
#endif

#endif
