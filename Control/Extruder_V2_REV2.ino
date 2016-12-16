//All Menu is based off of the MenuDesign.txt file, associated in the same folder.
//Each menu has a directory, so the system knows where it is at all times.
//Each line is a state, so the screen knows how to update and what to do if the button is clicked.
//Include the screenUpdate file with this code for the full program.

//reference http://www.instructables.com/id/Easy-Arduino-Menus-for-Rotary-Encoders/step2/Code/
#include <math.h>
#include <Servo.h>
#include <AccelStepper.h>
#include <LiquidCrystal.h>
//#include <max6675.h>

//#include <PID_v1.h>


float gearBox = 2;
//gearBox:1

//_______________________________________________________________________________________
//Accelfunctionparameters
int mode = 0; //auto = 1, manual = 0
int state = 0;
int directory = 0;

unsigned long lastInputTime = 0;
int Y = 0; //For acceleration purposes
int Ydeg = 180;
int Xdeg = 1;

//int accelFactor = 25;


//_______________________________________________________________________________________
//plastic settings
int plastic = 0;
//_______________________________________________________________________________________
int desiredAugerRPM = 7;
int currentAugerRPM = 0;

int pullerRPM = 10;

int winderRPM = 9;
//______________________________________________________________________________________
//filament diameter

//int diameterSensor =;

double currentDiameter;
double desiredDiameter;

//_______________________________________________________________________________________
//auger direction and pulse pin
int dir = 47;
int pul = 45;

int augerEnable = 28;

//run count


//______________________________________________________________________________________
//puller control pins
int pullerEnable = 52;
int pullerM0 = 53;
int pullerM1 = 50;
int pullerM2 = 51;
int pullerStep = 49;
int pullerDIR = 46;
//______________________________________________________________________________________
//winder control pins
int winderEnable = 48;
int winderM0 = 31;
int winderM1 = 39;
int winderM2 = 38;
int winderStep = 36;
int winderDIR = 37;
//_____________________________________________________________________________________
//Temperature control
int heaterRelayPin = 22;


int seriesResistor = 10000;
#define thermistorNominal 100000
int temperatureNominal = 25;
int thermistorPin = A0;
#define numSamples 5
int Bcoefficient = 3950;
int samples[numSamples];
uint8_t i;
float average;
float steinhart;
//int augerTempSO = 11;
//int augerTempCS = 10;
//int augerTempCLK = 9;

//MAX6675 augerTemp(augerTempCLK, cuaugerTempCS, augerTempSO);

int heaterEnable = 0;
double desiredTemp = 0;
double currentTemp;
bool heaterState = LOW;
bool oldHeaterState = LOW;

int val;                
double temp;

//#define heatingElement = ;//relay pin

//PID heaterCore(&input, &output, &setpoin, 2,5,1, DIRECT);
//_______________________________________________________________________________________
//Servo control
Servo filamentGuide;
int filamentPos = 0;
//_______________________________________________________________________________________
//stepper definitions
AccelStepper auger(1, pul, dir);
AccelStepper puller(1, pullerStep, pullerDIR);
AccelStepper winder(1, winderStep, winderDIR);
//___________________________________________________________________________________
//ecoder setup
static int pinA = 2;
static int pinB = 3;
volatile byte aFlag = 0;
volatile byte bFlag = 0;

volatile byte encoderPos = 0;
volatile byte oldEncoderPos = 0;
volatile byte reading = 0;

const byte buttonPin = 4;
byte oldButtonState = HIGH;
const unsigned long debounceTime = 100; //milliseconds
unsigned long buttonPressTime; //when the switch last changed state
boolean buttonPressed = 0;

//__________________________________________________________________________________________
//Menu and submenu/setting declarations
//byte mode0 = 0;
//const byte modeMax = 0; //submenues we want

//_____________________________________________________________________________________
// Fan setup
int fanEnable = 0;
int fanSpeed = 255;//0-1023 analog output
int fanPin = 7;

bool bathPower = LOW;
//int bathPin = ;
//____________________________________________________________________________________
int spoolStart;
int spoolStop;
int spoolPos;
//int spoolpin; // attach servo?
//_____________________________________________________________________________________
//LCD control
LiquidCrystal lcd(44,43,42,41,40,35,34,33,32,24,26);
//________________________________________________________________________________
void setup() {
  //Serial.begin(9600);
  //analogReference(EXTERNAL);
  pinMode(fanPin, OUTPUT);
  pinMode(heaterRelayPin, OUTPUT);
 
  //______________________________________________________________________________
 //questionable sectin
  auger.setMaxSpeed(50000);
  auger.setAcceleration(500);

  puller.setMaxSpeed(10000);
  puller.setAcceleration(1000);

  winder.setMaxSpeed(10000);
  winder.setAcceleration(1000);
//_________________________________________________________________________________________
//puller set up
  pinMode(pullerEnable, OUTPUT);
  pinMode(pullerM0, OUTPUT);
  pinMode(pullerM1, OUTPUT);
  pinMode(pullerM2, OUTPUT);
  pinMode(pullerStep, OUTPUT);
  pinMode(pullerDIR, OUTPUT);

  digitalWrite(pullerEnable, HIGH);
  digitalWrite(pullerM0, HIGH);
  digitalWrite(pullerM1, HIGH);
  digitalWrite(pullerM2, HIGH);
  digitalWrite(pullerStep, LOW);
  digitalWrite(pullerDIR, LOW);
//____________________________________________________________________________
//Winder set up
  pinMode(winderEnable, OUTPUT);
  pinMode(winderM0, OUTPUT);
  pinMode(winderM1, OUTPUT);
  pinMode(winderM2, OUTPUT);
  pinMode(winderStep, OUTPUT);
  pinMode(winderDIR, OUTPUT);

  digitalWrite(winderEnable, HIGH);
  digitalWrite(winderM0, HIGH);
  digitalWrite(winderM1, HIGH);
  digitalWrite(winderM2, HIGH);
  digitalWrite(winderStep, LOW);
  digitalWrite(winderDIR, LOW);

//____________________________________________________________________________
//Auger set up
  pinMode(dir, OUTPUT);
  pinMode(pul, OUTPUT);
  pinMode(augerEnable, OUTPUT);

  digitalWrite(dir, LOW);
  digitalWrite(pul,LOW);
  digitalWrite(augerEnable, HIGH);
  
  
//______________________________________________________________________________
//Set initial values
  auger.setSpeed(200*gearBox*desiredAugerRPM);
  currentAugerRPM = desiredAugerRPM;

  puller.setSpeed(200*pullerRPM);

  winder.setSpeed(200*winderRPM);
//_________________________________________________________________________________
//Servo setup
  filamentGuide.attach(12);
//__________________________________________________________________________________
  //currentTemp = augerTemp.readCelsius();


//________________________________________________________________________________
//User interface start
  lcd.begin(16,2);

  screenUpdate(0,currentTemp);

  pinMode(pinA, INPUT_PULLUP);
  pinMode(pinB, INPUT_PULLUP);
  attachInterrupt(0, PinA, RISING);
  attachInterrupt(1, PinB, RISING);
  pinMode(buttonPin, INPUT_PULLUP);
//user interface end

//Setup ends
//_________________________________________________________________________________
  delay(1000); //for MAX to settle
}
//________________________________________________________________________________



void loop() {
  

  
  //currentTemp = augerTemp.readCelsius();
  // put your main code here, to run repeatedly
  rotaryMenu();
/*
 for (i = 0; i < numSamples; i++) {
    samples[i] = analogRead(thermistorPin);
    auger.runSpeed();
    puller.runSpeed();
    winder.runSpeed();
  }
  
  average = 0;
  for (i=0; i< numSamples; i++) {
    average += samples[i];
    
    auger.runSpeed();
    puller.runSpeed();
    winder.runSpeed();
  }
  average /= numSamples;
  average = 1023 / average - 1;
  average = seriesResistor / average;
  
  steinhart = average / thermistorNominal;
  steinhart = log(steinhart);
  steinhart = steinhart / Bcoefficient;
  steinhart = steinhart + 1 / (temperatureNominal + 273.15);
  steinhart = 1.0/steinhart;
  steinhart = steinhart - 273.15;
  
  currentTemp = steinhart;
 
 */\
val = analogRead(0);
currentTemp = Thermistor(val);

 
 //currentTemp = analogRead(thermistorPin);
 
  auger.runSpeed();
  puller.runSpeed();
  winder.runSpeed();
  //diameterMonitor
  
  //ServoControl
  //if switchpressed, increment by diameter width
  
//menu screen timer
//  if ((directory != 0) && (millis () - lastInputTime >= 5000)){
//    infoScreen();
//    directory = 0;
//    encoderPos = 0;
//   }
  if ((directory == 0) && ((millis() - lastInputTime) >= 1000)) {
    screenUpdate(0, currentTemp);    
    
  }
  
  temperatureControl(heaterEnable, desiredTemp, heaterState, currentTemp);
  //diameterControl
  
} 


//________________________________________________________________________________
//Rotary encoder interrupt service routine for one encoder pins
void PinA(){
  cli();
  reading = PINE & 0x30;
  if (reading == B00110000 && aFlag){
    encoderPos --;
    bFlag = 0;
    aFlag = 0;
  }
  else if (reading == B00010000) bFlag = 1;
  sei();
}

void PinB(){
  cli();
  reading = PINE & 0x30;
  if (reading == B00110000 && bFlag){
    encoderPos ++;
    bFlag = 0;
    aFlag = 0;
  }
  else if (reading == B00100000) aFlag = 1;
  sei();
}
//_______________________________________________________________________________________
//_______________________________________________________________________________________
//_______________________________________________________________________________________
//Functions menu below
/*
//Plastic settings
void loadPlasticSettings() {
  if (plastic == 0) {  //no selection
        lcd.clear;
  }
  
  if (plastic == 1) { //PLA
    desiredAugerRPM = 5;
    desiredTemp = 140;  
  }
  
  if (plastic == 2) { //RecycledPLA
    desiredAugerRPM = 5;
    desiredTemp = 140;    
  }
  
  if (plastic == 3) { //RecycledABS
    desiredAugerRPM = 5;
    desiredTemp = 180;
  }
  
  if (plastic == 4) { //Recycled TPE
    desiredAugerRPM = 5;
    desiredTemp = 170;
  }
  
}
*/
/*
void augerAcceleration(int currentaugerRPM, int desiredAugerRPM, int accelFactor) {
    
    int X = 1/((currentAugerRPM*gearBox)*400);
  {
    //was 44
    
    int del = 1/((desiredAugerRPM*gearBox)*400);
    
    while (X != del){
      digitalWrite(pul, HIGH);
      delayMicroseconds(X);
      digitalWrite(pul, LOW);
      delayMicroseconds(X);
         if (Y != accelFactor){
          Y = Y + 1;
          }
          else {
          Y = 0;
          
            if (X > del){
              X = X - 1;
            }
            else {
              X = X + 1;
            }
      }
  }
  auger.setSpeed(desiredAugerRPM*gearBox*200);
  infoScreen(currentTemp);
}
*/
double Thermistor (int RawADC) {
  double temp;
  
  auger.runSpeed();
  puller.runSpeed();
  winder.runSpeed();
  
  temp = log(10000.0*((1024.0/RawADC-1)));
  temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * temp * temp ))* temp );
 temp = temp - 273.15;          
 //temp = (temp * 9.0)/ 5.0 + 32.0; 
  auger.runSpeed();
  puller.runSpeed();
  winder.runSpeed();
  
 return temp;
}
//_________________________________________________________________________________________________  


void temperatureControl(int heaterEnable, int desiredTemp, bool heaterState, double currentTemp) {
  
  auger.runSpeed();
  puller.runSpeed();
  winder.runSpeed();
  
  if ((heaterEnable == 1) && (currentTemp < (desiredTemp - 2))){
    //currentTemp = augerTemp.readCelsius();
    
    //auger.runSpeed();
    //winder.runSpeed();
    //puller.runSpeed();
    
      //digitalWrite(heaterRelayPin, HIGH);
      heaterState = HIGH;
      //auger.runSpeed();
      //winder.runSpeed();
      //puller.runSpeed();
  }
   else {
      //digitalWrite(heaterRelayPin, LOW);
      heaterState = LOW;
      //auger.runSpeed();
      //winder.runSpeed();
      //puller.runSpeed();
    }
    if (heaterState != oldHeaterState) {
       
     auger.runSpeed();
     puller.runSpeed();
     winder.runSpeed();
      
      if (heaterState == HIGH) {
        digitalWrite(heaterRelayPin, HIGH);
      }
      else {
        digitalWrite(heaterRelayPin, LOW);
      }
      oldHeaterState = heaterState;
    }
    
}
  
void fanControl(int fanEnable, int fanSpeed) {
  if (fanEnable == 1) {
    analogWrite(fanPin, fanSpeed);
  }
  else {
    analogWrite(fanPin, 0);
  }
}

/* 
void diameterControl(double desiredDiameter) {
  currentDiameter = analogRead(diameterPin);
  //PID functions
} 

  //______________________________________________________________________________________________-
  void augerStop() {
    auger.setSpeed(0);
  }
  //_____________________________________________________________________________________________________
  void pullerStop() {
    puller.setSpeed(0);
  }
*/  
  //_______________________________________________________________________________________________________
  //_-_-_-_-_-_-_-_-_-_-_-_-_-_
  //LCD and selector Settings
void rotaryMenu(){
  if(oldEncoderPos != encoderPos){
//__________________________
// Menu Navigation
      
      if (directory == 0){
        directory = 1;
        switch (encoderPos) {
          case (1) :
            state = 1;
            directory = 1;
            break;
            case (2) :
                state = 2;
                break;
              case (3) :
                state = 49;
                break;  
              case (4) :
                state = 1;
                encoderPos = 1;
                break;
              case (0) :
                encoderPos = 3;
                state = 49;
                break;
        }
        
      }
      if (directory == 1) {
        switch (encoderPos) {
          case (1) :
            state = 1;
            break;
            case (2) :
                state = 2;
                break;
              case (3) :
                state = 49;
                break;  
              case (4) :
                state = 1;
                encoderPos = 1;
                break;
              case (0) :
                encoderPos = 3;
                state = 49;
                break;
        }
      }
      /*   
         else if (directory == 2) {
           switch (encoderPos) {
             case (0) :
               state = 50;
               break;
             case (1) :
              state = 51;
              break;
            
            case (2) :
              state = 57;
              break;
            
            case (3) :
              state = 58;
              break;
            
            case (4) :
              state = 50;
              encoderPos = 0;
              break;
            
            case (255) :
              state = 58;
              encoderPos = 3;
              break;
            
           }
         }
        */ 
        else if (directory == 3) {
          switch(encoderPos) {
            case (1) : //
              state = 3;
              break;
            
            case (2) :
              state = 4;
              break;
            
            case (3) :
              state = 14; //servo
              break;
            
            case (4) :
              state = 22;
              break;
            
            case (5) : // auger
              state = 28;
              break;
            
            case (6) : //winder
              state = 35;
              break;
            
            case (7) : // Heater
              state = 42;
              break;
            
            case (8) :
              state = 3;
              encoderPos = 1;
              break;
            
            case (0) :
              state = 42;
              encoderPos = 7;
              break;
            
          }
        }    
        
        else if (directory == 4) {
          switch (encoderPos) {
            case (1) :
              state = 62;
              break;
            
            case (2) :
              state = 5;
              break;
            
            case (3) :
              state = 10;
              break;
            
            case (4):
              state = 62;
              encoderPos = 1;
              break;
            
            case (0) :
              state = 10;
              encoderPos = 3;
              break;
          
        }
        }
        else if (directory == 5) {
          switch (encoderPos) {
            case (1) :
              state = 63;
              break;
            
            case (2) :
              state = 6;
              break;
            
            case (3) :
              state = 9;
              break;
            
            case (4) :
              state = 63;
              encoderPos = 1;
              break;
            
            case (0) :
              state = 9;
              encoderPos = 3;
              break;
            
          }
        }
        
        else if (directory == 6) {
          switch (encoderPos) {
            case (1) :
              state = 64;
              break;
            
            case (2) :
              state = 7;
              break;
            
            case (3) :
              state = 8;
              break;
            
            case (4) :
              state = 64;
              encoderPos = 1;
              break;
            
            case (0) :
              state = 8;
              encoderPos = 3;
              break;
            
          }
        }
        
        else if (directory == 7) {
          switch (encoderPos) {
            case (1) :
              state = 66;
              break;
            
            case (2) :
              state = 12;
              break;
            
            case (3) :
              state = 13;
              break;
            
            case (4) :
              state = 66;
              encoderPos = 1;
              break;
            
            case (0) :
              state = 13;
              encoderPos = 3;
              break;
            
          }
        }
        
        else if (directory == 8) {
          switch (encoderPos) {
            case (1) :
              state = 15;
              break;
            
            case (2) :
              state = 16;
              break;
            
            case (3) :
              state = 20;
              break;
            
            case (4) :
              state = 21;
              break;
            
            case (5) :
              state = 15;
              encoderPos = 1;
              break;
            
            case (0) :
              state = 21;
              encoderPos = 4;
              break;
            
          }
        }
        
        else if (directory == 9) {
          switch (encoderPos) {
            case (1) :
              state = 17;
              break;
            
            case (2) :
              state = 18;
              break;
            
            case (3) :
              state = 19;
              break;
            
            case (4) :
              state = 17;
              encoderPos = 1;
              break;
            
            case (0) :
              state = 19;
              encoderPos = 3;
              break;
            
          }
        }
        
        else if (directory == 10) {
          switch (encoderPos) {
            case (1) :
              state = 23;
              break;
            
            case (2) :
              state = 24;
              break;
            
            case (3) :
              state = 77;
              break;
            case (4):
            state = 23;
            encoderPos = 1;
            break;
            
            case (0) :
              state = 77;
              encoderPos = 3;
              break;
            
          }
        }
        
        else if (directory == 11) {
          switch (encoderPos) {
            case (1) :
              state = 25;
              break;
            
            case (2) :
              state = 26;
              break;
            
            case (3) :
              state = 27;
              break;
            
            case (4) :
              state = 25;
              encoderPos = 1;
              break;
            
            case (0) :
              state = 27;
              encoderPos = 3;
              break;
            
          }
        }
        
        else if (directory == 12) {
          switch (encoderPos){
            case (1) :
              state = 29;
              break;
            
            case (2) :
              state = 30;
              break;
            
            case (3) :
              state = 34;
              break;
            
            case (4) :
              state = 29;
              encoderPos = 1;
              break;
            
            case (0) :
              state = 34;
              encoderPos = 3;
              break;
            
          }
        }
        
        else if (directory == 13) {
          switch (encoderPos) {
            case (1) :
              state = 31;
              break;
            
            case (2) :
              state = 32;
              break;
            
            case (3) :
              state = 33;
              break;
            
            case (4) :
              state = 31;
              encoderPos = 1;
              break;
            
            case (0) :
              state = 33;
              encoderPos = 3;
              break;
            
          }
        }
        
        else if (directory == 14) {
          switch (encoderPos) {
            case (1) :
              state = 36;
              break;
            
            case (2) :
              state = 37;
              break;
            
            case (3) :
              state = 41;
              break;
            
            case (4) :
              state = 36;
              encoderPos = 1;
              break;
            
            case (0) :
              state = 41;
              encoderPos = 3;
              break;
            
          }
        }
        
        else if (directory == 15) {
          switch (encoderPos) {
            case (1) :
              state = 38;
              break;
            
            case (2) :
              state = 39;
              break;
            
            case (3) :
              state = 40;
              break;
            
            case (4) :
              state = 38;
              encoderPos = 1;
              break;
            
            case (0) :
              state = 40;
              encoderPos = 3;
              break;
            
          }
        }
        
        else if (directory == 16) {
          switch (encoderPos) {
            case (1) :
              state = 43;
              break;
            
            case (2) :
              state = 44;
              break;
            
            case (3) :
              state = 48;
              break;
            
            case (4) :
              state = 43;
              encoderPos = 1;
              break;
            
            case (0) :
              state = 48;
              encoderPos = 3;
              break;
            
          }
        }
        
        else if (directory == 17) {
          switch (encoderPos) {
            case (1) :
              state = 45;
              break;
            
            case (2) :
              state = 46;
              break;
            
            case (3) :
              state = 47;
              break;
            
            case (4) :
              state = 45;
              encoderPos = 1;
              break;
            
            case (0) :
              state = 47;
              encoderPos = 3;
              break;
            
          }
        }
        
        else if (directory == 18) {
          switch (encoderPos) {
            case (1) :
              state = 50;
              break;
            
            case (2) :
              state = 51;
              break;
            
            case (3) :
              state = 57;
              break;
            
            case (4) :
              state = 58;
              break;
            
            case (5) :
              state = 50;
              encoderPos = 1;
              break;
            
            case (0) :
              state = 58;
              encoderPos = 4;
              break;
            
          }
        }
        
        else if (directory == 19) {
          switch (encoderPos) {
            case (1) :
              state = 52;
              break;
            
            case (2) :
              state = 53;
              break;
            
            case (3) :
              state = 54;
              break;
            
            case (4) :
              state = 55;
              break;
            
            case (5):
              state = 56;
              break;
            
            case (6) :
              state = 52;
              encoderPos = 1;
              break;
            
            case (0) :
              state = 56;
              encoderPos = 5;
              break;
            
          }
        }
        
        else if (directory == 20){
          switch (encoderPos) {
            case (1) :
              state = 59;
              break;
            
            case (2) :
              state = 60;
              break;
            
            case (3) :
              state = 61;
              break;
            
            case (4) :
              state = 59;
              encoderPos = 1;
              break;
            
            case (0) :
              state = 61;
              encoderPos = 3;
              break;
          }
          }
          else if (directory == 21) {
            switch (encoderPos) {
              case (1) :
              state = 71;
              break;
              
              case (2) :
                state = 72;
                break;
              
              case (3) :
                state = 73;
                break;
              
              case (4) :
                state = 71;
                encoderPos = 1;
                break;
              
              case (0) :
                state = 73;
                encoderPos = 3;
                break;
              
            }
          }
          else if (directory == 22) { // state = 67
            if (encoderPos == 255) {
              encoderPos = 100;
            }
            else if (encoderPos == 101) {
              encoderPos = 0;
            }
          }
          
          else if (directory == 23) {//state = 68
            if ((encoderPos < Xdeg) || (encoderPos > Ydeg)) {
              encoderPos = oldEncoderPos;
            }
          }
          
          else if (directory == 24) { //state = 69
            if ((encoderPos < Xdeg) || (encoderPos > Ydeg)) {
              encoderPos = oldEncoderPos;
            }
          }
          
          else if (directory == 25) { //state = 70
            if ((encoderPos < Xdeg) || (encoderPos > Ydeg)) {
              encoderPos = oldEncoderPos;
            }
          }
          
          else if (directory == 27) { //state = 74
            if ((encoderPos == 255) || (encoderPos == 100)) {
              encoderPos = oldEncoderPos;
            }
          }
          
          else if (directory == 26) {// state = 78
            if ((encoderPos == 255) || (encoderPos == 25)) {
              encoderPos = oldEncoderPos;
            }
          }
          else if (directory == 27) {
            if (encoderPos == 255) {
              encoderPos = 0;
            }
            else if (encoderPos == 100) {
              encoderPos = 100;
            }
          }
          
          else if (directory == 28) {
            if (encoderPos == 255) {
              encoderPos = 0;
            }
            else if (encoderPos == 25) {
              encoderPos = 25;
            }
          }
          else if (directory == 29) {
            if (encoderPos == 255) {
              encoderPos = 0;
            }
            else if (encoderPos == 254) {
              encoderPos = 253;
            }
          }
          else if (directory == 30) { //stte = 65
            switch (encoderPos) {
              case 1:
                state = 65;
              break;
              case 2:
                state = 11;
              break;
              case 3:
                state = 65;
                encoderPos = 1;
              break;
                case 0:
                state = 11;
                encoderPos = 2;              
              break;
            }
          }
    
        
        
        
        
        
        
        screenUpdate(state, currentTemp);
//____________________________   
    
        oldEncoderPos = encoderPos;
  }

  byte buttonState = digitalRead(buttonPin);
  if (buttonState != oldButtonState){
    if (millis () - buttonPressTime >= debounceTime){
      buttonPressTime = millis ();
      oldButtonState = buttonState;
      if (buttonState == LOW){
        buttonPressed = 1;
      }
      else {
  
        buttonPressed = 0;
      }
    }
  }
    //___________________
    //Main menu section
 //____________
 //Navigation
 
 if (buttonPressed == 1) {
   buttonPressed = 0;
    switch (state) {
      case (0) :
        state = 1;
        directory = 1;
        break;
      
      case (1) :
        state = 0;
        directory = 0;
        break;
      
      case (2) :
        state = 3;
        directory = 3;
        break;
      
      case (3) :
        state = 1;
        directory = 1;
        break;
      
      case (4) :
        state = 62;
        directory = 4;
        break;
      
      case (5) :
        state = 63;
        directory = 5;
        break;
      
      case (6) :
        state = 64;
        directory = 6;
        break;
      
      case (7) :
        state = 63;
        directory = 5;
        fanEnable = 1;
        fanControl(fanEnable, fanSpeed);
        break;
      
      case (8) :
        state = 63;
        directory = 5;
        fanEnable = 0;
        fanControl(fanEnable, fanSpeed);
        break;
      
      case (9):
        directory = 22;
        state = 67;
        break;
      
      case (10) :
        directory = 30;
        state = 65;
        break;
      
      case (11) :
        directory = 7;
        state = 66;
        break;
      
      case (12) :
        state = 65;
        directory = 30;
        bathPower = HIGH;
        break;
      
      case (13) :
        state = 65;
        directory = 30;
        bathPower = LOW;
        break;
      
      case (14) :
        directory = 8;
        state = 15;
        break;
      
      case (15) :
        directory = 3;
        state = 14;
        break;
      
      case (16) :
        directory = 9;
        state = 17;
        break;
      
      case (17) :
        state = 15;
        directory = 8;
        break;
      
      case (18) :
        directory = 23;
        state = 68;
        break;
      
      case (19) :
        directory = 24;
        state = 69;
        break;
      
      case (20) :
        directory = 25;
        state = 70;
        break;
      
      case (21) :
        directory = 21;
        state = 71;
        break;
      
      case (22) :
        directory = 10;
        state = 23;
        break;
      
      case (23) :
        directory = 3;
        state = 3;
        break;
      
      case (24) :
        directory = 11;
        state = 25;
        break;
      
      case (25) :
        directory = 10;
        state = 23;
        break;
      
      case (26) :
        digitalWrite(pullerEnable, LOW);
        directory = 10;
        state = 23;
        break;
      
      case (27) :
        digitalWrite(pullerEnable, HIGH);
        state = 23;
        directory = 10;
        break;
      
      
      case (28) :
        state = 29;
        directory = 12;
        break;
      
      case (29) :
        state = 3;
        directory = 3;
        break;
      
      case (30) :
        state = 31;
        directory = 13;
        break;
      
      case (31) :
        state = 29;
        directory = 12;
        break;
      
      case (32) :
        digitalWrite(augerEnable, LOW);
        state = 29;
        directory = 12;
        break;
      
      case (33) :
        digitalWrite(augerEnable, HIGH);
        state = 29;
        directory = 12;
        break;
      
      case (34) :
        state = 74;
        directory = 27;
        break;
      
      case (35) :
        state = 36;
        directory = 14;
        break;
      
      case (36) :
        directory = 3;
        state = 3;
        break;
      
      case (37) :
        state = 38;
        directory = 15;
        break;
      
      case (38) :
        state = 36;
        directory = 14;
        break;
      
      case (39) :
        digitalWrite(winderEnable, LOW);
        state = 36;
        directory = 14;
        break;
      
      case (40) :
        digitalWrite(winderEnable, HIGH);
        state = 36;
        directory = 14;
        break;
      
      case (41) :
        state = 75;
        directory = 28;
        break;
      
      case (42) :
        state = 43;
        directory = 16;
        break;
      
      case (43) :
        directory = 3;
        state = 3;
        break;
      
      case (44) :
        directory = 17;
        state = 45;
        break;
      
      case (45) :
        state = 43;
        directory = 16;
        break;
      
      case (46) :
        heaterEnable = 1;
        state = 43;
        directory = 16;
        break;
      
      case (47) :
        heaterEnable =0;
        state = 43;
        directory = 16;
        break;
      
      case (48) :
        state = 76;
        directory = 29;
        break;
      
      case (49) :
        state = 50;
        directory = 18;
        break;
      
      case (50) :
        state = 49;
        directory = 2;
        break;
      case (62) :
      state = 3;
      directory = 3;
      break;
       case(63) :
       state = 62;
       directory = 4;
       break;
       case (64) :
       state = 63;
       directory = 5;
       break;
        
        
     
      
      
      case (67) :
        fanSpeed = encoderPos*.01*255;
        state = 63;
        directory = 5;
        fanControl(fanEnable, fanSpeed);
        break;
      
      case (68) :
        spoolStart = encoderPos;
        state = 15;
        directory = 8;
        break;
      
      case (69) :
        spoolStop = encoderPos;
        state = 15;
        directory = 8;
        break;
      
      case (70) :
        spoolPos = encoderPos;
        filamentGuide.write(spoolPos);
        state = 15;
        directory = 3;
        break;
      
      case (74) :
        desiredAugerRPM = encoderPos;
        auger.setSpeed(200*gearBox*desiredAugerRPM);
        currentAugerRPM = desiredAugerRPM;
        state = 29;
        directory = 12;
        break;
      
      case (75) :
        winderRPM = encoderPos;
        winder.setSpeed(200*winderRPM);
        state = 36;
        directory = 14;
        break;
      
      case (76) :
        desiredTemp = encoderPos;
        state = 43;
        directory = 16;
        break;
      
      case (77) :
        state = 78;
        directory = 26;
        break;
      
      case (78) :
        pullerRPM = encoderPos;
        puller.setSpeed(200*pullerRPM*10);
        state = 23;
        directory = 10;
        break;
     
    }
  screenUpdate(state, currentTemp);
  encoderPos = 1;
 }
}
  
  
  

  //________________________________________________________________________________________________________
  //Carry out common activities each time a setting is changed  
  /*
void setAdmin(byte name, byte setting){ 
  lcd.clear();
  lcd.print("Setting ");
  lcd.print(name);
  lcd.print(" = ");
  lcd.println(setting);
  encoderPos = 0;
  buttonPressed = 0;
  mode = 0;
  lcd.println("MainMenu");
}
*/
