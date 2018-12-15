/********************************************************************************************
   motorTest2.c
---------------------------------------------------------------------------------------------
	Group Name: Automatic Pet Feeder
	Group Members: Raul Rojas,Isrrael Mendoza,Nyron Daniel
	
	By: Raul Rojas
	This program demonstrates the funcitonality of our servo motor and its functions which 
	will be incorperated in our finished project. The demo of this project will perform 
	short dispenses that allow the hall effect sensor to keep track of the position of the 
	motor. This is crucial so that the program will know when the motor is stalled and the
	motor will perform a maneuver in an attempt to unjam whatever was causing it to be 
	stuck. 

********************************************************************************************/

#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <time.h>
#include "finalMain.h"

//declaring variables needed for global use in file.
int motorPosition = 0;	//Used to store the value of the current position of the motor.
int previousPosition;	//Used to store the value of the previous position of the motor.
int stallFlag;			//A flag which indicates if the motor is stalled. 
extern int dispenseFlag;

//main used for testing of functions

/*
int main(void)
{
	//WiringPi GPIO pin initialization
	wiringPiSetupGpio();
	
	pinMode(motorSig, OUTPUT);
	pinMode(motorStatLed, OUTPUT);
	pinMode(hes, INPUT);

	printf("initialization successful.\nBeginning motor testing.\n\n");

	digitalWrite(motorSig, 0);	//Making sure the motor signal pin begins in a known state.
	
	//executing motor testing
	while(1)
	{
		delay (1000);	//delay time for demo
		
		time_t result = time(NULL) -14400;
		printf("current time: %s \n",  asctime(localtime(&result)));

		//motorDispense();
		printf("begin move.");
		vibMove();
		delay (1000);	//delay time for demo
		
		//motorUnstall();
		
		printf("Input a value from 650 to 2200: ");
		scanf("%d", &motorVal);
		motorPosition = motorVal;
		motorMove(motorVal);
		printf("value accepted. Motor shouldve moved.\n");
		delay(100);

		if(digitalRead(hes)==0)
		{
			digitalWrite(motorStatLed,0);
		}
		else
		{
			digitalWrite(motorStatLed,1);
		}
		
	}

	return 0;
}
*/


/********************************************************************************************
   void motorMove(int value)
---------------------------------------------------------------------------------------------
	By: Raul Rojas
	
	This function is the core of the program. It is available to other files in case
	the motor needs to be positioned to a specific location. Using custom software pulse
	width modulation to apply a signal to the motor which corresponds to the position 
	desired. The motor itself can only move about 120 degrees thus limiting the input value
	from around 650 - 2200. These values correspond to the HIGH time of the pulse. This 
	function then adjust the low time to fit a 20ms window (50Hz). 

********************************************************************************************/
void motorMove(int value)
{
	int i;
	for(i = 0; i < 10 ; i++)	//Loop to repeat the desired PWM signal for a set time.
	{
		digitalWrite(motorSig, HIGH);	//sets the signal pin HIGH 
		delayMicroseconds(value);		//delay time for the HIGH signal 
		digitalWrite(motorSig, LOW);	//Clears the signal pin 
		delayMicroseconds(20000-value);	//adjusts LOW time so the frequency is 50Hz(20ms).
	}
	return;
}

/********************************************************************************************
   void motorDispense(void)
---------------------------------------------------------------------------------------------
	By: Raul Rojas
	
	This function provides a smart method of dispensing. It attempts to determine the current
	position of the motor and then moves the motor accordingly. This is important becuase 
	since the motor can only rotate 120 degrees, it must know what position the motor is in 
	to rotate in the right direction. It also uses the hall effect sensor to detect whether 
	the motor has been stalled after each movement. To accomplish this, the motor must move 
	in 90 degree increments whilst checking the hall effect sensor between those movements
	to make sure the motor actually moved. 
	
	note: The hall effect sensor is positioned at 90 degrees. Therefore, when the magnet is 
	at 0 or 180 (120 actual) degrees, the hall effect sensor should not detect a magnet. 
	For convention, consider 650 as 0 degrees, 1500 as 90 degrees, and 2200 as 180 degrees.

********************************************************************************************/
void motorDispense(void)
{
	int count = 0;	//count which controls the amount of desired dispenses. 
	
	//On boot motorPosition is 0 that way the program can attempt to determine position.
	if(motorPosition == 0)
	{
		if(!digitalRead(hes))	//Is the motor position in 90 degrees?
		{
			motorPosition = 1501;	
		}
		else
		{
			motorMove(1501);	//if not at 90 deg, move to it as a starting position. 
			delay(100);
			motorPosition = 1501;
			count++;			//This will count as a dispense. 
			printf("count: %d \n", count);

		}
	}
	while (count < 2)	//dispense only twice.
	{
		delay(500);	//pause between dispenses.
		
//The following Switch block rotates the motor according to its previous positions.
		switch (motorPosition)
		{
			case 650:
				motorMove(1499);	//use 1499 as an indicator that it moved from 650.
				motorPosition = 1499;	//store its known position.
				previousPosition = 650;	//store its previously known position.
				delay(100);
				if(digitalRead(hes))	//check if motor is stalled. 
				{
					stallFlag = 1;	//motor is stalled, set flag.
					printf("motor is stalled. \n");
					motorPosition = previousPosition;	//if stalled, motor didnt move.
				}
				else
				{
					count++;	//if not stalled, it counts as a successful dispense.
				}
				printf("count: %d \n", count);
				break;
				
			case 1499:	//indicates the previous position was at 650.
				motorMove(2200);	//rotate motor so it continues its rotation of 180 deg.
				motorPosition = 2200;
				previousPosition = 1499;
				delay(100);
				if(!digitalRead(hes))
				{
					stallFlag = 1;
					printf("motor is stalled. \n");
					motorPosition = previousPosition;
				}
				else
				{
					count++;
				}
				
				printf("count: %d \n", count);
				break;
				
			case 1500:	//this case only possible if using the manual input method of demo.
				motorMove(650);
				motorPosition = 650;
				previousPosition = 1500;
				delay(100);
				if(!digitalRead(hes))
				{
					stallFlag = 1;
					printf("motor is stalled. \n");
					motorPosition = previousPosition;
				}
				else
				{
					count++;
				}
				
				printf("count: %d \n", count);
				break;
				
			case 1501:	//indicates that previous position of motor was 2200.
				motorMove(650);
				motorPosition = 650;
				previousPosition = 1501;
				delay(100);
				if(!digitalRead(hes))
				{
					stallFlag = 1;
					printf("motor is stalled. \n");
					motorPosition = previousPosition;
				}
				else
				{
					count++;
				}
				
				printf("count: %d \n", count);
				break;
				
			case 2200:
				motorMove(1501);
				motorPosition = 1501;
				previousPosition = 2200;
				delay(100);
				if(digitalRead(hes))
				{
					stallFlag = 1;
					printf("motor is stalled. \n");
					motorPosition = previousPosition;
				}
				else
				{
					count++;
				}
				
				printf("count: %d \n", count);
				break;
				
			default:	//only used in the manual input method of motor demo.  
				motorMove(1501);
				motorPosition = 1501;
				previousPosition = 1501;
				delay(100);
				if(digitalRead(hes))
				{
					stallFlag = 1;
					printf("motor is stalled. \n");
					motorPosition = previousPosition;
				}
				else
				{
					count++;
				}
				
				printf("count: %d \n", count);
				
		}
		delay(500);	//delay time between dispenses.
		
		//if motor is position at 90 deg, turn off led. else, keep it on. 
		if(digitalRead(hes)==0)	
		{
			digitalWrite(motorStatLed,0);
		}
		else
		{
			digitalWrite(motorStatLed,1);
		}
		
		if(stallFlag)
		{
			motorUnstall();
		}
	}
}


/********************************************************************************************
   void motorUnstall(void)
---------------------------------------------------------------------------------------------
	By: Raul Rojas
	
	This short function performs a short maneuver to attempt to remove any thing that is 
	causing the motor to be stuck. It rotates back and forth quickly for a self fix solution. 

********************************************************************************************/
void motorUnstall(void)
{
	printf("unstalling.. \n");
	delay(500);
	int stall;	//count for loop.
	
	for(stall = 0; stall < 2; stall++)
	{
		motorMove(motorPosition + 300);	//rotate motor slightly one way from current position
		delay(20);
		motorMove(motorPosition - 300);	//rotate slightly other way from original position
		delay(20);
		motorMove(motorPosition);	//return to original position.
	}
	stallFlag = 0;	//release flag.
}

void vibMove(void)
{
	printf("Entered vibMove.");
	motorPosition = 650;
	motorMove(motorPosition);
	delay(1000);
	int adder = 700;
	int subtr = 600;
	//while(motorPosition < 2100);
	int i;
	for(i=0; i<50;i++)
	{
		printf("%d \n", i);
		//delay(50);
		motorMove(motorPosition += adder);
		printf("%d \n", motorPosition);
		if(motorPosition > 2200)
		{
			break;
		}
		//delay(50);
		motorMove(motorPosition -= subtr);
	}
	
	for(i=0; i<50;i++)
	{
		printf("%d \n", i);
		//delay(50);
		motorMove(motorPosition -= adder);
		printf("%d \n", motorPosition);
		if(motorPosition <650)
		{
			break;
		}
		//delay(50);
		motorMove(motorPosition += subtr);
	}
	dispenseFlag = 0;
	return;
}
