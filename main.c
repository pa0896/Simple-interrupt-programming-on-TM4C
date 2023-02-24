#include <stdint.h>
#define GPIO_PORTB_DATA_R       (*((volatile unsigned long *)0x400053FC))
#define GPIO_PORTB_DIR_R        (*((volatile unsigned long *)0x40005400))
#define GPIO_PORTB_AFSEL_R      (*((volatile unsigned long *)0x40005420))
#define GPIO_PORTB_DEN_R        (*((volatile unsigned long *)0x4000551C))
#define GPIO_PORTB_AMSEL_R      (*((volatile unsigned long *)0x40005528))
#define GPIO_PORTB_PCTL_R       (*((volatile unsigned long *)0x4000552C))
#define SYSCTL_RCGCGPIO_R 		(*((volatile unsigned long *)0x400FE608))
#define SYSCTRL_STCTRL			(*((volatile unsigned long *)0xE000E010))
#define SYSCTRL_STRELOAD		(*((volatile unsigned long *)0xE000E014))
#define SYSCTRL_STCURRENT		(*((volatile unsigned long *)0xE000E018))
#define SYSCTRL_SYSPRI3			(*((volatile unsigned long *)0xE000ED20))
#define SYSCTL_PRGPIO_R			(*((volatile unsigned long *)0x400FEA08))
//void SysTick_Init(uint32_t period);
//void SysTick_Handler(void);

void init(void){
	SYSCTL_RCGCGPIO_R |= 0x00000002;           // Port B clock
	while((SYSCTL_PRGPIO_R&0x00000002) == 0){
		//wait for Port B clock to be stabilised
	};
	GPIO_PORTB_DIR_R |= 0x00000040;         // PB6 output
	GPIO_PORTB_DEN_R |= 0x00000040;         // enable digital I/O on PB6
	GPIO_PORTB_AMSEL_R &= ~0x00000040;     // disable analog function on PB6
	GPIO_PORTB_AFSEL_R &= ~0x00000040;      // disable alternate function on PB6
	GPIO_PORTB_PCTL_R &= ~0x0F000000;
	GPIO_PORTB_DATA_R |= 0x00000040;
}

void SysTick_Init(uint32_t period){
	SYSCTRL_STCTRL	&= ~0x00000007;
	SYSCTRL_STRELOAD	 = period - 1;
	SYSCTRL_STCURRENT	= 0;
	SYSCTRL_SYSPRI3		|= 	0x40000000;
	SYSCTRL_STCTRL	|=	0x00000007;
}

/**
 * main.c
 */
int main(void)
{
	init();
	SysTick_Init(80000000);
	while(1){
		//do nothing
	}
}
