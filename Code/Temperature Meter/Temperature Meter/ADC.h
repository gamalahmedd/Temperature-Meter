#ifndef ADC_H_
#define ADC_H_
#include "ADC_Config.h"
#include <avr/io.h>
#include "MACROS.h"
#include <avr/interrupt.h>

/*
	Function Name        : ADC_vInit
	Function Returns     : void
	Function Arguments   : unsigned char channel
	Function Description : Configure and Enable internal module ADC
*/
void ADC_vInit(unsigned char channel);
/*
	Function Name        : ADC_u16Read
	Function Returns     : unsigned short
	Function Arguments   : void
	Function Description : Get the value of input electrical analog signal after ADC conversion
*/
unsigned short ADC_u16Read(void);
/*
	Function Name        : ADC_vStartConversion
	Function Returns     : void
	Function Arguments   : void
	Function Description : Set ADSC flag to 1
*/
void ADC_vStartConversion(void);
/*
	Function Name        : ADC_vControlInterrupt
	Function Returns     : void
	Function Arguments   : unsigned char enable
	Function Description : Control Interrupt of ADC to disable or enable it
*/
void ADC_vControlInterrupt(unsigned char enable);
#endif