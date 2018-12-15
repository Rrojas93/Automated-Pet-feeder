#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <lcd.h>
#include <mcp23017.h>
#include "finalMain.h"

extern int lcd;
extern int fd;
extern int button;
extern int petModeFlag;
extern int setModeFlag;
extern int petModeStorage;
extern int dispenseFlag;
int timeCount = 0;

int main(void)
{
	printf("Entered Main. \n");
	setups();
	
	while(digitalRead(powerSw) == 0)
	{
		printf("waiting for Power Switch. \n");
		delay(20);
	}
	
	while(digitalRead(powerSw))
	{
		//bootSequence();
		defaultDisplay();
		while(digitalRead(resetSw) == 0 && digitalRead(powerSw))
		{
//Main code routines begin here
//===========================================================================================
			timeCount++;
			smartDelay(20);
			
			if(setModeFlag)
			{
				setMode();
			}
			
			dispenseCheck();
			
			if (dispenseFlag == 1)
			{
				//vibMove();
				delay(2000);
				dispenseFlag = 0;
			}
			if(timeCount == 10)
			{
				//foodCheck();
				updateWeight();
				timeCount = 0;
			}
			updateTimer();
//===========================================================================================
		}
		while(digitalRead(resetSw) == 1 && digitalRead(powerSw))
		{
			printf("reset switch pressed. \n");
			delay(20);
		}
		printf("reset switch released \n");
	}
	pwDownSequence();
	return 0;
}

void bootSequence(void)
{
	digitalWrite(motorStatLed, LOW);
	digitalWrite(foodStatLed, LOW);
	digitalWrite(redLed, LOW);
	digitalWrite(blueLed, LOW);
	digitalWrite(greenLed, LOW);

	int i;
	
	for(i=0; i<4; i++)
	{
		segWrite(i, 0);
	}
	
	lcdTest();
	
	digitalWrite(motorStatLed, HIGH);
	digitalWrite(foodStatLed, HIGH);
	digitalWrite(redLed, HIGH);
	digitalWrite(blueLed, HIGH);
	digitalWrite(greenLed, HIGH);
	
	segClear();
	defaultDisplay();
	return;
}

void defaultDisplay(void)
{
	lcdPosition(lcd, 0, 1);
	lcdPrintf(lcd, "Weight(g):");
	wiringPiI2CWriteReg8 (fd,decimal,colon);
}
void pwDownSequence(void)
{
	digitalWrite(motorStatLed, HIGH);
	digitalWrite(foodStatLed, HIGH);
	digitalWrite(redLed, HIGH);
	digitalWrite(blueLed, HIGH);
	digitalWrite(greenLed, HIGH);
	
	lcdClear(lcd);
	return;
}

