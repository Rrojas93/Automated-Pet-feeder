/********************************************************************************************
	scanKeypad.c
---------------------------------------------------------------------------------------------
Objective: This program scans the keypad for any button pressed.
Things of note:
GPIO assignments:
		ROWS:
		r1 = 104
		r2 = 105
		r3 = 106
		r4 = 107

		Columns:
		c1 = 21
		c2 = 10
		c3 = 19
		c4 = 9

		integer returned from this function corresponds to the number as shown below
		within the button. If no buttn is pressed the function returns 0.

		+----+----+----+----+
		|  1 |  2 |  3 |  4 | row1
		+----+----+----+----+
		|  5 |  6 |  7 |  8 | row2
		+----+----|----+----+
		|  9 | 10 | 11 | 12 | row3
		+----+----+----+----+
		| 13 | 14 | 15 | 16 | row4
		+----+----+----+----+
		col1 col2 col3 col4

********************************************************************************************/
#include <stdio.h>
#include <wiringPi.h>
#include <mcp23017.h>
#include "finalMain.h"

/*
int r1 = 104;	//setting up constant variable to represent gpio pin numbers.
int r2 = 105;
int r3 = 106;
int r4 = 107;

int c1 = 21;
int c2 = 10;
int c3 = 19;
int c4 = 9;
*/

int rowPressed =0;	//set these as global so that the main and the scan loop can access/modify
int colPressed =0;

//extern int lcd;

//void delay();
//int scanKeypadM(void);
//int scanLoop(void);
//int scanKeypad(void);
//void segWrite(int Digit,int Data);
//void segClear(void);


int scanKeypad(void)
{
	//wiringPiSetupGpio();	//required wiringPi library set up function
	//mcp23017Setup(100, 0x20); //required mcp23017 extender set up function.
/*
	int i;
	for (i = 0; i < 4; i++)		//setting up pin modes.
	{
		//delay(20);
		//if(i<4)
		//{
			pinMode (104+i, OUTPUT);	//all rows = outputs, all columns = inputs.
		//}
		//else
		//{
		//	pinMode (100+i, INPUT);
		//}
	}
	pinMode(9, INPUT);
	pinMode(10, INPUT);
	pinMode(19, INPUT);
	pinMode(21, INPUT);
*/
	//printf("program started. \n");
	//while(1)
	//{
		//delay(20);
		//printf("entered while 1 loop\n");
		int button = scanKeypadM();
		if(button != 0)
		{
			//printf("you Pressed: %d \n", button);
			colPressed =0;
			rowPressed = 0;
		}
		else
		{
			//printf("nothing pressed\n");
		}
//		delay(100);
	//}
	return button;
}

/********************************************************************************************
	int scanKeypad(void)

	This function scans the keypad via the gpio extender mcp 23017.
********************************************************************************************/
int scanKeypadM(void)
{
	//printf("entered scanKeypad\n");
	//delay(100);

	/*
	wiringPiSetupGpio();	//required wiringPi library set up function
	//mcp23017Setup(100, 0x20); //required mcp23017 extender set up function.
	
	int i;
	for (i = 0; i < 8; i++)		//setting up pin modes.
	{
		if(i<4)
		{
			pinMode (19+i, OUTPUT);	//all rows = outputs, all columns = inputs.
		}
		else
		{			
			pinMode (19+i, INPUT);
		}
	}
	*/
	if (scanLoop())	//if a row and column is press, return the button pressed to caller
	{
		int buttonPressed = colPressed + ((rowPressed-1)*4);

		return buttonPressed;
	}
	else
	{
		return 0;
	}

}


/********************************************************************************************
	int scanLoop(void)
	
	This function performs a nested loop to scan both rows and columns. If a button is 
	pressed, it will store the column and row that was pressed in the global variables 
	rowPressed, and colPressed.
********************************************************************************************/
int scanLoop(void)
{
//	printf("entered scanLoop\n");
//	delay(100);
	
	int r;
	//int row;
	for(r = 1; r<5; r++)	//Loop to decide which row to check.
	{

		//delay(20);
		//printf(" row check: %d \n",r);
		digitalWrite(103+r, HIGH);	//set row "r" high. 
		delay(5);	//debounce delay
		int c;
		int col;
		for(c = 1; c < 5; c++)	//Loop to scan columns
		{
			if(c==1)
			{
				col = 21;
			}
			else if(c==2)
			{
				col = 10;
			}
			else if(c==3)
			{
				col = 19;
			}
			else if(c==4)
			{
				col = 9;
			}

			//delay(20);
//			printf("col check: %d \n",c);
			if (digitalRead(col))	//if column is high, save the row and column pressed.
			{
				//delay(20);
				rowPressed = r;
				colPressed = c;
//				printf("rowPressed: %d \n",r);
//				printf("colPressed: %d \n",c);
				//delay(20);
				digitalWrite(103+r, LOW);
				//delay(20);
				break;
			}
			//else
			//{}
		}
		if (colPressed > 0)
		{
			//delay(20);
			digitalWrite(103+r, LOW);
			//delay(20);
			return rowPressed;
		}
		//delay(20);
		digitalWrite(103+r, LOW);
		//delay(20);
	}
	return 0;
}


//int newScan()
