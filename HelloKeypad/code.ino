#include <Keypad.h>
#include <LiquidCrystal.h>
#include "EmonLib.h"                   // Include Emon Library

EnergyMonitor emon1;

#define LEFT 0
#define RIGHT 1
#define STOP 2

const byte numRows= 4; //number of rows on the keypad
const byte numCols= 4; //number of columns on the keypad

char keymap[numRows][numCols] ={{'1', '2', '3', 'A'},
                                {'4', '5', '6', 'B'},
                                {'7', '8', '9', 'C'},
                                {'.', '0', '#', 'D'}};

const byte rowPins[numRows] = {5,4,3,2}; //Rows 0 to 3
const byte colPins[numCols]= {A2,A3,A4,A5}; //Columns 0 to 3


const int in1 = 6;
const int in2 = 9;

String data = "";
int kp=10;
int kd=1;

float desiredCurrent = 0;
float lastError = 0.0;
char keypressed;

Keypad myKeypad= Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);
LiquidCrystal lcd(7, 8, 13, 12, 11, 10);          //12,11,5,4,3,2

void setup()
{
//  Serial.begin(9600);
  lcd.begin(20,4);
  emon1.current(0, 2.84);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
}

void loop()
{
  keypressed = myKeypad.getKey();
  
  if (keypressed != NO_KEY)
  {
    //press A button on keypad
    if(keypressed=='A')
      A_key_function();

    //press B button on keypad
    else if(keypressed=='B')
      B_key_function();

    //press C button on keypad
    else if(keypressed=='C')
      C_key_funtion();

    //press C button on keypad
    else if(keypressed=='D')
      D_key_funtion();
   }
   else
   {
    calculatePD();
   }
}

void rotateMotor(unsigned char dir,int i)
{
  if (dir == 0)
  {
    analogWrite(in1,i);
    digitalWrite(in2,LOW);
  }
  else if(dir == 1)
  {
    digitalWrite(in1,LOW);
    analogWrite(in2,i);
  }
  else
  {
    digitalWrite(in1,LOW);
    digitalWrite(in2,LOW);
  }
}

void calculatePD()
{
  double sensorCurrent = emon1.calcIrms(1480);
  sensorCurrent = sensorCurrent - 0.01;

  double error = desiredCurrent - sensorCurrent;
  double pd = (kp*error + kd*(error-lastError));
  lastError = error;
  
  lcd.setCursor(0,0);
  lcd.print(F("Sensor Current:"));
  lcd.setCursor(15,0);
  lcd.print(sensorCurrent,1);
  
  lcd.setCursor(0,1);
  lcd.print(F("Desired Current:"));
  lcd.setCursor(16,1);
  lcd.print(desiredCurrent,1);
  
  if(pd >= 1.1)             //1.5
  {
    rotateMotor(RIGHT,100);
//    lcd.setCursor(0,3);
//    lcd.print(F("rotate clockwise"));
  }
  if(pd <= -1.1)            //-1.5
  {
    rotateMotor(LEFT,100);
//    lcd.setCursor(0,3);
//    lcd.print(F("rotate anti clockwise"));
  }
  if((pd > -1.1 && pd < 0) || (pd < 1.1 && pd >0))
  {
    rotateMotor(STOP,0);
//    lcd.setCursor(0,3);
//    lcd.print(F("stop"));
  }
}


void A_key_function()
{
  int i = 11;
  delay(100);
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(F("old current:"));
  lcd.setCursor(12,0);
  lcd.print(desiredCurrent,1);
  lcd.setCursor(0,1);
  lcd.print(F("new current:"));
  
  while(1)
  {
    //use matrix keys to set new current
    keypressed = myKeypad.getKey();
    if (keypressed != NO_KEY)
    {
       //put pressed key value into string
      data += keypressed;
      i++;
      //show the value in monitor
      lcd.setCursor(i,1);
      lcd.print(keypressed);
      if(keypressed == '#')
      {
        desiredCurrent = data.toFloat();
        lcd.setCursor(0,2);
        lcd.print(F("done"));
        delay(1000);
        data = "";
        break;
      }
    }
  }
  lcd.clear();
  delay(500);
}

void B_key_function()
{
  int i = 6;
  delay(100);
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(F("old kp:"));
  lcd.setCursor(7,0);
  lcd.print(kp);
  lcd.setCursor(0,1);
  lcd.print(F("new kp:"));
  
  while(1)
  {
     //use matrix keys to set new kp
     keypressed = myKeypad.getKey();
     if (keypressed != NO_KEY)
      {
        //put pressed key value into string
        data += keypressed;
        i++;
        //show the value in monitor
        lcd.setCursor(i,1);
        lcd.print(keypressed);
        //if # character is pressed then set the new kd value
        if(keypressed == '#')
        {
            kp = data.toInt();
            lcd.setCursor(0,2);
            lcd.print(F("done"));
            delay(1000);
            data = "";
            break;
        }
    }
  }
  lcd.clear();
  delay(500);
}

void C_key_funtion()
{
  int i = 6;
  delay(100);
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(F("old kd:"));
  lcd.setCursor(7,0);
  lcd.print(kd);
  lcd.setCursor(0,1);
  lcd.print(F("new kd:"));
  
  while(1)
  {
     //use matrix keys to set new kp
     keypressed = myKeypad.getKey();
     if (keypressed != NO_KEY)
     {
        //put pressed key value into string
        data += keypressed;
        i++;
        //show the value in monitor
        lcd.setCursor(i,1);
        lcd.print(keypressed);
        //if # character is pressed then set the new kd value
        if(keypressed == '#')
        {
            kd = data.toInt();
            lcd.setCursor(0,2);
            lcd.print(F("done"));
            delay(1000);
            data = "";
            break;
        }
     }
  }
  lcd.clear();
  delay(500);
}

void D_key_funtion()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(F("code is developed by"));
  lcd.setCursor(0,1);
  lcd.print(F("Debasish Dev,EEE-12"));
  lcd.setCursor(0,2);
  lcd.print(F("RUET"));
  lcd.setCursor(0,3);
  lcd.print(F("blackviper065@gmail.com"));
  
  delay(5000);
  lcd.clear();
}

