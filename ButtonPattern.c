#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include "finalMain.h"
#include <wiringPi.h>

extern int dispenseFlag;

extern int firstPedalFlag;
extern int secondPedalFlag;
extern int thirdPedalFlag;

int coolCount; 
int i; 
int n;
int number;
int firstNumber=-1;
int secondNumber=-1;
int thirdNumber=-1;
int startTime;
int timer;

void foodPattern(void)
{
	
	digitalWrite (redLed, HIGH);
	digitalWrite (blueLed, HIGH);
	digitalWrite (greenLed, HIGH);
	
	
	
	n=3; 		//chooses the amount of buttons that must be pressed before food is dispensed
	
	srand((unsigned) time(&t)); //intializes random number generator
	
	for (i=0;  i < n; i++ )	//3 random numbers between 0 and 2 will be generated
	{		
		if (i>0)
		{	
			while (number == firstNumber || number == secondNumber || number == thirdNumber)
			{
			number = rand()%3;	//store random number in variable 
			}	
		}
		else 
		{
			number = rand()%3;
		}	
		printf("Numer: %d\n", number);
		if (i==0)				
		{
			firstNumber = number;	
			chooseLed();			//stores the random number generated to a variable out side
		}							//the loops that generates the number. This way, the random
		else if (i==1)				// number is saved before it is overwritten by the next
		{
			secondNumber = number;
			chooseLed();
		}	
		else if (i==2)
		{
			thirdNumber = number;
			chooseLed();
		}
		
	}
	 
	printf("First Number\n");
	switch (firstNumber)
	{
		case 0:
			waitForFirstPedal();	//depending on the first random that was generated  
			break;					// the program will select the corresponding case
		case 1:					
			waitForSecondPedal();
			break;
		case 2:
			waitForThirdPedal();
			break;
	}
				
	printf("secondNumber\n");	
	switch (secondNumber)
	{
		case 0:
			waitForFirstPedal();
			break;						//the same proccess happens to 2 more times, since
		case 1:							//there is 3 different random number generated, which
			waitForSecondPedal();		//correlates to three dog pedals that must be pressed 
			break;						//before food is despensed
		case 2:
			waitForThirdPedal();
			break;
	}
		
	printf("ThirdNumber\n");	
	switch (thirdNumber)
	{
		case 0:
			waitForFirstPedal();
			break;
		case 1:
			waitForSecondPedal();	//once the third case is reached, the program will set the  
			break;					//dispense flag high wether the last dog pedal was pressed 
		case 2:						//or if the 1 minute timeout was reached
			waitForThirdPedal();
			break;	
	}
	
	printf("3 Minute Timeout\n");
	printf("Despense FOOD!\n");		//returns to main
	return;
} 


/********************************************************************************************
void Flash Red 
	By Isrrael Mendoza
	
	This Function will "Flash" the red LED when called upon. For instance if "0" was the 
	random number generated, the red LED will quickly be flash to indicate that it was
	selected.
********************************************************************************************/
void flashRed()
{
	digitalWrite(redLed,0);	//quickly turns on and turns off the red LED
	delay(250);
	digitalWrite(redLed,1);
	
}

/********************************************************************************************
void Flash Blue 
	By Isrrael Mendoza
	
	This Function will "Flash" the blue LED when called upon. For instance if "1" was the 
	random number generated, the blue LED will quickly be flash to indicate that it was
	selected.
********************************************************************************************/
void flashBlue()
{
	digitalWrite(blueLed,0);	//quickly turns on and turns off the blue LED
	delay(250);
	digitalWrite(blueLed,1);
}

/********************************************************************************************
void Flash Green 
	By Isrrael Mendoza
	
	This Function will "Flash" the green LED when called upon. For instance if "2" was the 
	random number generated, the green LED will quickly be flash to indicate that it was
	selected.
********************************************************************************************/
void flashGreen()
{
	digitalWrite(greenLed,0);	//quickly turns on and turns off the green LED
	delay(250);
	digitalWrite(greenLed,1);
}

/********************************************************************************************
 Blink Red LED
	By Isrrael Mendoza
	
	will simply "blink" the Red LED when call upon. Similar to the "Flash" Red function 
	but the difference between them is that this function turn on and turn off the LED at
	slower rate while it scans the corresponding pedal.If the pedal was pressed it'll 
	return from the function
********************************************************************************************/
void blinkRedLed()
{
	printf("Blink Red LED\n");
	int i;							
	digitalWrite (redLed, 1);
	for (i=0;i<25;i++)			//Loop that will consisting blink the LED and simutanlously
	{							//check the firstPedalFlag to see if it was pressed
		if (firstPedalFlag)
		{						//this loop blinks the LED Every 0.5 seconds 
			break;
		}
		smartDelay (20);		//smart delay is used to check the status of the pedal
		if (firstPedalFlag)
		{
			break;
		}
	}

	if (firstPedalFlag)
	{
		return;
	}

	digitalWrite (redLed,0);
	for (i=0;i<25;i++)
	{
		if(firstPedalFlag)
		{
			break;
		}
		smartDelay (20);
		if(firstPedalFlag)
		{
			break;
		}
	}
	
	digitalWrite (redLed,1);
	
}	

/********************************************************************************************
Blink Blue LED
	By Isrrael Mendoza

	will simply blink the Blue LED when call upon. Similar to the "Flash" Blue function 
	but the difference between them is that this function turn on and turn off the LED at
	slower rate while it scans the corresponding pedal.If the pedal was pressed it'll 
	return from the function
********************************************************************************************/
void blinkBlueLed()
{
	printf("Blink Blue LED\n");
	int i;
	digitalWrite (blueLed, 1);
	for (i=0;i<25;i++)			//Loop that will consisting blink the LED and simutanlously
	{							//check the firstPedalFlag to see if it was pressed
		if (secondPedalFlag)
		{
			break;				//this loop blinks the LED Every 0.5 seconds
		}
		smartDelay (20);		//smart delay is used to check the status of the pedal
		if (secondPedalFlag)
		{
			break;
		}
	}
	
	if (firstPedalFlag)
	{
		return;
	}
	
	digitalWrite (blueLed,0);
	for (i=0;i<25;i++)
	{
		if(secondPedalFlag)
		{
			break;
		}
		smartDelay (20);
		if(secondPedalFlag)
		{
			break;
		}
	}
	
	digitalWrite (blueLed,1);
	
}	

/********************************************************************************************
Blink Green LED
	By Isrrael Mendoza

	will simply blink the Green LED when call upon. Similar to the "Flash" Blue function 
	but the difference between them is that this function turn on and turn off the LED at
	slower rate while it scans the corresponding pedal.If the pedal was pressed it'll 
	return from the function
********************************************************************************************/
void blinkGreenLed()
{
	printf("Blink Green LED\n");
	int i;
	digitalWrite (greenLed, 1);
	for (i=0;i<25;i++)			//Loop that will consisting blink the LED and simutanlously
	{							//check the firstPedalFlag to see if it was pressed
		if (thirdPedalFlag)
		{
			break;				//this loop blinks the LED Every 0.5 seconds
		}
		smartDelay (20);		//smart delay is used to check the status of the pedal
		if (thirdPedalFlag)
		{
			break;
		}
	}
	
	if (firstPedalFlag)
	{
		return;
	}
	
	digitalWrite (greenLed,0);	
	for (i=0;i<25;i++)
	{
		if (thirdPedalFlag)
		{
			break;
		}
		smartDelay (20);
		if (thirdPedalFlag)
		{
			break;
		}
	}
	digitalWrite (greenLed,1);
}	

/********************************************************************************************
Choose LED 
	By Isrrael Mendoza
	
	This function will choosing the corresponding LED to blink according to what number was 
	That was generated. If a zero was generated the corresponding LED is the RED LED. If a
	one was generated the corresponding LED is the Blue LED. And lastly, if a Two was
	generated the corresponding LED is the Green
	random number 
********************************************************************************************/
void chooseLed()
{
	switch (number)
	{
			case 0:
				flashRed();
				break;
			case 1:
				flashBlue();	//depending which number was generated, the corresponding
				break;			//LED will be flashed, thus indicating the pattern
			case 2:
				flashGreen();
				break;
	}
}	

/********************************************************************************************
Wait For First Pedal
	by Isrrael Mendoza
	
	This function waits for the First Dog Pedal (Red LED) to be pressed. If it does not get 
	pressed within 1 miutes the program will timeout and automatically go onto the next LED 
	that needs to be pressed before dispense
********************************************************************************************/

void waitForFirstPedal()
{
	int t;
	coolCount ++;
	for (t=0;t<29;t++)
	{
		printf("%d\n",t);	
		if (firstPedalFlag) 			//loop waits for a minute, while consistently
		{								//checking the first pedal status and blinking
			break;						//the corresponding LED
		}
		blinkRedLed();
		if (firstPedalFlag) 
		{
			break;
		}
		smartDelay(20);
		if (firstPedalFlag) 
		{
			break;
		}
		
	}
	if (firstPedalFlag)						//if first pedal was pressed then and if it
	{										//happens to be the third case then it will 
		printf("First Pedal Pressed\n");	//set the dispense flag high, otherwise it 
		if (coolCount == 3)			// the program will just set pedalFlag low
		{
			dispenseFlag =1;
			printf("First Pedal, High, Dispense Flag Set\n");
		}	
		t = 0;
		firstPedalFlag=0;
	}	
	else 
	{
		printf("1 Mintue Timeout Reached!\n");  //if first pedal was not pressed the 1
		if (coolCount == 3)				//minute time out was reached. If it 
		{										//happens to be the third case then it
			dispenseFlag = 1;					//will set the dispense flag high 
			printf("First Pedal, Timeout, Dispense Flag Set\n");		
		}	
		t = 0;
	}
}	

/********************************************************************************************
Wait For Second Pedal
	by Isrrael Mendoza
	
	This function waits for the Second Dog Pedal (Blue LED) to be pressed. If it does not get 
	pressed within 1 miutes the program will timeout and automatically go onto the next LED 
	that needs to be pressed before dispense
********************************************************************************************/
void waitForSecondPedal()
{
	coolCount ++;
	int t;
	for (t=0;t<29;t++)
	{
		printf("%d\n",t);
		if (secondPedalFlag) 	//loop waits for a minute, while consistently
		{						//checking the first pedal status and blinking
			break;				//the corresponding LED
		}
		blinkBlueLed();
		if (secondPedalFlag) 
		{
			break;
		}
		smartDelay(20);
		if (secondPedalFlag) 
		{
			break;
		}
	}
	if (secondPedalFlag)					//if first pedal was pressed then and if it
	{										//happens to be the third case then it will 
		printf("Second Pedal Pressed\n");	//set the dispense flag high, otherwise it
		if (coolCount == 3)			// the program will just set pedalFlag low
		{
			dispenseFlag=1;
			printf("Second Pedal, High, Dispense Flag Set\n");
		}	
		t = 0;
		secondPedalFlag=0;
	}	
	else 
	{
		printf("1 Mintue Timeout Reached!\n");	//if first pedal was not pressed the 1
		if (coolCount == 3)				//minute time out was reached. If it 
		{										//happens to be the third case then it
			dispenseFlag=1;						//will set the dispense flag high 
			printf("Second Pedal, Timeout, Dispense Flag Set\n");
		}	
		t = 0;
	}
}	

/********************************************************************************************
Wait For Second Pedal
	by Isrrael Mendoza
	
	This function waits for the Second Dog Pedal (Blue LED) to be pressed. If it does not get 
	pressed within 1 miutes the program will timeout and automatically go onto the next LED 
	that needs to be pressed before dispense
********************************************************************************************/

void waitForThirdPedal()
{
	coolCount ++;
	int t;
	for (t=0;t<29;t++)
	{
		printf("%d\n",t);
		if (thirdPedalFlag) 		//loop waits for a minute, while consistently
		{							//checking the first pedal status and blinking
			break;					//the corresponding LED
		}
		blinkGreenLed();
		if (thirdPedalFlag) 
		{
			break;
		}
		smartDelay(20);
		if (thirdPedalFlag) 
		{
			break;
		}
	}	
	if (thirdPedalFlag)						//if first pedal was pressed then and if it
	{										//happens to be the third case then it will
		printf("Third Pedal Pressed\n");	//set the dispense flag high, otherwise it
		if (coolCount == 3)			// the program will just set pedalFlag low
		{
			dispenseFlag= 1;
			printf("Third Pedal, High, Dispense Flag Set\n");
		}	
		t = 0;
		thirdPedalFlag=0;
	}	
	else 
	{
		printf("1 Mintue Timeout Reached!\n");	//if first pedal was not pressed the 1
		if (coolCount == 3)				//minute time out was reached. If it 
		{										//happens to be the third case then it
			dispenseFlag=1;						//will set the dispense flag high 
			printf("Third Pedal, Timeout, Dispense Flag Set\n");
		}	
		t = 0;
	}
}	