#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <lcd.h>
#include "finalMain.h"

extern int lcd;
int weight;

/********************************************************************************************
HX711 Setup Function
	by Isrrael Mendoza
	
	This function is used to intialize the Raspberry Pie and the hx711. Sets up pin modes
	and puts hx711 in normal operating conditions.
	
********************************************************************************************/
void hx711Setup(void)
{
	
	pinMode (DOUT,INPUT);			//setting up pin modes
	pinMode (PD_SCK, OUTPUT);
	digitalWrite (PD_SCK, LOW);		//setting hx711 in normal mode
}
/********************************************************************************************
BitBang Function 
	by Isrrael Mendoza 
	
	This function is used to retrieve the 24 bit output from the hx711. The "Bit Banging"
	method is used to obtain bits. Once Dout goes low the hx711 is ready for data is ready
	for retrieval. While Dout is low we will pulse PD_SCK and with every pulse a bit shifted
	our from the dout pin. Repeat 24 times to obatin our 24 bits and then pulse the PD_SCK 
	pin once more to select channel A with a gain of 128.
	
********************************************************************************************/
long startTime;
long timeOut;
int storedData = 0;

int offset=58;
int getMass()						//bit banging will be implemented to
{									//retrieve data
	printf("inside getMass().\n");
	int i;
	int data=0;
	startTime = micros();
	while (digitalRead(DOUT))	//waits until hx711 is ready for data retrieval
	{
		timeOut = micros() - startTime;
		if(timeOut >= 100000)
		{
			return storedData;
		}
	}
	
	for (i=0;i<25;i++)
	{				//Pulse PD_SCK to shift bits one by one, starting with
		if(i <= 23)
		{
		digitalWrite(PD_SCK, HIGH); 	//MSB
		data = ((data<<1)|digitalRead(DOUT)); //store bits into data variable
		digitalWrite(PD_SCK, LOW);
		}
		
	}
	
	if (data >= 0x800000) 
	{
		data= (data|0xFF000000);
	}
	

	data =(0.001196359*data)+offset;
	data = (data *2.127659574);
	
	//printf("data: %d", data);
	//if((data-storedData) > 100 || (storedData - data) > 100)
	//{
		//data = storedData;
	//}
	printf("exit getMass(). data: %d \n", data);
	storedData = data;
	return data;				//bit signed inter
}

/********************************************************************************************
********************************************************************************************/

int tare()
{
	offset = (getMass()-offset);		//Tares the balance 
	
	return offset;
}
//int storedWeight = 0;
void updateWeight(void)
{	
	//int measure = -999;
	/*int count = 0;
	while(measure == -999)
	{
		count++;
		printf("GETING NEW WEIGHT\n");
		measure = avgWeight();
		if(count == 3)
		{
			return;
		}
	}*/
	weight = getMass();
	
	
	//position lcd curser to a position which will not interfere with the constant characters
	lcdPosition(lcd, 10,1);
	
	//clear any existing characters in the data section of the first line of the LCD.
	lcdPrintf(lcd, "      ");	
	
	//Reposition LCD curser
	lcdPosition(lcd, 10,1);
	//printf("Weight: %d g\n", weight);
	
	//Print data into grams.
	lcdPrintf(lcd, "%d", weight);
	
	return;
}

int avgWeight(void)
{
	int i;
	
	int measure1 = 0;
	int measure2 = 0;
	int measure3 = 0;
	
	weight = 0;
	// call function which reads and converts the data into g's. Funciton located in hx711.c
	for(i = 0; i < 3; i++)
	{
		switch (i)
		{
			//delay(5);
			case 0:
				measure1 = getMass();
			break;
			
			case 1: 
				measure2 = getMass();
			break;
			
			case 2:
				measure3 = getMass();
			break;
		}
	}
	
	if(((measure1 > measure2) && (measure1 - measure2) < 50) || ((measure1 < measure2) && (measure1 - measure2) > -50))
	{
		return ((measure1+measure2)/2);
	}
	else if(((measure1 > measure3) && (measure1 - measure3) < 50) || ((measure1 < measure3) && (measure1 - measure3) > -50))
	{
		return ((measure1 + measure3)/2);
	}
	else if(((measure2 > measure3) && (measure2 - measure3) < 50) || ((measure2 < measure3) && (measure2 - measure3) > -50))
	{
		return ((measure2 + measure2)/2);
	}
	else 
	{
		return -999;
	}
}