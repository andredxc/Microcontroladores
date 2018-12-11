#include "api.h"

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

FDS _fd;

// -----------------------------------------------------------------------------
int setMotorVoltage(double volts){

    double dutyCycle;

    if(volts > 27 || volts < -27){
        fprintf(stderr, "%s - Error, motor voltage must be between -27 and 27\n", __FUNCTION__);
        return -2;
    }

    dutyCycle = (volts + 27) / 54;
    return setPWM(dutyCycle);
}

// -----------------------------------------------------------------------------
float readEncoders(){

    /*
        A Galileo Gen 2 foi configurada para gerenciar o sinal #SS de tal forma:

        Adicionando o parâmetro: "intel_qrk_plat_galileo_gen2.gpio_cs=1" na
        linha que começa com a palavra kernel no arquivo
        "/media/card/boot/grub/grub.conf"
    */

	uint32_t buf_read_32;
	uint32_t buf_write_32;

	struct spi_ioc_transfer buf_spi;

    // MDR0 Division factor =  1 / Asynchronous Index / Free Running Count Mode / x1 Quadrature Count Mode

    // Configura MDR0
    buf_write_32 = 0x88030000;
    write(_fd.spi, &buf_write_32, sizeof(buf_write_32));

    // Configura MDR1
    buf_write_32 = 0x90010000;
    write(_fd.spi, &buf_write_32, sizeof(buf_write_32));

    // Zera bufer de leitura
    buf_read_32 = 0x00000000;

    // Configura a struct
    buf_spi.tx_buf = buf_write_32;
    buf_spi.rx_buf = buf_read_32;
    buf_spi.len = sizeof(buf_write_32);
    buf_spi.speed_hz = 200;
    buf_spi.delay_usecs = 1000;
    buf_spi.bits_per_word = 32;
    buf_spi.cs_change =0;

     // OTR = CNTR
    buf_write_32 = 0xE8000000;

    ioctl(_fd.spi, SPI_IOC_MESSAGE(1), &buf_spi);

    buf_write_32 = 0x68000000;

    ioctl(_fd.spi, SPI_IOC_MESSAGE(1), &buf_spi);

    return (double)((buf_read_32%0x1000000)*M_PI)/13824;
}

// -----------------------------------------------------------------------------
int readElbow1(){

    return readGPIO(_fd.elb1);
}

// -----------------------------------------------------------------------------
int readElbow2(){
    return readGPIO(_fd.elb2);
}

// -----------------------------------------------------------------------------
double PID(double endPos, double curPos){

    static double oldError = 0;
	static double integral = 0;
	double error, derivative;
    double dt, KP, KI, KD;

    // Determina constantes
    KP = 0.1;
    KI = 0.005;
    KD = 0.01;
    dt = 0.01; // 100ms

    // Realiza o cálculo
	error = endPos - curPos;
	integral = integral + (error * dt);
	derivative = (error - oldError)/dt;
    oldError = error;

	return (KP * error) + (KI * integral)+ (KD * derivative);
}

// -----------------------------------------------------------------------------
void clear_counter(){

    uint32_t buf_escrita_32;

	buf_escrita_32 = 0x20000000;
	write(_fd.spi, &buf_escrita_32, sizeof(buf_escrita_32));
}

// -----------------------------------------------------------------------------
int init(){

    // LFLAG
    if((_fd.lflag = open(LFLAG, O_RDONLY)) < 0){
        fprintf(stderr, "%s - Error opening %s\n", __FUNCTION__, LFLAG);
        finish(); return -1;
    }
    // DFLAG
    if((_fd.dflag = open(DFLAG, O_RDONLY)) < 0){
        fprintf(stderr, "%s - Error opening %s\n", __FUNCTION__, DFLAG);
        finish(); return -1;
    }
    // ELB1
    if((_fd.elb1 = open(ELB1, O_RDONLY)) < 0){
        fprintf(stderr, "%s - Error opening %s\n", __FUNCTION__, ELB1);
        finish(); return -1;
    }
    // ELB2
    if((_fd.elb2 = open(ELB2, O_RDONLY)) < 0){
        fprintf(stderr, "%s - Error opening %s\n", __FUNCTION__, ELB2);
        finish(); return -1;
    }
    // INDEX
    if((_fd.index = open(INDEX, O_WRONLY)) < 0){
        fprintf(stderr, "%s - Error opening %s\n", __FUNCTION__, INDEX);
        finish(); return -1;
    }
    // EN
    if((_fd.en = open(EN, O_WRONLY)) < 0){
        fprintf(stderr, "%s - Error opening %s\n", __FUNCTION__, EN);
        finish(); return -1;
    }
    // ENABLE
    if((_fd.enable = open(ENABLE, O_WRONLY)) < 0){
        fprintf(stderr, "%s - Error opening %s\n", __FUNCTION__, ENABLE);
        finish(); return -1;
    }
    // PWM_DUTYCYCLE
    if((_fd.pwmDutyCycle = open(PWM_DUTYCYCLE, O_WRONLY)) < 0){
        fprintf(stderr, "%s - Error opening %s\n", __FUNCTION__, PWM_DUTYCYCLE);
        finish(); return -1;
    }
    // PWM_PERIOD
    if((_fd.pwmPeriod = open(PWM_PERIOD, O_RDWR)) < 0){
        fprintf(stderr, "%s - Error opening %s\n", __FUNCTION__, PWM_PERIOD);
        finish(); return -1;
    }
    // PWM_ENABLE
    if((_fd.pwmEnable = open(PWM_ENABLE, O_WRONLY)) < 0){
        fprintf(stderr, "%s - Error opening %s\n", __FUNCTION__, PWM_ENABLE);
        finish(); return -1;
    }
    // SPI
    if(init_spi() < 0){
        fprintf(stderr, "%s Error initializing SPI\n", __FUNCTION__);
        finish(); return -1;
    }

    return 1;
}

// -----------------------------------------------------------------------------
int init_spi(){

	uint8_t mode = SPI_MODE_0;		// CPOL = 0 e CPHA = 0
	uint8_t lsb = 0;				// Configurado para MSB First
	uint8_t bpw= 32;					// Bit per word = 32
	uint32_t rate= 200;			// Taxa máxima de Transferência

	char name[50];
	strcpy(name,"/dev/spidev1.0");

	// Abre o pseudo arquivo
	if((_fd.spi = open(name, O_RDWR))==-1)
	{
		perror("Can't open device");
		return -1;
	}
	// Mode = 0
	if(ioctl(_fd.spi, SPI_IOC_WR_MODE, &mode))
	{
		perror("Can't write clock mode");
		return -1;
	}
	// MSB First
	if(ioctl(_fd.spi, SPI_IOC_WR_LSB_FIRST, &lsb))
	{
		perror("Can't read LSB mode");
		return -1;
	}
	if(ioctl(_fd.spi, SPI_IOC_WR_BITS_PER_WORD, &bpw))
	{
		perror("Can't read bits per word");
		return -1;
	}
	// Máxima taxa de transferência
	if(ioctl(_fd.spi, SPI_IOC_WR_MAX_SPEED_HZ, &rate))
	{
		perror("Can't read maximal rate");
		return -1;
	}

	return 1;
}

// -----------------------------------------------------------------------------
void finish(){

    writeGPIO(_fd.pwmEnable, 0);
    close(_fd.lflag);
    close(_fd.dflag);
    close(_fd.elb1);
    close(_fd.elb2);
    close(_fd.index);
    close(_fd.en);
    close(_fd.enable);
    close(_fd.pwmDutyCycle);
    close(_fd.pwmPeriod);
    close(_fd.pwmEnable);
    close(_fd.spi);
}

// -----------------------------------------------------------------------------
void testPins(int numIterations, int interval){

    int count, pwmPeriod;

    pwmPeriod = 1000000;


    if(writeGPIO(_fd.pwmPeriod, pwmPeriod) < 0){
        fprintf(stderr, "%s - Error writing to pwmPeriod\n", __FUNCTION__);
    }
    if(writeGPIO(_fd.pwmEnable, 1) < 0){
        fprintf(stderr, "%s - Error writing to pwmEnable\n", __FUNCTION__);
    }

    count = 0;
    while(count < numIterations){

        fprintf(stderr, ".");
        // LFLAG
        if(readGPIO(_fd.lflag)){
            fprintf(stderr, "%s - LFLAG activated\n", __FUNCTION__);
        }
        // DFLAG
        if(readGPIO(_fd.dflag)){
            fprintf(stderr, "%s - DFLAG activated\n", __FUNCTION__);
        }
        // ELB1
        if(readGPIO(_fd.elb1)){
            fprintf(stderr, "%s - ELB1 activated\n", __FUNCTION__);
        }
        // ELB2
        if(readGPIO(_fd.elb2)){
            fprintf(stderr, "%s - ELB2 activated\n", __FUNCTION__);
        }
        // Outputs --------------------------------------------------------
        // INDEX
        if(writeGPIO(_fd.index, count%2) < 0){
            fprintf(stderr, "%s - Error writing to INDEX\n", __FUNCTION__);
        }
        // ENABLE
        if(writeGPIO(_fd.enable, count%2) < 0){
            fprintf(stderr, "%s - Error writing to ENABLE\n", __FUNCTION__);
        }
        // EN
        if(writeGPIO(_fd.en, count%2) < 0){
            fprintf(stderr, "%s - Error writing to EN\n", __FUNCTION__);
        }

        // PWM ------------------------------------------------------------
        if(writeGPIO(_fd.pwmDutyCycle, (int)((count%101)/100.0 * (float)pwmPeriod)) < 0){
            fprintf(stderr, "%s - Error writing to pwmDutyCycle\n", __FUNCTION__);
        }

        usleep(1000*interval);
        count++;
    }

    writeGPIO(_fd.pwmEnable, 0);
    writeGPIO(_fd.index, 0);
    writeGPIO(_fd.enable, 0);
    writeGPIO(_fd.en, 0);
}

// -----------------------------------------------------------------------------
int readGPIO(int fd){

    char buffer[20];

    lseek(fd, 0, SEEK_SET);
    if(read(fd, buffer, sizeof(buffer)) < 0){
        fprintf(stderr, "%s - Error reading from file\n", __FUNCTION__);
        return -1;
    }

    return atoi(buffer);
}

// -----------------------------------------------------------------------------
int writeGPIO(int fd, int data){

    int bytesWritten;
    char buffer[30];

    snprintf(buffer, sizeof(buffer), "%d", data);

    lseek(fd, 0, SEEK_SET);
    if((bytesWritten = write(fd, buffer, strlen(buffer))) < 0){
        fprintf(stderr, "%s - Error writing to file\n", __FUNCTION__);
        return -1;
    }

    return bytesWritten;
}

// -----------------------------------------------------------------------------
int setPWM(double value){

    int dutyCycle, period;

    if(value < 0 || value > 100.0){
        fprintf(stderr, "%s - Value must be between 0 and 100\n", __FUNCTION__);
        return -1;
    }

    period = readGPIO(_fd.pwmPeriod);

    dutyCycle = (float)period*value/100.0;
    if(writeGPIO(_fd.pwmDutyCycle, dutyCycle) < 0){
        fprintf(stderr, "%s - Error writing duty cycle\n", __FUNCTION__);
        return -1;
    }

    writeGPIO(_fd.pwmEnable, 1);

    fprintf(stderr, "Dutycycle: %d\n", dutyCycle);
    return dutyCycle;
}
