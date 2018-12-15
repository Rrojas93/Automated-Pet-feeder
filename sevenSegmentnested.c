/********************************************************************************************
*    sevenSegmentnested.c
*--------------------------------------------------------------------------------------------
*	By: Nyron Daniel
*	Group 4: Automatic Pet Feeder
*	Group Members: Raul Rojas, Nyron Daniel & Isrreal Mendoza
*		   
*	This program demonstrates the ability to control and minipulate the 4 digit 7 
*	segment of our Automatic Pet Feeder. When executed this program will begin to 
*	count from 0 to 9 on each digit of the display and will then be cleared. It will
*	continue to cycle through the count after each clear until the program is terminated.
********************************************************************************************/

#include <stdio.h>
#include <wiringPiI2C.h>
#include <wiringPi.h>
#include "finalMain.h"
/*
//declaring function prototypes 
void delay();	
void segWrite(int Digit,int Data);
void segClear(void);
void sevenSegmentTest (void);
*/
extern int fd;	//including variables from other files 

/********************************************************************************************
	void sevenSegmentTest (void)
	
	This function tests the functionality of the 4 digit 7 segment display. once this 
	function is called it stays in an infinate while loop. 
********************************************************************************************/
void sevenSegmentTest (void)
{
/*	
  wiringPiSetupGpio();
 if((fd=wiringPiI2CSetup(0x71)))//Intializing the seven segment on the I2C bus.
 {

 }
  */
	//while(1)
	//{
		segWrite (0,0);//Displays a zero on the left most digit (digit1) of the seven segment.
		segWrite (1,0);//Displays a zero on (digit2) of the seven segment.
		segWrite (2,0);//Displays a zero on (digit3) of the seven segment.
		segWrite (3,0);//Displays a zero on (digit4) of the seven segment.
		wiringPiI2CWriteReg8 (fd,decimal,colon);//displays the colon on the seven segment.	 
		delay(1000);
				
		segWrite (0,1);//Displays a one on the left most digit (digit1) of the seven segment.
		segWrite (1,1);
		segWrite (2,1);
		segWrite (3,1);
		wiringPiI2CWriteReg8 (fd,decimal,colon);	 
		delay(1000);

		segWrite (0,2);
		segWrite (1,2);
		segWrite (2,2);
		segWrite (3,2);
		wiringPiI2CWriteReg8 (fd,decimal,colon);	 
		delay(1000);

		segWrite (0,3);
		segWrite (1,3);
		segWrite (2,3);
		segWrite (3,3);
		wiringPiI2CWriteReg8 (fd,decimal,colon);	 
		delay(1000);


		segWrite (0,4);
		segWrite (1,4);
		segWrite (2,4);
		segWrite (3,4);
		wiringPiI2CWriteReg8 (fd,decimal,colon);	 
		delay(1000);

		segWrite (0,5);
		segWrite (1,5);
		segWrite (2,5);
		segWrite (3,5);
		wiringPiI2CWriteReg8 (fd,decimal,colon);	 
		delay(1000);

		segWrite (0,6);
		segWrite (1,6);
		segWrite (2,6);
		segWrite (3,6);
		wiringPiI2CWriteReg8 (fd,decimal,colon);	 
		delay(1000);

		segWrite (0,7);
		segWrite (1,7);
		segWrite (2,7);
		segWrite (3,7);
		wiringPiI2CWriteReg8 (fd,decimal,colon);	 
		delay(1000);

		segWrite (0,8);
		segWrite (1,8);
		segWrite (2,8);
		segWrite (3,8);
		wiringPiI2CWriteReg8 (fd,decimal,colon);	 
		delay(1000);

		segWrite (0,9);
		segWrite (1,9);
		segWrite (2,9);
		segWrite (3,9);
		wiringPiI2CWriteReg8 (fd,decimal,colon);	 
		delay(1000);
		segClear ();//Call a function that clears the seven segment.
	//}	
//return 0;
}
	
/*******************************************************************************************
*(segWrite) Write to the segment Function
* By: Nyron Daniel
*
* This function checks for the key pressed on the keypad and then displays the pressed digit
* on the four digit seven segment.
*******************************************************************************************/

void segWrite(int Digit,int Data)
{
 switch (Digit)//Checks to see what digit is selected 
	{
		 case 0: //In this case the left most digit (digit1) was selected.
			switch (Data) //Checks to see what number will be displayed. 
		{		case 0:
					wiringPiI2CWriteReg8 (fd,digit1,zero);//Writes a zero to digit 1.
					printf("Digit 1 - Number 0 was selected\n");
					break;
				case 1:
					wiringPiI2CWriteReg8 (fd,digit1,one);//Writes a one to digit 1.
					printf("Digit 1 - Number 1 was selected\n");
					break;
				case 2:
					wiringPiI2CWriteReg8 (fd,digit1,two);//Writes a two to digit 1.
					printf("Digit 1 - Number 2 was selected\n");
					break;
				case 3:
					wiringPiI2CWriteReg8 (fd,digit1,three);//Writes a three to digit 1.
					printf("Digit 1 - Number 3 was selected\n");
					break;
				case 4:
					wiringPiI2CWriteReg8 (fd,digit1,four);//Writes a four to digit 1.
					printf("Digit 1 - Number 4 was selected\n");
					break;
				case 5:
					wiringPiI2CWriteReg8 (fd,digit1,five);//Writes a five to digit 1.
					printf("Digit 1 - Number 5 was selected\n");
					break;
				case 6:
					wiringPiI2CWriteReg8 (fd,digit1,six);//Writes a six to digit 1.
					printf("Digit 1 - Number 6 was selected\n");
					break;
				case 7:
					wiringPiI2CWriteReg8 (fd,digit1,seven);//Writes a seven to digit 1.
					printf("Digit 1 - Number 7 was selected\n");
					break;
				case 8:
					wiringPiI2CWriteReg8 (fd,digit1,eight);//Writes an eight to digit 1.
					printf("Digit 1 - Number 8 was selected\n");
					break;
				case 9:
					wiringPiI2CWriteReg8 (fd,digit1,nine);//Writes a nine to digit 1.
					printf("Digit 1 - Number 9 was selected\n");
					break;
				default:
					printf("Invalid number was selected\n");

	    }

		break;
		 case 1:  // In this case the second digit from the left was selected.
			switch (Data) //Checks to see what number needs to be displayed. 
		{		case 0:
					wiringPiI2CWriteReg8 (fd,digit2,zero);//Writes a zero to digit 2.
					printf("Digit 2 - Number 0 was selected\n");
					break;
				case 1:
					wiringPiI2CWriteReg8 (fd,digit2,one);
					printf("Digit 2 - Number 1 was selected\n");
					break;
				case 2:
					wiringPiI2CWriteReg8 (fd,digit2,two);
					printf("Digit 2 - Number 2 was selected\n");
					break;
				case 3:
					wiringPiI2CWriteReg8 (fd,digit2,three);
					printf("Digit 2 - Number 3 was selected\n");
					break;
				case 4:
					wiringPiI2CWriteReg8 (fd,digit2,four);
					printf("Digit 2 - Number 4 was selected\n");
					break;
				case 5:
					wiringPiI2CWriteReg8 (fd,digit2,five);
					printf("Digit 2 - Number 5 was selected\n");
					break;
				case 6:
					wiringPiI2CWriteReg8 (fd,digit2,six);
					printf("Digit 2 - Number 6 was selected\n");
					break;
				case 7:
					wiringPiI2CWriteReg8 (fd,digit2,seven);
					printf("Digit 2 - Number 7 was selected\n");
					break;
				case 8:
					wiringPiI2CWriteReg8 (fd,digit2,eight);
					printf("Digit 2 - Number 8 was selected\n");
					break;
				case 9:
					wiringPiI2CWriteReg8 (fd,digit2,nine);
					printf("Digit 2 - Number 9 was selected\n");
					break;
				default:
					printf("Invalid number was selected\n");
				
	    }
			
		break;
		case 2://In this case the third from the left digit is selected.
			switch (Data) 
		{		case 0:
					wiringPiI2CWriteReg8 (fd,digit3,zero);
					printf("Digit 3 - Number 0 was selected\n");
					break;
				case 1:
					wiringPiI2CWriteReg8 (fd,digit3,one);
					printf("Digit 3 - Number 1 was selected\n");
					break;
				case 2:
					wiringPiI2CWriteReg8 (fd,digit3,two);
					printf("Digit 3 - Number 2 was selected\n");
					break;
				case 3:
					wiringPiI2CWriteReg8 (fd,digit3,three);
					printf("Digit 3 - Number 3 was selected\n");
					break;
				case 4:
					wiringPiI2CWriteReg8 (fd,digit3,four);
					printf("Digit 3 - Number 4 was selected\n");
					break;
				case 5:
					wiringPiI2CWriteReg8 (fd,digit3,five);
					printf("Digit 3 - Number 5 was selected\n");
					break;
				case 6:
					wiringPiI2CWriteReg8 (fd,digit3,six);
					printf("Digit 3 - Number 6 was selected\n");
					break;
				case 7:
					wiringPiI2CWriteReg8 (fd,digit3,seven);
					printf("Digit 3 - Number 7 was selected\n");
					break;
				case 8:
					wiringPiI2CWriteReg8 (fd,digit3,eight);
					printf("Digit 3 - Number 8 was selected\n");
					break;
				case 9:
					wiringPiI2CWriteReg8 (fd,digit3,nine);
					printf("Digit 3 - Number 9 was selected\n");
					break;
				default:
					printf("Invalid number was selected\n");
		}	
		break;
		case 3: //In this case the fourth digit is selected.
			switch (Data) 
		{		case 0:
					wiringPiI2CWriteReg8 (fd,digit4,zero);
					printf("Digit 4 - Number 0 was selected\n");
					break;
				case 1:
					wiringPiI2CWriteReg8 (fd,digit4,one);
					printf("Digit 4 - Number 1 was selected\n");
					break;
				case 2:
					wiringPiI2CWriteReg8 (fd,digit4,two);
					printf("Digit 4 - Number 2 was selected\n");
					break;
				case 3:
					wiringPiI2CWriteReg8 (fd,digit4,three);
					printf("Digit 4 - Number 3 was selected\n");
					break;
				case 4:
					wiringPiI2CWriteReg8 (fd,digit4,four);
					printf("Digit 4 - Number 4 was selected\n");
					break;
				case 5:
					wiringPiI2CWriteReg8 (fd,digit4,five);
					printf("Digit 4 - Number 5 was selected\n");
					break;
				case 6:
					wiringPiI2CWriteReg8 (fd,digit4,six);
					printf("Digit 4 - Number 6 was selected\n");
					break;
				case 7:
					wiringPiI2CWriteReg8 (fd,digit4,seven);
					printf("Digit 4 - Number 7 was selected\n");
					break;
				case 8:
					wiringPiI2CWriteReg8 (fd,digit4,eight);
					printf("Digit 4 - Number 8 was selected\n");
					break;
				case 9:
					wiringPiI2CWriteReg8 (fd,digit4,nine);
					printf("Digit 4 - Number 9 was selected\n");
					break;
				default:
					printf("Invalid number was selected\n");

			    }

	}
}
/*******************************************************************************************
*(segClear) Clears the segment Function
* By: Nyron Daniel
*
* This function clears the four digit seven segment and sets the cursor at the left most
* digit (Digit1)
*******************************************************************************************/

void segClear (void) 
{
	wiringPiI2CWrite (fd,0x76); //Clears the seven segment.
	printf("Cleared Screen!\n");
	//delay(500);
	
}
/******************************************************************************************/
