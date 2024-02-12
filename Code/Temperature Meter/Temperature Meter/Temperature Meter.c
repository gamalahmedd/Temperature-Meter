#include "ADC.h"
#include "LCD.h"
#include "MACROS.h"
#define F_CPU 8000000UL
#include <util/delay.h>

unsigned short temperature;
int main(void)
{
	LCD_vInit();
	ADC_vInit(CHANNEL1);
	LCD_vSendString("Temperature = ");
	while(1)
	{
		temperature = (ADC_u16Read() * 0.25);
		if(temperature < 10)
		{
			//Write New Temp Value
			LCD_vMoveCursor(1, 14);
			LCD_vSendChar(' ');
			LCD_vSendChar(' ');
			LCD_vSendChar(temperature + 48);
			LCD_vSendChar(0xDF);
			LCD_vSendChar('C');
		}
		else if(temperature < 100)
		{
			//Write New Temp Value
			LCD_vMoveCursor(1, 14);
			LCD_vSendChar(' ');
			LCD_vSendChar((temperature / 10) + 48);
			LCD_vSendChar((temperature % 10) + 48);
			LCD_vSendChar(0xDF);
			LCD_vSendChar('C');
		}
		else if(temperature < 155)
		{
			//Write New Temp Value
			LCD_vMoveCursor(1, 14);
			LCD_vSendChar((temperature / 100) + 48);
			LCD_vSendChar(((temperature % 100) / 10) + 48);
			LCD_vSendChar(((temperature % 100) % 10) + 48);
			LCD_vSendChar(0xDF);
			LCD_vSendChar('C');
		}
	}
}