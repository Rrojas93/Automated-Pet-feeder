#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <wiringPi.h>
#include <lcd.h>
#include "finalMain.h"

extern int lcd;

extern int hour;
extern int min;

	int number;
	int numberStorage;
	int buttonPressed;
	//int cursor = 0;
	//int count = 27;
	int buttonFlag = 0;
	int incFlag = 0;
	int decFlag = 0;
	int toggleAP;
	int currentAP;
	int cursorShiftedF;
	int setModeStep;
	
	int hourTenths;
	int hourOnes;
	int minTenths;
	int minOnes;
	char ap;
	int perDay;
	//int timeBetweenHTenths;
	int timeBetweenHTenths;
	int timeBetweenHOnes;
	int timeBetweenMTenths;
	int timeBetweenMOnes;
void setMode(void)
{
	setModeStep = 0;
	while(digitalRead(setModeSw) && digitalRead(powerSw) && !digitalRead(resetSw))
	{
		delay(10);
		switch (setModeStep)
		{
			case 0:
				printf("in case zero.\n");
				timeSet();
			break;
			
			case 1:
				printf("in case one.\n");
				timesPerDay();
			break;
			
			case 2:
				if(perDay == 1)
				{
					setModeStep = 0;
					//timeBetweenHTenths = 0;
					//timeBetweenHTenths = 1;
					break;
				}
				printf("in case two.\n");
				timeBetweenDisp();
			break;
		}
		
		while(scanKeypad() == 8)
		{
			delay(10);
		}
	}
	saveHour();
	getHour();
	saveMin();
	getMin();
	saveAP();
	getAP();
	
	savePerDay();
	getPerDay();
	
	saveTimeBetween();
	getTimeBetween();
	
	lcdClear(lcd);
	return;
}	//end of setMode();

void timeSet(void)
{
	int cursor = 0;
	int count = 27;
	toggleAP = 0;
	
	lcdClear(lcd);
	lcdPosition(lcd, 0, 1);
	lcdPrintf(lcd, "First dispense.");
	lcdPosition(lcd, 0, 0);
	getHour();
	getMin();
	getAP();
	if(ap == 'A')
	{
		currentAP = 0;
	}
	else 
	{
		currentAP = 1;
	}
	
	printf("Hour Stored: %d%d \n", hourTenths, hourOnes);
	if(hourTenths == 0 && hourOnes == 0)
	{
		lcdPrintf(lcd, "    01:00 AM");
	}
	else 
	{
		lcdPrintf(lcd, "    %d%d:%d%d %cM", hourTenths, hourOnes, minTenths, 
			minOnes, ap);
	}
	
	while(digitalRead(setModeSw) && digitalRead(powerSw) && !digitalRead(resetSw))
	{
		count--;
		printf("in set Mode. count: %d \nnumber: %d \n", count, number);
		//delay(20);
		
		switch (cursor)
		{
			case 0:
			printf("entered case 0. \n");
				lcdPosition(lcd, 4, 0);	
				
				if (count == 26)
				{
					lcdPrintf(lcd, " ");
				}
				else if(count == 20 || buttonFlag == 1)
				{
					//printf("update LCD")
					if(buttonFlag == 1)
					{
						hourTenths = numberStorage;
						if(hourTenths > 1)
						{
							hourOnes = hourTenths;
							hourTenths = 0;
							
							//if(hourOnes > 2)
							//{
								//hourOnes = 2;
								lcdPosition(lcd, 5, 0);
								lcdPrintf(lcd, "%d", hourOnes);
								lcdPosition(lcd, 4, 0);
								cursor++;
							//}
						}
						if(hourTenths == 1 && hourOnes > 2)
						{
							hourOnes = 0;
							lcdPosition(lcd, 5, 0);
							lcdPrintf(lcd, "%d", hourOnes);
							lcdPosition(lcd, 4, 0);
						}
						if(hourTenths == 0 && hourOnes == 0)
						{
							hourOnes = 1;
							lcdPosition(lcd, 5, 0);
							lcdPrintf(lcd, "%d", hourOnes);
							lcdPosition(lcd, 4, 0);
						}
						//numberStorage = number;
						lcdPrintf(lcd, "%d", hourTenths);
						if(decFlag == 0 && incFlag ==0 && cursor < 5)
						{
							cursor++;
						}
						
						count = 27;
						buttonFlag = 0;
					}
					else
					{
						lcdPrintf(lcd, "%d", hourTenths);
					}
				}
				
				if(decFlag)
				{
					cursor = 4;
					decFlag = 0;
					count = 27;
				}
				if(incFlag)
				{
					cursor++;
					incFlag = 0;
					count = 27;
				}
				
				if (toggleAP == 1)
				{
					cursor = 4;
				}
				if(cursor != 0)
				{
					lcdPosition(lcd, 4, 0);
					lcdPrintf(lcd, "%d", hourTenths);
				}
				
				if(count == 0)
				{
					count = 27;
				}
				break;
				
			case 1:
			printf("entered case 1. \n");
				lcdPosition(lcd, 5, 0);
				
				if (count == 26)
				{
					lcdPrintf(lcd, " ");
				}
				else if(count == 20 || buttonFlag == 1)
				{
					//printf("update LCD")
					if(buttonFlag == 1)
					{
						hourOnes = numberStorage;
						if(hourTenths == 1 && hourOnes > 2)
						{
							hourOnes = 2;
						}
						if(hourTenths == 0 && hourOnes == 0)
						{
							hourOnes = 1;
						}
						//numberStorage = number;
						lcdPrintf(lcd, "%d", hourOnes);
						if(decFlag == 0 && incFlag ==0 && cursor < 5)
						{
							cursor++;
						}
						count = 27;
						buttonFlag = 0;
					}
					else
					{
						lcdPrintf(lcd, "%d", hourOnes);
					}
				}
				
				if(decFlag)
				{
					cursor--;
					decFlag = 0;
					count = 27;
				}
				if(incFlag)
				{
					cursor++;
					incFlag = 0;
					count = 27;
				}
				
				if (toggleAP == 1)
				{
					cursor = 4;
				}
				if(cursor != 1)
				{
					lcdPosition(lcd, 5, 0);
					lcdPrintf(lcd, "%d", hourOnes);
				}
				
				if(count == 0)
				{
					count = 27;
				}
				break;
			case 2:
			printf("entered case 2. \n");
				lcdPosition(lcd, 7, 0);
				
				if (count == 26)
				{
					lcdPrintf(lcd, " ");
				}
				else if(count == 20 || buttonFlag == 1)
				{
					//printf("update LCD")
					if(buttonFlag == 1)
					{
						minTenths = numberStorage;
						if(minTenths > 5)
						{
							minTenths = 5;
						}
						//numberStorage = number;
						lcdPrintf(lcd, "%d", minTenths);
						if(decFlag == 0 && incFlag ==0 && cursor < 5)
						{
							cursor++;
						}
						count = 27;
						buttonFlag = 0;
					}
					else
					{
						lcdPrintf(lcd, "%d", minTenths);
					}
				}
				
				if(decFlag)
				{
					cursor--;
					decFlag = 0;
					count = 27;
				}
				if(incFlag)
				{
					cursor++;
					incFlag = 0;
					count = 27;
				}
				
				if (toggleAP == 1)
				{
					cursor = 4;
				}
				if(cursor != 2)
				{
					lcdPosition(lcd, 7, 0);
					lcdPrintf(lcd, "%d", minTenths);
				}
				
				if(count == 0)
				{
					count = 27;
				}
				break;	
			case 3:
			printf("entered case 3. \n");
				lcdPosition(lcd, 8, 0);
				
				if (count == 26)
				{
					lcdPrintf(lcd, " ");
				}
				else if(count == 20 || buttonFlag == 1)
				{
					
					//printf("update LCD")
					if(buttonFlag == 1)
					{
						minOnes = numberStorage;
						/*
						if(!cursorShiftedF)
						{
							minOnes = numberStorage;
						}
						else
						{
							cursorShiftedF = 0;
						}
						*/
						//numberStorage = number;
						lcdPrintf(lcd, "%d", minOnes);
						if(decFlag == 0 && incFlag ==0 && cursor < 5)
						{
							cursor++;
						}
						count = 27;
						buttonFlag = 0;
					}
					else
					{
						lcdPrintf(lcd, "%d", minOnes);
					}
				}
				
				if(decFlag)
				{
					cursor--;
					decFlag = 0;
					count = 27;
				}
				if(incFlag)
				{
					cursor++;
					incFlag = 0;
					count = 27;
				}
				
				if (toggleAP == 1)
				{
					cursor = 4;
				}
				if(cursor != 3)
				{
					lcdPosition(lcd, 8, 0);
					lcdPrintf(lcd, "%d", minOnes);
				}
				
				if(count == 0)
				{
					count = 27;
				}
				break;	
			case 4:
			printf("entered case 4. \n");
				lcdPosition(lcd, 10, 0);
				
				if(toggleAP)
				{
					if(currentAP == 0)
					{
						currentAP = 1;
					}
					else if (currentAP == 1)
					{
						currentAP = 0;
					}
				}
				
				if (count == 26)
				{
					lcdPrintf(lcd, " ");
				}
				else if(count == 20 || toggleAP == 1 || decFlag)
				{
					
					if(currentAP == 1)
					{
						ap = 'P';
						lcdPrintf(lcd, "%c", ap);
						
					}
					else
					{
						ap = 'A';
						lcdPrintf(lcd, "%c", ap);
					}
					
					toggleAP =0;
				}
				
				if(count == 0)
				{
					count = 27;
				}
				
				if(incFlag)
				{
					cursor = 0;
					incFlag = 0;
					count = 27;
				}
				
				if(decFlag)
				{
					cursor--;
					decFlag = 0;
					count = 27;
					cursorShiftedF = 1;
				}
				
				if(cursor != 4)
				{
					lcdPosition(lcd, 10, 0);
					lcdPrintf(lcd, "%c", ap);
				}
				
				break;	
	
		}
		
		while((buttonPressed = scanKeypad()) > 0)
		{
			
			//buttonFlag = 1;
			
			
			number = numberPressed(buttonPressed);
			if(number >= 0)
			{
				buttonFlag = 1;
			}
			
			if(buttonPressed == 4)
			{
				toggleAP = 1;
			}
			
			if(buttonPressed == 13 && cursor >= 0)
			{
				
				decFlag = 1;
			}
			if (buttonPressed == 15 && cursor <= 5)
			{
				incFlag = 1;
			}
			
			if(buttonPressed == 8)
			{
				setModeStep++;
				break;
			}
		}
		
		if(number >= 0 && cursor != 4)
		{
			numberStorage = number;
			//if(cursor < 5)
			//{
				//cursor++;
			//}
		}
		//printf("numberStorage: %d \n", numberStorage);
		
		if(buttonPressed > 12)
		{
			//printf("button pressed: %d \n", button);
		}
		else if(buttonPressed > 8)
		{
			delay(5);
		}
		else if(buttonPressed > 4)
		{
			delay(10);
		}
		else if(buttonPressed > 0)
		{
			delay(15);
		}
		
		if(buttonPressed == 8)
		{
			break;
		}
		
	}
	
	saveHour();
	getHour();
	saveMin();
	getMin();
	saveAP();
	getAP();
	return;
} //end of timeSet();

void timesPerDay(void)
{
	lcdClear(lcd);
	int count = 27;
	getPerDay();
	printf("perDayValue grabed is: %d \n", perDay);
	lcdPosition(lcd, 0, 0);
	lcdPrintf(lcd, "dispenses/day: %d", perDay);
	while(digitalRead(setModeSw) && digitalRead(powerSw) && !digitalRead(resetSw))
	{
		
		count--;
		printf("count: %d \n", count);
		lcdPosition(lcd, 15, 0);
		if (count == 26)
		{
			lcdPrintf(lcd, " ");
		}
		else if(count == 20 || buttonFlag == 1)
		{
			lcdPrintf(lcd, "%d", perDay);
			buttonFlag =0;
		}
		
		if(count == 0)
		{
			count = 27;
		}
		
		while((buttonPressed = scanKeypad()) > 0)
		{
			number = numberPressed(buttonPressed);
			if(number >= 0)
			{
				buttonFlag = 1;
				perDay = number;
			}
			
			if(buttonPressed == 8)
			{
				setModeStep++;
				break;
			}
			
		}
		
		
		
		if(buttonPressed > 12)
		{
			//printf("button pressed: %d \n", button);
		}
		else if(buttonPressed > 8)
		{
			delay(5);
		}
		else if(buttonPressed > 4)
		{
			delay(10);
		}
		else if(buttonPressed > 0)
		{
			delay(15);
		}
		
		if(buttonPressed == 8)
		{
			break;
		}
	}
	
	savePerDay();
	getPerDay();
	
	return;
}	//end of timesPerDay();

void timeBetweenDisp (void)
{
	int cursor = 0;
	int incFlag;
	lcdClear(lcd);
	int count = 27;
	getTimeBetween();
	//timeBetweenHTenths = 1;
	//timeBetweenHOnes = 2;
	
	lcdPosition(lcd, 0, 0);
	lcdPrintf(lcd, "Time between");
	lcdPosition(lcd, 0, 1);
	lcdPrintf(lcd, "Disp:  %d%d:%d%d hrs", timeBetweenHTenths, timeBetweenHOnes, timeBetweenMTenths, timeBetweenMOnes);
	
	while(digitalRead(setModeSw) && digitalRead(powerSw) && !digitalRead(resetSw))
	{
		
		count--;
		//printf("count: %d \n", count);
		switch (cursor)
		{
			case 0:
				
				lcdPosition(lcd, 7, 1);
				if (count == 26)
				{
					lcdPrintf(lcd, " ");
				}
				else if((count == 20 || buttonFlag == 1))
				{
					if(buttonFlag == 1 && number >= 0)
					{
						timeBetweenHTenths = number;
					}
					
					//cursor conditions begin here
					if(timeBetweenHTenths == 0 && timeBetweenHOnes == 0 && timeBetweenMTenths == 0 && timeBetweenMOnes == 0)
					{
						printf("case 0: both zero ones is now 1 \n");
						timeBetweenMOnes = 1;
						lcdPosition(lcd, 11, 1);
						lcdPrintf(lcd, "%d", timeBetweenMOnes);
						lcdPosition(lcd, 10, 1);
					}
					else if(timeBetweenHTenths > 2)
					{
						printf("case 0: tenths greater than 2. ones is now thenths. \n");
						timeBetweenHOnes = timeBetweenHTenths;
						timeBetweenHTenths = 0;
						lcdPrintf(lcd, "%d", timeBetweenHTenths);
						lcdPosition(lcd, 8, 1);
						lcdPrintf(lcd, "%d", timeBetweenHOnes);
						lcdPosition(lcd, 7, 1);
					}
					else if(timeBetweenHTenths == 2 && timeBetweenHOnes > 4)
					{
						lcdPosition(lcd, 8, 1);
						timeBetweenHOnes = 4;
						lcdPrintf(lcd, "%d", timeBetweenHOnes);
						lcdPosition(lcd, 7, 1);
					}
					{
						lcdPosition(lcd, 7, 1);
						printf("case 0: no adjustments, tenths is 0, 1, or 2.\n");
						lcdPrintf(lcd, "%d", timeBetweenHTenths);
					}
					
					
					
				}
				
				if(buttonFlag == 1)
				{
					printf("case 0: button was pressed, moving cursor.\n");
					cursor = 1;
				}
					
				if(incFlag == 1)
				{
					printf("case 0: cursor flag is set, moving cursor.\n");
					cursor++;
					incFlag = 0;
				}
				if(decFlag == 1)
				{
					printf("case 0: cursor flag is set, moving cursor.\n");
					cursor = 3;
					decFlag = 0;
				}
				if(cursor != 0)
				{
					printf("case 0: cursor is not on case 0. displaying tenths before exit. tenths:%d Ones:%d\n", timeBetweenHTenths,timeBetweenHOnes);
					lcdPosition(lcd, 7, 1);
					lcdPrintf(lcd, "%d", timeBetweenHTenths);
				}
				
				if(count == 0)
				{
					count = 27;
				}
				
				buttonFlag = 0;
			break;
			
			case 1:
				lcdPosition(lcd, 8, 1);
				if (count == 26)
				{
					lcdPrintf(lcd, " ");
				}
				else if((count == 20 || buttonFlag == 1))
				{
					//printf("")
					if(buttonFlag == 1 && number >= 0)
					{
						timeBetweenHOnes = number;
					}
					
					//cursor conditions begin here
					printf("case 1: tenths:%d ones:%d \n", timeBetweenHTenths, timeBetweenHOnes);
					if(timeBetweenHTenths == 2 && timeBetweenHOnes > 4)
					{
						printf("case 1: total time greater than 24, adjusting..\n");
						timeBetweenHOnes = 4;
					}
					else
					if(timeBetweenHTenths == 0 && timeBetweenHOnes == 0 && timeBetweenMTenths == 0 && timeBetweenMOnes == 0)
					{
						timeBetweenHOnes = 1;
					}
					else
					{
						lcdPrintf(lcd, "%d", timeBetweenHOnes);
					}
				}
				if(buttonFlag == 1)
				{
					printf("case 0: button was pressed, moving cursor.\n");
					cursor++;
				}
				if(incFlag == 1)
				{
					printf("case 1: cursor flag set, moving cursor.\n");
					cursor++;
					incFlag = 0;
				}
				if(decFlag == 1)
				{
					printf("case 0: cursor flag is set, moving cursor.\n");
					cursor--;
					decFlag = 0;
				}
				if(cursor != 1)
				{
					printf("case 1: cursor is not in case 1. displaying ones before exit.\n");
					lcdPosition(lcd, 8, 1);
					lcdPrintf(lcd, "%d", timeBetweenHOnes);
				}
				
				if(count == 0)
				{
					count = 27;
				}
				buttonFlag = 0;
			break;
			
			case 2:
				lcdPosition(lcd, 10, 1);
				if (count == 26)
				{
					lcdPrintf(lcd, " ");
				}
				else if((count == 20 || buttonFlag == 1))
				{
					if(buttonFlag == 1 && number >= 0)
					{
						timeBetweenMTenths = number;
					}
					
					//cursor conditions begin here
					if(timeBetweenMTenths == 0 && timeBetweenMOnes == 0)
					{
						printf("case 0: both zero ones is now 1 \n");
						timeBetweenMOnes = 1;
						lcdPosition(lcd, 11, 1);
						lcdPrintf(lcd, "%d", timeBetweenMOnes);
						lcdPosition(lcd, 10, 1);
					}
					else if(timeBetweenMTenths > 5)
					{
						printf("case 0: tenths greater than 5. ones is now thenths. \n");
						timeBetweenMTenths = 5;
						lcdPrintf(lcd, "%d", timeBetweenMTenths);
					}
					else
					{
						lcdPosition(lcd, 10, 1);
						printf("case 0: no adjustments, tenths is 0, 1, or 2.\n");
						lcdPrintf(lcd, "%d", timeBetweenMTenths);
					}
				
				}
				
				if(buttonFlag == 1)
				{
					printf("case 0: button was pressed, moving cursor.\n");
					cursor++;
				}
					
				if(incFlag == 1)
				{
					printf("case 0: cursor flag is set, moving cursor.\n");
					cursor++;
					incFlag = 0;
				}
				if(decFlag == 1)
				{
					printf("case 0: cursor flag is set, moving cursor.\n");
					cursor--;
					decFlag = 0;
				}
				if(cursor != 2)
				{
					printf("case 0: cursor is not on case 0. displaying tenths before exit. tenths:%d Ones:%d\n", timeBetweenMTenths,timeBetweenMOnes);
					lcdPosition(lcd, 10, 1);
					lcdPrintf(lcd, "%d", timeBetweenMTenths);
				}
				
				if(count == 0)
				{
					count = 27;
				}
				
				buttonFlag = 0;
			break;
			
			case 3:
				lcdPosition(lcd, 11, 1);
				if (count == 26)
				{
					lcdPrintf(lcd, " ");
				}
				else if((count == 20 || buttonFlag == 1))
				{
					//printf("")
					if(buttonFlag == 1 && number >= 0)
					{
						timeBetweenMOnes = number;
					}
					//printf("case 1: tenths:%d ones:%d \n", timeBetweenMTenths, timeBetweenMOnes);
					
					//cursor conditions begin here
					if(timeBetweenHTenths == 0 && timeBetweenHOnes == 0 && timeBetweenMTenths == 0 && timeBetweenMOnes == 0)
					{
						timeBetweenMOnes = 1;
					}
					else
					{
						lcdPrintf(lcd, "%d", timeBetweenMOnes);
					}
				}
				
				if(incFlag == 1)
				{
					printf("case 1: cursor flag set, moving cursor.\n");
					cursor = 0;
					incFlag = 0;
				}
				if(decFlag == 1)
				{
					printf("case 0: cursor flag is set, moving cursor.\n");
					cursor--;
					decFlag = 0;
				}
				if(cursor != 3)
				{
					printf("case 1: cursor is not in case 1. displaying ones before exit.\n");
					lcdPosition(lcd, 11, 1);
					lcdPrintf(lcd, "%d", timeBetweenMOnes);
				}
				
				if(count == 0)
				{
					count = 27;
				}
				buttonFlag = 0;
			break;
		}
		
		
		if(count == 0)
		{
			count = 27;
		}
		
		while((buttonPressed = scanKeypad()) > 0)
		{
			number = numberPressed(buttonPressed);
			if(number >= 0)
			{
				buttonFlag = 1;
				//timeBetweenHTenths = number;
			}
			
			if(buttonPressed == 8)
			{
				setModeStep = 0;
				break;
			}
			
			if(buttonPressed == 15 )
			{
				incFlag = 1;
				
			}
			else if(buttonPressed == 13)
			{
				decFlag = 1;
			}
		}
		
		
		
		if(buttonPressed > 12)
		{
			//printf("button pressed: %d \n", button);
		}
		else if(buttonPressed > 8)
		{
			delay(5);
		}
		else if(buttonPressed > 4)
		{
			delay(10);
		}
		else if(buttonPressed > 0)
		{
			delay(15);
		}
		
		if(buttonPressed == 8)
		{
			break;
		}
	}
	
	saveTimeBetween();
	getTimeBetween();
	
	return;
}	//end of timeBetweenDisp();

int numberPressed(int buttonPressed)
{
	switch(buttonPressed)
	{
		case 1:
			return 1;
			break;
		case 2:
			return 2;
			break;
		case 3:
			return 3;
			break;
		case 5:
			return 4;
			break;
		case 6:
			return 5;
			break;
		case 7:
			return 6;
			break;
		case 9:
			return 7;
			break;
		case 10:
		 	return 8;
			break;
		case 11:
			return 9;
			break;
		case 14:
			return 0;
			break;
			
		default:
			return -1;
	}
}