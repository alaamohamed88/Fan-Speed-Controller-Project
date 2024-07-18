/*
 * Fan_Controller.c
 *
 * Created: 12/08/2023 05:37:41 م
 *  Author: Alaa Mohamed
 */ 

#include "ADC.h"
#include "LCD.h"
#include "TIMER.h"

int main(void)
{
	LCD_Initialize();
	ADC_Initialize();
	LCD_SendString("Temperature=");
	unsigned short voltage,temperature;
	while(1)
	{
		voltage = ADC_read() * 2.5;
		if (voltage >= 1000) //temperature is positive
		{
			temperature = (voltage - 1000)/10;
			if (temperature < 10)
			{
				LCD_MoveCursor(1,13);
				LCD_SendCharacter(temperature+48);
				LCD_SendCharacter(0xDF);
				LCD_SendCharacter('C');
				LCD_SendCharacter(' ');
				LCD_MoveCursor(2,1);
				LCD_SendString("Fan is off      ");
				TIMER0_FASTPWMNonInverting(0);
			}
			else if(temperature < 100)
			{
				LCD_MoveCursor(1,13);
				LCD_SendCharacter((temperature/10)+48);
				LCD_SendCharacter((temperature%10)+48);
				LCD_SendCharacter(0xDF);
				LCD_SendCharacter('C');
				LCD_SendCharacter(' ');
				if(temperature < 30)
				{
					LCD_MoveCursor(2,1);
					LCD_SendString("Fan is off      ");
					TIMER0_FASTPWMNonInverting(0);
				}
				else if (temperature >= 30 && temperature < 35)
				{
					LCD_MoveCursor(2,1);
					LCD_SendString("Fan on, Level 1");
					LCD_SendCharacter(' ');
					TIMER0_FASTPWMNonInverting(25);
				}
				else if (temperature >= 35 && temperature < 40)
				{
					LCD_MoveCursor(2,1);
					LCD_SendString("Fan on, Level 2");
					LCD_SendCharacter(' ');
					TIMER0_FASTPWMNonInverting(50);
				}
				else if (temperature >= 40 && temperature < 45)
				{
					LCD_MoveCursor(2,1);
					LCD_SendString("Fan on, Level 3");
					LCD_SendCharacter(' ');
					TIMER0_FASTPWMNonInverting(75);
				}
				else if (temperature >= 45)
				{
					LCD_MoveCursor(2,1);
					LCD_SendString("Fan on,Max Level");
					TIMER0_FASTPWMNonInverting(100);
				}
			}
			else
			{
				LCD_MoveCursor(1,13);
				LCD_SendCharacter((temperature/100)+48);
				LCD_SendCharacter(((temperature/10)%10)+48);
				LCD_SendCharacter((temperature%10)+48);
				LCD_SendCharacter(0xDF);
				LCD_SendCharacter('C');
				LCD_MoveCursor(2,1);
				LCD_SendString("Fan on,Max Level");
				TIMER0_FASTPWMNonInverting(100);
			}
		}
		else //temperature is negative
		{
			temperature = (1000 - voltage )/10;
			if (temperature < 10)
			{
				LCD_MoveCursor(1,13);
				LCD_SendCharacter('-');
				LCD_SendCharacter(temperature+48);
				LCD_SendCharacter(0xDF);
				LCD_SendCharacter('C');
				LCD_SendCharacter(' ');
				LCD_MoveCursor(2,1);
				LCD_SendString("Fan is off      ");
				TIMER0_FASTPWMNonInverting(0);
			}
			else if(temperature < 100)
			{
				LCD_MoveCursor(1,13);
				LCD_SendCharacter('-');
				LCD_SendCharacter((temperature/10)+48);
				LCD_SendCharacter((temperature%10)+48);
				LCD_SendCharacter(0xDF);
				LCD_SendCharacter('C');
				LCD_SendCharacter(' ');
				LCD_MoveCursor(2,1);
				LCD_SendString("Fan is off      ");
				TIMER0_FASTPWMNonInverting(0);
			}
			else
			{
				LCD_MoveCursor(1,13);
				LCD_SendCharacter('-');
				LCD_SendCharacter((temperature/100)+48);
				LCD_SendCharacter(((temperature/10)%10)+48);
				LCD_SendCharacter((temperature%10)+48);
				LCD_SendCharacter(0xDF);
				LCD_SendCharacter('C');
				LCD_MoveCursor(2,1);
				LCD_SendString("Fan is off      ");
				TIMER0_FASTPWMNonInverting(0);
			}
		}
		
	}
}