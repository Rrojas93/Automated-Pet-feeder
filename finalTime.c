#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include "finalMain.h"

time_t rawtime;
struct tm *timestruct;

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

extern int dispenseFlag;
int dispenseCount;
char timeAP;

int getTimeH(void)
{ 
	time(&rawtime);
	timestruct = gmtime(&rawtime);
	int hour = timestruct->tm_hour;
	
	
	hour = hour - 4;
	if(hour < 0)
	{
		hour = (24-abs(hour));
	}
	
	//hour = 24;
	if(hour < 12 || hour == 24)
	{
		timeAP = 'A';
	}
	else if (hour >= 12)
	{
		timeAP = 'P';
	}

	
	//printf("hour from struct: %d\n", hour);
	hour = hour%12;
	
	if (hour == 0)
	{
		hour = 12;
	}
	return hour;
}

int getTimeHMilit(void)
{ 
	time(&rawtime);
	timestruct = gmtime(&rawtime);
	int hour = timestruct->tm_hour;
	
	
	hour = hour - 4;
	if(hour < 0)
	{
		hour = (24-abs(hour));
	}
	
	
	//printf("hour from struct: %d\n", hour);
	return hour;
}

int getTimeM(void)
{
	time(&rawtime);
	timestruct = gmtime(&rawtime);
	int minute = timestruct->tm_min;
	return minute;
}

int getTimeS(void)
{
	time(&rawtime);
	timestruct = gmtime(&rawtime);
	int seconds = timestruct->tm_sec;
	return seconds;
}

int cHour;	//Current Hour
int cMin;	// Current Minutes 


void dispenseCheck(void)
{
	getHour();
	getMin();
	getAP();
	getTimeBetween();
	int sHour;	//Sceduled hour
	int sMin;	//Scheduled minutes
	int cSec;	// current seconds
	//int timeBetweenH = (timeBetweenHTenths*10)+timeBetweenHOnes;
	int timeBetweenM = (timeBetweenMTenths*10)+timeBetweenMOnes;
	printf("Time Between Minutes: %d\n", timeBetweenM);
	int scheduleH[perDay];
	int scheduleM[perDay];
	
	char sAP[perDay];
	sHour = (hourTenths * 10) + hourOnes;
	sMin = (minTenths * 10) + minOnes;
	//getTimeH();
	cHour = getTimeH();
	cMin = getTimeM();
	cSec = getTimeS();
	
	int timeBetweenH = (timeBetweenHTenths*10)+timeBetweenHOnes;
	
	if(ap == 'P' && sHour != 12)
	{
		sHour = sHour + 12;
		//printf("if PM adjust sHour: %d\n", sHour);
	}
	
	if(perDay > 1)	// && (sHour + ((perDay-1) * timeBetweenH)) < 24
	{
		int i;
		
		
		for(i = 0; i < perDay; i++)
		{
			scheduleH[i] = sHour + (i * timeBetweenH);
			scheduleM[i] = sMin + (i * timeBetweenM);
			while(scheduleM[i] >= 60)
			{
				scheduleH[i]++;
				scheduleM[i] = scheduleM[i] -60;
			}
			printf("Dispense scheduleH: I = %d:  Hour: %d Minute: %d\n", i, scheduleH[i], scheduleM[i]);
			if(scheduleH[i] < 12)
			{
				sAP[i] = 'A';
			}
			else
			{
				scheduleH[i] = scheduleH[i] - 12;
				sAP[i] = 'P';
			}
			//printf("perday is equal to 1. \n");
			printf("Current: %d:%d.%d %cM \n", cHour, cMin, cSec, timeAP);
			printf("Scheduled: %d:%d %cM \n", scheduleH[i], scheduleM[i], sAP[i]);
			if((scheduleH[i] == cHour) && (scheduleM[i] == cMin) && (sAP[i] == timeAP) && (cSec = getTimeS()) == 0)
			{
				
				while((cSec = getTimeS()) == 0)
				{
					dispenseCount = i+1;
					dispenseFlag = 1;
				}
			}
		}
		
	}
	else if(perDay <= 1)
	{
		sHour = sHour % 12;
		//printf("perday is equal to 1. \n");
		printf("Second current: %d:%d.%d %cM \n", cHour, cMin, cSec, timeAP);
		printf("Second Scheduled: %d:%d %cM \n", sHour, sMin, ap);
		if((sHour == cHour) && (sMin == cMin) && (ap == timeAP) && ((cSec = getTimeS()) < 5))
			{
				while((cSec = getTimeS()) < 5)
				{
					dispenseCount++;
					dispenseFlag = 1;
				}
			}
	}
	
	
	return;
}	//end of dispenseCheck()

void updateTimer(void)
{
	getTimeBetween();
	getPerDay();
	printf("after getTimeBetween(); timeBetweenHTenths: %d timeBetweenHOnes: %d\n", timeBetweenHTenths, timeBetweenHOnes);
	int timeBetweenH = (timeBetweenHTenths*10)+timeBetweenHOnes;
	int timeBetweenM = (timeBetweenMTenths*10)+timeBetweenMOnes;
	/*
	int schedule[perDay];
	//char sAP[perDay];
	
	int currentHrM = getTimeHMilit();
	//printf("currentHrM")
	int i;
	int sHour = (hourTenths * 10) + hourOnes;
	if(ap == 'P')
	{
		sHour = sHour + 12;
	}
	int hourToDisp;
	int minToDisp;
	printf("sHour: %d\n", sHour);
	for(i = 0; i < perDay; i++)
	{
		schedule[i] = sHour + (i * timeBetweenH);
		
	}
	
	int index;
	
	for(i = 0; i < perDay; i++)
	{
		printf("schedule [i]: %d\n i: %d", schedule[i], i);
		sHour = schedule[i];
		
		if(sHour > currentHrM)
			{	
				index = i;
				break;
			}
	}
	*/
	//char tempAP;
	int currentHrM = getTimeHMilit();
	int currentMin = getTimeM();
	int sHour = (hourTenths * 10) + hourOnes;
	int sMin = (minTenths * 10) + minOnes;
	//printf("declaration sHour: %d\n", sHour);
	
	if(ap == 'P' && sHour != 12)
	{
		sHour = sHour + 12;
		//printf("if PM adjust sHour: %d\n", sHour);
	}
	//printf("")
	int hourToDisp;
	int minToDisp;
	int i;
	int tempHour;
	int tempMin;
	printf("BEFORE FOR LOOP perDay = %d\n timeBetweenM = %d", perDay, timeBetweenM);
	//dispenseCount = 0;
	
	for(i = 0;i < perDay;i++)
	{
		printf("INSIDE FOR LOOP\n");
		//printf("i: %d sHour: %d timeBetweenH: %d", i, sHour, timeBetweenH);
		tempHour = sHour + (i * timeBetweenH);
		tempMin = sMin + (i * timeBetweenM);
		
		if(dispenseCount == perDay)
		{
			hourToDisp = (23 - currentHrM) + sHour;
			minToDisp = (60 - currentMin) + sMin;
			if(minToDisp >= 60)
			{
				minToDisp = minToDisp - 60;
				hourToDisp++;
			}
			break;
		}
		
		printf("\n tempHour: %d\ntempMin: %d \n", tempHour, tempMin);
		/*
		while(sMin >= 60)
			{
				sHour++;
				sMin = sMin -60;
			}*/
		//printf("sHour in loop: %d\n", sHour);
		//printf("UpdateTimer: sHour= %d\nupdateTimer: currentHrM= %d\nTimeBetweenH: %d\n", sHour, currentHrM, timeBetweenH);
		if(tempHour > currentHrM)
		{
			
			hourToDisp = ((tempHour - currentHrM));
			if(tempMin < currentMin)
			{
				hourToDisp--;
				minToDisp = (60 - currentMin) + tempMin;
			}
			else
			{
				hourToDisp--;
				minToDisp = tempMin-currentMin;
			}
			
			if(minToDisp >= 60)
			{
				hourToDisp++;
				minToDisp = minToDisp - 60;
			}
			//dispenseCount = i;
			break;
		}
		else if(tempHour == currentHrM && tempMin >= currentMin)
		{
			printf("DISPENSE COUNT: %d\n", dispenseCount);
			if(tempMin == currentMin && tempHour == currentHrM && dispenseCount != perDay)
			{
				hourToDisp = timeBetweenH;
				//printf("MIN TO DISPLAY WHEN TEMP BEFORE ADJUSTMENT = CURRENT: %d\n", minToDisp);
				minToDisp = (tempMin + timeBetweenM)-currentMin;
				//printf("MIN TO DISPLAY WHEN TEMP AFTER ADJUSTMENT = CURRENT: %d\n", minToDisp);
			}
			else
			{
				hourToDisp = 0;
				minToDisp = tempMin - currentMin;
			}
			//dispenseCount = i;
			break;
		}
		
		
		
	}
	
	
	
	
	
	
	//printf("timerupdate(): Hour to display: %d\n", hourToDisp);
	//printf("timerupdate(): Minute to display: %d\n", minToDisp);
	printf("timerupdate():schedule to use: %d\n", sHour);
	//printf("timerupdate():current military hour: %d\n", currentHrM);
	
	int hrToDispTenths = 0;
	int hrToDispOnes;
	while(hourToDisp > 9)
	{
		hrToDispTenths++;
		hourToDisp = hourToDisp - 10;
	}
	hrToDispOnes = hourToDisp;
	
	int minToDispTenths = 0;
	int minToDispOnes;
	while(minToDisp > 9)
	{
		minToDispTenths++;
		minToDisp = minToDisp - 10;
	}
	minToDispOnes = minToDisp;
		
	segWrite(0, hrToDispTenths);
	segWrite(1, hrToDispOnes);
	segWrite(2, minToDispTenths);
	segWrite(3, minToDispOnes);
				
	return;
}








