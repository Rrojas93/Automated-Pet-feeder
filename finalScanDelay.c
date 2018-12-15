#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <lcd.h>
#include <mcp23017.h>
#include "finalMain.h"

int button;
int petModeFlag;
int setModeFlag;

int firstPedalFlag;
int secondPedalFlag;
int thirdPedalFlag;
int dispenseFlag;

void smartDelay(int ms)
{
	if (ms < 20)			//making sure that the while loop executes at least once.
	{
		ms = 20;
	}

	int i; 			//calculating the amount of times to preform the while loop.

	//int stat = 0;
	int timeCheck = 0;	//used for testing how much time has been delayed in total.
	
	for(i = ms/20; i >= 0; i--)
	{
		//Priority 1: Power and reset Switch/Button.
		if(digitalRead(powerSw) == 0 || digitalRead(resetSw) == 1 )
		{
			break;
		}
		
		//Priority 2: Set mode & Pet mode Switches.
		if(digitalRead(setModeSw))
		{
			setModeFlag = 1;
		}
		else
		{
			setModeFlag = 0;
		}
		
		if(digitalRead(petModeSw))
		{
			petModeFlag = 1;
		}
		else
		{
			petModeFlag = 0;
		}
	  
		//Priority 3: keypad scan/delay
		while((button = scanKeypad()) > 0)
		{
			if (button == 16)
			{
				dispenseFlag = 1;
			}
			
			if(button > 12)
			{
				//printf("button pressed: %d \n", button);
			}
			else if(button > 8)
			{
				delay(5);
			}
			else if(button > 4)
			{
				delay(10);
			}
			else if(button > 0)
			{
				delay(15);
			}
			timeCheck += 20;
			
			if(timeCheck >= ms || i <= 0)
			{
				i = 0;
				//printf("breaking.. \n");
				break;
			}
			else
			{
				//printf("smartDelay loop iteration: %d \n", i);
				//printf("Time delayed: %d \n", timeCheck);
				i--;
			}
		}
		//printf("smartDelay loop iteration: %d \n", i);
		//printf("Time delayed: %d \n", timeCheck);
		
		
	}
	if (digitalRead(firstPedal))
		{
			while(digitalRead(firstPedal))
			{
				firstPedalFlag = 1;
			}
			printf("firstPedalFlag: %d\n", firstPedalFlag);
			//return;
		}
		else 
		{
			firstPedalFlag = 0; 
		}
		
		if (digitalRead(secondPedal))
		{
			while(digitalRead(secondPedal))
			{
				secondPedalFlag = 1;
			}
			//return;
		}
		else 
		{
			secondPedalFlag = 0; 
		}
		
		if (digitalRead(thirdPedal))
		{
			while(digitalRead(thirdPedal))
			{
				thirdPedalFlag = 1;
			}
			//return;
		}
		else 
		{
			thirdPedalFlag = 0; 
		}
	//printf("secondPedalFlag: %d\n", secondPedalFlag);
	//printf("thirdPedalFlag: %d\n", thirdPedalFlag);
	return;
}