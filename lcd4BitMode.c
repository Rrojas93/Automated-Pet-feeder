/*******************************************************************************************
*    lcd4BitMode.c
*    Group 4: Automatic Pet Feeder
*    Group Members: Raul Rojas, Nyron Daniel & Isrreal Mendoza
*		   
*    This program demonstrates the ability to control and minipulate the LCD display of our
*    Automatic Pet Feeder. When executed, this program will show the names of our group 
*    members, as well as the class name, term and our group number. The lcd will then 
*    display a set of random characters and will then be cleared.
*******************************************************************************************/
#include <wiringPi.h>
#include <lcd.h>
#include <stdio.h>
#include <mcp23017.h>

#define LCD_RS 108
#define LCD_E 109
#define LCD_D4 110
#define LCD_D5 111
#define LCD_D6 112
#define LCD_D7 113
extern int lcd;		//Handle for LCD

int lcdTest(void);

int lcdTest(void)
{
	/*
	int i;
	wiringPiSetupGpio();	//must have to coplie program
	mcp23017Setup (100, 0x20);
	printf("Rpi MCP23017 Test\n");

	for (i=0;i<6;++i)
	{
		pinMode(108+i,OUTPUT);

	}

	if ((lcd = lcdInit(2,16,4,LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7,0,0,0,0)))
	{
		printf("lcd init faild!\n");
		return -1;

	}
	*/

	lcdPosition(lcd,0,0);			//Postion cursor on the first line in the first column
	lcdPuts(lcd,"Nyron Daniel");		//prints our names, class, term, and group number
	delay(1000);
	lcdPosition(lcd,0,1);
	lcdPuts(lcd,"Raul Rojas");
	delay(1000);
	lcdPosition(lcd,0,0);
	lcdPuts(lcd,"Isrrael Mendoza");
	delay(1000);
	lcdPosition(lcd,0,0);
	lcdPuts(lcd,"Digital 3-Group4");
	lcdPosition(lcd,0,1);
	lcdPuts(lcd,"Spring 2016");
	delay(2000);
	lcdClear(lcd);				//clears LCD

	/*
	lcdPosition(lcd,0,0);
	lcdPuts(lcd,"a1!B2@c3#D4$e5%F6^g7&H8*i9(J0)k");
	delay(1000);
	lcdPuts(lcd,"-L+m=N_o<P>q?R/s.T,u`V;w:X#y|z}");
	delay(1000);
		

	lcdClear(lcd);
	
	delay(1000);
	lcdPosition(lcd,1,0);
	lcdPuts(lcd,"Happy Pi Day!!");
	lcdPosition(lcd,3,1);
	lcdPuts(lcd, "3-14-2016");
	*/
return 0;
}
