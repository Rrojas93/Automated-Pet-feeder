#include <stdio.h>
#include <wiringPi.h>
#include "finalMain.h"

extern int petModeFlag;
extern int setModeFlag;
int petModeStorage = 0;

int hour;
int min;

extern int hourTenths;
extern int hourOnes;
extern int minTenths;
extern int minOnes;
extern char ap;
extern int perDay;
extern int timeBetweenHTenths;
extern int timeBetweenHOnes;
extern int timeBetweenMTenths;
extern int timeBetweenMOnes;

FILE *hourTenthsFile;
FILE *hourOnesFile;
FILE *minTenthsFile;
FILE *minOnesFile;
FILE *apFile;
FILE *perDayFile;
FILE *timeBetweenHTenthsFile;
FILE *timeBetweenHOnesFile;
FILE *timeBetweenMTenthsFile;
FILE *timeBetweenMOnesFile;

void saveHour(void)
{
	//hour = (hourTenths * 10) + hourOnes;
	//printf("hour going in file: %d \n", hour);
	//min = (minuteTenths * 10) + minuteOnes;
	
	
	//FILE *hourTenthsFile; 
	
	hourTenthsFile = fopen("/home/pi/DigitalThree/final/userSettings/hourTenthsFile.txt", "w+");
	printf("updating hourTenthsFile \n");
	fprintf(hourTenthsFile, "%d", hourTenths);
	fclose(hourTenthsFile);
	printf("finished writing hourThenthsFile\n");
	
	delay(10);
	hourOnesFile = fopen("/home/pi/DigitalThree/final/userSettings/hourOnesFile.txt", "w+");
	printf("updating hourOnesFile \n");
	fprintf(hourOnesFile, "%d", hourOnes);
	fclose(hourOnesFile);
	printf("finished writing hourOnesFile \n");
	return; 
}

void saveMin(void)
{
	minTenthsFile = fopen("/home/pi/DigitalThree/final/userSettings/minTenthsFile.txt", "w+");
	printf("updating minTenthsFile \n");
	fprintf(minTenthsFile, "%d", minTenths);
	fclose(minTenthsFile);
	printf("finished writing hourThenthsFile\n");
	
	delay(10);
	minOnesFile = fopen("/home/pi/DigitalThree/final/userSettings/minOnesFile.txt", "w+");
	printf("updating minOnesFile \n");
	fprintf(minOnesFile, "%d", minOnes);
	fclose(minOnesFile);
	printf("finished writing minOnesFile \n");
	return; 
}

void getHour(void)
{
	hourTenthsFile = fopen("/home/pi/DigitalThree/final/userSettings/hourTenthsFile.txt", "r");
	//printf("Reading hourTenthsFile \n");
	hourTenths = fgetc(hourTenthsFile);
	fclose(hourTenthsFile);
	hourTenths = hourTenths - 48;
	//printf("hour from file in buffer is: %d \n", hourTenths);
	
	hourOnesFile = fopen("/home/pi/DigitalThree/final/userSettings/hourOnesFile.txt", "r");
	//printf("Reading hourOnesFile \n");
	hourOnes = fgetc(hourOnesFile);
	fclose(hourOnesFile);
	hourOnes = hourOnes - 48;
	//printf("hour from file in buffer is: %d \n", hourOnes);
	
	return; 
}

void getMin(void)
{
	minTenthsFile = fopen("/home/pi/DigitalThree/final/userSettings/minTenthsFile.txt", "r");
	//printf("Reading minTenthsFile \n");
	minTenths = fgetc(minTenthsFile);
	fclose(minTenthsFile);
	minTenths = minTenths - 48;
	//printf("hour from file in buffer is: %d \n", minTenths);
	
	minOnesFile = fopen("/home/pi/DigitalThree/final/userSettings/minOnesFile.txt", "r");
	//printf("Reading minOnesFile \n");
	minOnes = fgetc(minOnesFile);
	fclose(minOnesFile);
	minOnes = minOnes - 48;
	//printf("hour from file in buffer is: %d \n", minOnes);
	
	return; 
}

void saveAP(void)
{
	apFile = fopen("/home/pi/DigitalThree/final/userSettings/apFile.txt", "w+");
	printf("updating apFile \n");
	fprintf(apFile, "%c", ap);
	fclose(apFile);
	printf("finished writing apFile \n");
	return;
}

void getAP(void)
{
	apFile = fopen("/home/pi/DigitalThree/final/userSettings/apFile.txt", "r");
	printf("Reading apFile \n");
	ap = fgetc(apFile);
	fclose(apFile);
	printf("Character from apFile is: %c \n", ap);
}

void savePerDay(void)
{
	perDayFile = fopen("/home/pi/DigitalThree/final/userSettings/perDayFile.txt", "w+");
	printf("updating perDayFile \n");
	fprintf(perDayFile, "%d", perDay);
	fclose(perDayFile);
	printf("finished writing perDayFile.\n");
	return;
}

void getPerDay(void)
{
	perDayFile = fopen("/home/pi/DigitalThree/final/userSettings/perDayFile.txt", "r");
	printf("Reading perDayFile \n");
	perDay = fgetc(perDayFile);
	fclose(perDayFile);
	perDay = perDay - 48;
	printf("perDay value from file is: %d \n", perDay);
	return;
}

void saveTimeBetween(void)
{
	timeBetweenHTenthsFile = fopen("/home/pi/DigitalThree/final/userSettings/timeBetweenHTenthsFile.txt", "w+");
	//printf("updating timeBetweenHTenthsFile \n");
	fprintf(timeBetweenHTenthsFile, "%d", timeBetweenHTenths);
	fclose(timeBetweenHTenthsFile);
	//printf("finished writing timeBetweenHTenthsFile.\n");
	
	timeBetweenHOnesFile = fopen("/home/pi/DigitalThree/final/userSettings/timeBetweenHOnesFile.txt", "w+");
	//printf("updating timeBetweenHOnesFile \n");
	fprintf(timeBetweenHOnesFile, "%d", timeBetweenHOnes);
	fclose(timeBetweenHOnesFile);
	//printf("finished writing timeBetweenHOnesFile.\n");
	
	timeBetweenMTenthsFile = fopen("/home/pi/DigitalThree/final/userSettings/timeBetweenMTenthsFile.txt", "w+");
	//printf("updating timeBetweenMTenthsFile \n");
	fprintf(timeBetweenMTenthsFile, "%d", timeBetweenMTenths);
	fclose(timeBetweenMTenthsFile);
	//printf("finished writing timeBetweenMTenthsFile.\n");
	
	timeBetweenMOnesFile = fopen("/home/pi/DigitalThree/final/userSettings/timeBetweenMOnesFile.txt", "w+");
	//printf("updating timeBetweenMOnesFile \n");
	fprintf(timeBetweenMOnesFile, "%d", timeBetweenMOnes);
	fclose(timeBetweenMOnesFile);
	//printf("finished writing timeBetweenMOnesFile.\n");
	return;
}

void getTimeBetween(void)
{
	timeBetweenHTenthsFile = fopen("/home/pi/DigitalThree/final/userSettings/timeBetweenHTenthsFile.txt", "r");
	//printf("Reading timeBetweenHTenthsFile \n");
	timeBetweenHTenths = fgetc(timeBetweenHTenthsFile);
	fclose(timeBetweenHTenthsFile);
	timeBetweenHTenths = timeBetweenHTenths - 48;
	//printf("timeBetweenHTenths value from file is: %d \n", timeBetweenHTenths);
	
	timeBetweenHOnesFile = fopen("/home/pi/DigitalThree/final/userSettings/timeBetweenHOnesFile.txt", "r");
	//printf("Reading timeBetweenHOnesFile \n");
	timeBetweenHOnes = fgetc(timeBetweenHOnesFile);
	fclose(timeBetweenHOnesFile);
	timeBetweenHOnes = timeBetweenHOnes - 48;
	//printf("timeBetweenHOnes value from file is: %d \n", timeBetweenHOnes);
	
	timeBetweenMTenthsFile = fopen("/home/pi/DigitalThree/final/userSettings/timeBetweenMTenthsFile.txt", "r");
	//printf("Reading timeBetweenMTenthsFile \n");
	timeBetweenMTenths = fgetc(timeBetweenMTenthsFile);
	fclose(timeBetweenMTenthsFile);
	timeBetweenMTenths = timeBetweenMTenths - 48;
	//printf("timeBetweenMTenths value from file is: %d \n", timeBetweenMTenths);
	
	timeBetweenMOnesFile = fopen("/home/pi/DigitalThree/final/userSettings/timeBetweenMOnesFile.txt", "r");
	//printf("Reading timeBetweenMOnesFile \n");
	timeBetweenMOnes = fgetc(timeBetweenMOnesFile);
	fclose(timeBetweenMOnesFile);
	timeBetweenMOnes = timeBetweenMOnes - 48;
	//printf("timeBetweenMOnes value from file is: %d \n", timeBetweenMOnes);
	return;
}
