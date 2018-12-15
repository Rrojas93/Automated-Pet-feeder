/*******************************************************************************************
*    rangingMod.c
*    Group 4: Automatic Pet Feeder
*    Group Members: Raul Rojas, Nyron Daniel & Isrreal Mendoza
*		   
*    This program when executed will use an ultrasonic Ranging Module (HC-SR04) to find the
*    distance of the furthest object in centimeters. This program will be used to detect the
*    food level of our Pet Feeder.   
*******************************************************************************************/
#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <lcd.h>
#include "finalMain.h"

//#define TRIGPIN 4
//#define ECHOPIN 6

//int getCM();
void rangingModSetup();
long travelTime;
void callTest(void);
long startTime;
extern int lcd;
/*
int main (void)
{			//Calling Ultrasonic Ranging Module Function.
			rangingModSetup();

			printf("Distance: %dcm\n", getCM());
	return 0;
}
*/

void rangingModSetup () 
{
				wiringPiSetupGpio();
				pinMode(TRIGPIN, OUTPUT);
				pinMode(ECHOPIN, INPUT);

				//TRIGPIN must start low in order to get a clear signal.
				digitalWrite(TRIGPIN, LOW);
				delay(30);
}

int getCM()
{
	printf("in getCM\n");
	//Sending Trigger pulse.
	printf("sending trigpin signal.\n");
	digitalWrite(TRIGPIN, HIGH);
	printf("trigpin high.\n");
	delayMicroseconds(20);
	digitalWrite(TRIGPIN, LOW);
	printf("trigpin low. trigger signal sent.\nStarting wait. \nwaiting for signal. \n");
	//printf("starting wait.");
	//printf("waiting for signal\n");

	startTime = micros();

	callTest();

	//Waiting for ECHOPIN to end.
	startTime = micros();

	while (digitalRead(ECHOPIN) == HIGH);

	travelTime = micros() - startTime;
	//Attaining the distance in centimeters.
	int distance = travelTime / 58;
	
	printf("exit getCM. Distance: %d", distance);
	return distance;
}

void callTest(void)
{

	while (digitalRead(ECHOPIN) == LOW)
	{
		printf("test");
		travelTime = micros() - startTime;
		if(travelTime > 500)
		{
			break;
		}
	}
	return;
}

void foodCheck(void)
{
	int distance = getCM();
	if(distance >= 12)
	{
		digitalWrite(foodStatLed, LOW);
	}
	else
	{
		digitalWrite(foodStatLed, HIGH);
	}
	
}