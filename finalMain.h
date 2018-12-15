/********************************************************************************************
Final demo main Header File (finalMain.h) 
	By: Isrrael Mendoza, Raul Rojas, and Nyron Daniels 
	
	This file will contain all of the function prototypes and constant definitions that will 
	be utilized in the main code. 
********************************************************************************************/
//MISC
void delay();
void smartDelay(int ms);
void bootSequence(void);
void pwDownSequence(void);
void setups(void);
void defaultDisplay(void);

//foodPattern setups
void foodPattern(void);
time_t t;
void flashRed();
void flashBlue();
void flashGreen();
void chooseLed();
void blinkRedLed();
void blinkBlueLed();
void blinkGreenLed();
void waitForFirstPedal();
void waitForSecondPedal();
void waitForThirdPedal();

//finalScheduler (setMode) prototypes
void timeSet(void);
void timesPerDay(void);
void timeBetweenDisp (void);
void setMode(void);
int numberPressed(int buttonPressed);

//finalTime prototypes.
int getTimeH(void);
int getTimeHMilit(void);
int getTimeM(void);
int getTimeS(void);
void dispenseCheck(void);
void updateTimer(void);
//finalFileIO prototypes
void saveHour(void);
void saveMin(void);
void getHour(void);
void getMin(void);
void saveAP(void);
void getAP(void);
void savePerDay(void);
void getPerDay(void);
void saveTimeBetween(void);
void getTimeBetween(void);


//Servo Motor Headers
#define motorSig 18
#define motorStatLed 14
#define hes 13

void motorMove(int value);
void motorDispense(void);
void motorUnstall(void);
void vibMove(void);

//ADC HEADERS
int getMass();
int tare();
void updateWeight(void);
int avgWeight(void);

#define PD_SCK 7
#define DOUT 12

//RANGING MODULE HEADERS
int getCM();
void foodCheck(void);


#define TRIGPIN 4
#define ECHOPIN 6

//LCD HEADERS
int lcdTest(void);
#define LCD_RS 108	//defining constants
#define LCD_E 109
#define LCD_D4 110
#define LCD_D5 111
#define LCD_D6 112
#define LCD_D7 113

//SEVEN SEGMENT HEADERS
void segWrite(int Digit,int Data);
void segClear(void);

#define zero  0x3F
#define one  0x06
#define two  0x5B
#define three  0x4F
#define four  0x66
#define five  0x6D
#define six  0x7D
#define seven  0x07
#define eight  0x7F
#define nine  0x67
#define A  0x77
#define B  0x7c
#define C  0x39
#define D  0x5E
#define E  0x79
#define F  0x71
#define decimal  0x77
#define colon  0x10
#define digit1  0x7B
#define digit2  0x7C
#define digit3  0x7D
#define digit4  0x7E

//HALL EFFECT SENSOR HEADERS
int hesRead(void);
#define hes 13

//Keypad Setups
int scanKeypadM(void);
int scanLoop(void);
int scanKeypad(void);

#define	r1	104
#define	r2	105
#define	r3	106
#define	r4	107
#define	c1	21
#define	c2	10
#define	c3	19
#define	c4	9

//General IO Gpio pin constants
#define motorStatLed 14			
#define foodStatLed 15
#define powerSw 24
#define petModeSw 5
#define setModeSw 25
#define firstPedal 17
#define secondPedal 27
#define thirdPedal 22
#define redLed 16
#define blueLed 26
#define greenLed 20
#define resetSw 23

