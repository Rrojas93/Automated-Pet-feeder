/********************************************************************************************
	setups.c
---------------------------------------------------------------------------------------------
	by: Raul Rojas
	
	Function: void setups(void)
	This funciton contains all necessary lines of code which initialize wiringPi libraries
	as well as any other necessry GPIO set ups for peripherals. Setups are orginized by
	peripheral. 
********************************************************************************************/

#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdlib.h>
#include <lcd.h>
#include <mcp23017.h>
#include "finalMain.h"

int lcd;	//declaring LCD handle variable. 
int fd;

void setups(void)
{
	
	wiringPiSetupGpio();
	
	//General IO setups
	pinMode(motorStatLed, OUTPUT);
	pinMode(foodStatLed, OUTPUT);
	pinMode(redLed, OUTPUT);
	pinMode(blueLed, OUTPUT);
	pinMode(greenLed, OUTPUT);
	
	digitalWrite(motorStatLed, HIGH);
	digitalWrite(foodStatLed, HIGH);
	digitalWrite(redLed, HIGH);
	digitalWrite(blueLed, HIGH);
	digitalWrite(greenLed, HIGH);
	
	pinMode(resetSw, INPUT);
	pinMode(powerSw, INPUT);
	pinMode(petModeSw, INPUT);
	pinMode(setModeSw, INPUT);
	pinMode(firstPedal, INPUT);
	pinMode(secondPedal, INPUT);
	pinMode(thirdPedal, INPUT);

	//Motor Setups
	pinMode(motorSig, OUTPUT);
	pinMode(motorStatLed, OUTPUT);
	pinMode(hes, INPUT);
	
	//SEVEN SEGMENT SETUP
		//int fd;
		if((fd=wiringPiI2CSetup(0x71)))//Intializing seven segment on I2C bus and handle 
		{}

	//LCD SETUP
		int i;
		//wiringPiSetupGpio();	//must have to coplie program
		mcp23017Setup (100, 0x20);	//Gpio expander initialization.
		//printf("Rpi MCP23017 Test\n");

		for (i=0;i<6;++i)		//loop to set pin modes for LCD. (on GPIO expander pins)
		{
			pinMode(108+i,OUTPUT);

		}

		//LCD initialization and handle set up
		
		lcd = lcdInit(2,16,4,LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7,0,0,0,0);
		//{
			//printf("lcd init failed!\n");
			//return -1;
		//}
		
	//KEYPAD SETUP
		for (i = 0; i < 4; i++)		//setting up pin modes.
		{
			pinMode (104+i, OUTPUT);	//all rows = outputs, all columns = inputs.
		}
		pinMode(c1, INPUT);	//Column pin assignments 
		pinMode(c2, INPUT);
		pinMode(c3, INPUT);
		pinMode(c4, INPUT);
		
	//ADC SETUP HX711
		pinMode (DOUT,INPUT);			//setting up pin modes
		pinMode (PD_SCK, OUTPUT);
		digitalWrite (PD_SCK, LOW);		//setting hx711 in normal mode
		
	//RANGIN MODULE SETUPS
		//wiringPiSetupGpio();
		pinMode(TRIGPIN, OUTPUT);
		pinMode(ECHOPIN, INPUT);
				
		//TRIGPIN must start low in order to get a clear signal.
		digitalWrite(TRIGPIN, LOW);
	//	delay(30);

	//HES SETUP
	pinMode(hes, INPUT);
	
	
}