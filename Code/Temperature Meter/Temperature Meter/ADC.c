#include "ADC.h"

void ADC_vInit(unsigned char channel)
{
	//Enable Internal ADC Module
	SET_BIT(ADCSRA, ADEN);
	//Select Channel of ADC
	ADMUX |= channel;
	//Configure Adjustment
	#if defined LEFT_ADJUST
	SET_BIT(ADMUX, ADLAR);
	#elif defined RIGHT_ADJUST
	CLR_BIT(ADMUX, ADLAR);
	#endif
	//Configure refernce voltage
	#if defined AREF
	CLR_BIT(ADMUX, REFS0);
	CLR_BIT(ADMUX, REFS1);
	#elif defined AVCC
	SET_BIT(ADMUX, REFS0);
	CLR_BIT(ADMUX, REFS1);
	#elif defined INTERNAL_REF
	SET_BIT(ADMUX, REFS0);
	SET_BIT(ADMUX, REFS1);
	#endif 
	//Set Prescaler factor
	#if defined SCALE_2
	CLR_BIT(ADCSRA, ADPS0);
	CLR_BIT(ADCSRA, ADPS1);
	CLR_BIT(ADCSRA, ADPS2);
	#elif defined SCALE_4
	CLR_BIT(ADCSRA, ADPS0);
	SET_BIT(ADCSRA, ADPS1);
	CLR_BIT(ADCSRA, ADPS2);
	#elif defined SCALE_8
	SET_BIT(ADCSRA, ADPS0);
	SET_BIT(ADCSRA, ADPS1);
	CLR_BIT(ADCSRA, ADPS2);
	#elif defined SCALE_16
	CLR_BIT(ADCSRA, ADPS0);
	CLR_BIT(ADCSRA, ADPS1);
	SET_BIT(ADCSRA, ADPS2);
	#elif defined SCALE_32
	SET_BIT(ADCSRA, ADPS0);
	CLR_BIT(ADCSRA, ADPS1);
	SET_BIT(ADCSRA, ADPS2);
	#elif defined SCALE_64
	CLR_BIT(ADCSRA, ADPS0);
	SET_BIT(ADCSRA, ADPS1);
	SET_BIT(ADCSRA, ADPS2);
	#elif defined SCALE_128
	SET_BIT(ADCSRA, ADPS0);
	SET_BIT(ADCSRA, ADPS1);
	SET_BIT(ADCSRA, ADPS2);
	#endif
} 

unsigned short ADC_u16Read(void)
{
	unsigned short return_val;
	//Start Conversion
	ADC_vStartConversion();
	//Checking the conversion
	while(READ_BIT(ADCSRA, ADIF) == 0);
	//Clear Flag bit
	SET_BIT(ADCSRA, ADIF);
	//Read the value
	return_val = ADCL;
	return_val |= (ADCH << 8);
	return return_val;
}

void ADC_vStartConversion(void)
{
	SET_BIT(ADCSRA, ADSC);
}

void ADC_vControlInterrupt(unsigned char enable)
{
	if(enable == 1)
	{
		//Enable Global Interrupt
		sei();
		//Enable Interrupt Bit
		SET_BIT(ADCSRA, ADIE);
	}
	else
	{
		//Disable Global Interrupt
		cli();
		//Disable Interrupt Bit
		CLR_BIT(ADCSRA, ADIE);
	}
}
