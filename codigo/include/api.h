/*
    Universidade Federal do Rio Grande do Sul
    Escola de Engenharia
    Departamento de Sistemas Elétricos de Automação e Energia
    Microcontroladores ENG10032

    André Dexheimer Carneiro 00243653
    Camilla Stefani Schmidt 00237738
    Henrique Ecker Pchara 00213945

    This API provides basic controls over the Quanser 2DSFJE Robot

    Copyright (c) 2018 André Dexheimer Carneiro, Camilla Stefani Schmidt and Henrique Ecker Pchara

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

    You can also obtain a copy of the GNU General Public License
    at <http://www.gnu.org/licenses>.

*/

#ifndef API_H
#define API_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <math.h>
#include <byteswap.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <linux/spi/spidev.h>

// IO 00 gpio11 as output(ENABLE)
// IO 01 gpio12 as input (ELB2)
// IO 02 gpio13 as input (ELB1)
// IO 03 pwm1 as output (MOTOR)
// IO 04 gpio6 as input(LFLAG_1)
// IO 05 gpio0 as input (DFLAG_1)
// IO 06 gpio1 as output (INDEX_1)
// IO 07 gpio38 as output (EN_1)
// IO 10 gpio10 as output (SS)
// IO 11 (MOSI)
// IO 12 (MISO)
// IO 13 (SCK)

// Input pins
# define LFLAG "/sys/class/gpio/gpio6/value"
# define DFLAG "/sys/class/gpio/gpio0/value"
# define ELB1 "/sys/class/gpio/gpio13/value"
# define ELB2 "/sys/class/gpio/gpio12/value"
// Output pins
# define INDEX "/sys/class/gpio/gpio1/value"
# define EN "/sys/class/gpio/gpio6/value"
# define ENABLE "/sys/class/gpio/gpio38/value"
// PWM pin
#define PWM_DUTYCYCLE "/sys/class/pwm/pwmchip0/pwm1/duty_cycle"
#define PWM_ENABLE "/sys/class/pwm/pwmchip0/pwm1/enable"
#define PWM_PERIOD "/sys/class/pwm/pwmchip0/device/pwm_period"


/*
    Constantes definidas na documentação do decodificador LS7366

    Esta documentação pode ser acessada em https://lsicsi.com/datasheets/LS7366R.pdf

    MDR0 configuration data - the configuration byte is formed with
    single segments taken from each group and ORing all together.
*/

//Count modes
#define NQUAD 0x00 			//non-quadrature mode
#define QUADRX1 0x01 		//X1 quadrature mode
#define QUADRX2 0x02 		//X2 quadrature mode
#define QUADRX4 0x03 		//X4 quadrature mode

//Running modes
#define FREE_RUN 0x00
#define SINGE_CYCLE 0x04
#define RANGE_LIMIT 0x08
#define MODULO_N 0x0C

//Index modes
#define DISABLE_INDX 0x00 	//index_disabled
#define INDX_LOADC 0x10 	//index_load_CNTR
#define INDX_RESETC 0x20 	//index_rest_CNTR
#define INDX_LOADO 0x30 	//index_load_OL
#define ASYNCH_INDX 0x00 	//asynchronous index
#define SYNCH_INDX 0x80 	//synchronous index

//Clock filter modes
#define FILTER_1 0x00 		//filter clock frequncy division factor 1
#define FILTER_2 0x80 		//filter clock frequncy division factor 2

//Flag modes
#define NO_FLAGS 0x00 		//all flags disabled
#define IDX_FLAG 0x10; 		//IDX flag
#define CMP_FLAG 0x20; 		//CMP flag
#define BW_FLAG 0x40; 		//BW flag
#define CY_FLAG 0x80; 		//CY flag

//1 to 4 bytes data-width
#define BYTE_4 0x00; 		//four byte mode
#define BYTE_3 0x01; 		//three byte mode
#define BYTE_2 0x02; 		//two byte mode
#define BYTE_1 0x03; 		//one byte mode

//Enable/disable counter
#define EN_CNTR 0x00; 		//counting enabled
#define DIS_CNTR 0x04; 		//counting disabled

/* LS7366R op-code list */
#define CLR_MDR0 0x08
#define CLR_MDR1 0x10
#define CLR_CNTR 0x20
#define CLR_STR 0x30
#define READ_MDR0 0x48
#define READ_MDR1 0x50
#define READ_CNTR 0x60
#define READ_OTR 0x68
#define READ_STR 0x70
#define WRITE_MDR1 0x90
#define WRITE_MDR0 0x88
#define WRITE_DTR 0x98
#define LOAD_CNTR 0xE0
#define LOAD_OTR 0xE4

// Fim das costantes definidas na documentação
// --------------------------------------------------------------

// Contém todos os descritores acessados para o acesso aos pinos da Galileo
typedef struct fds{
    // Inputs
    int lflag, dflag, elb1, elb2;
    // Outputs
    int index, en, enable;
    // PWM
    int pwmDutyCycle, pwmEnable, pwmPeriod;
    // SPI
    int spi;
} FDS;

#ifdef __cplusplus
extern "C"
{
#endif

    /*
    Aciona o motor com o valor de tensão indicado no parâmetro.

    Valores de retorno:
        -2 -> Erro, parâmtro "volts" fora dos limites
        -1 -> Erro na configuração do sinal PWM
         1 -> Execução correta
    */
    extern int setMotorVoltage(double volts);

    /*
	Retorna a posição atual do robô.

	Valores de retorno:
		Posição do robô em radianos
    */
    extern float readEncoders();

    /*
    Retorna o valor lógico do sensor de fim de curso denominado ELB1.

    Valores de retorno:
        -1 -> Erro na leitura do pino GPIO correspondente
         0 -> Execução correta, valor lido do sensor é 0
         1 -> Execução correta, valor lido do sensor é 1
    */
    extern int readElbow1();

    /*
    Retorna o valor lógico do sensor de fim de curso denominado ELB2.

    Valores de retorno:
        -1 -> Erro na leitura do pino GPIO correspondente
         0 -> Execução correta, valor lido do sensor é 0
         1 -> Execução correta, valor lido do sensor é 1
    */
    extern int readElbow2();

    /*
	Faz o cáculo do controlador PID

	Valor de retorno:
        Tensão que deve ser aplicada no motor.
    */
    extern double PID(double endPos, double curPos);

    /*
	Redefine o contador do decoder
    */
    extern void clear_counter();

    /*
    Inicializa todos os descritores de arquivos utilizados pela API.
    Deve ser a primeira função chamada.

    Valores de retorno:
        -1 -> Erro na inicialização
         1 -> Execução correta
    */
    extern int init();

    /*
    Configura o decodificador de quadratura para a transferência de dados por
    SPI.
    É chamada internamente pela função init().

    Valores de retorno:
        -1 -> Erro na inicialização
         1 -> Execução correta
    */
    extern int init_spi();

    /*
    Finaliza a execução da API.
    Deve ser a última função chamada.
    */
    extern void finish();

    /*
    Testa todos os pinos utilizados pela API.
    */
    extern void testPins(int numIterations, int interval);

    /*
    Lê o valor de um pino GPIO.

    Valores de retorno:
        -1 -> Erro acessando os pinos
         0 -> Execução correta, valor lido do pino é 0
         1 -> Execução correta, valor lido do pino é 1
    */
    extern int readGPIO(int fd);

    /*
    Escreve um valor em algum pino de saída.

    Valores de retorno:
        -1 -> Erro escrevendo dado
        >0 -> Número de bytes escritos no arquivo.
    */
    extern int writeGPIO(int fd, int data);

    /*
    Determina o valor do duty cycle do sinal PWM a partir de um valor entre
    0 e 100 passado como parâmetro.

    Valores de retorno:
        -1 -> Erro configurando sinal PWM
        >0 -> Valor do duty cycle atribuído ao sinal PWM
    */
    extern int setPWM(double value);

#ifdef __cplusplus
};
#endif
#endif
