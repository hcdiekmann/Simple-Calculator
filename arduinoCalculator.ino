#include <Display.h>
#include <TM1637Display.h>

//constant global variables that won't change
const int ledRed = 4;
const int ledGreen = 5;
const int ledBlue = 6;
const int ledYellow = 7;
const int buttonRight = 8;
const char a = 'a';
const char s = 's';
const char t = 't';
const char d = 'd';


 int buttonState = 0;
 int mode = 0;
 int lastButtonState = 0;
 int poti;
 float percentage;
 int value1;
 int value2;
 float result;
 char operatorsign;
 



void setup() 
{
  Serial.begin(9600);
  Display.clear();                      //Clear the Display
  pinMode(ledRed, OUTPUT);         
  pinMode(ledGreen, OUTPUT);         
  pinMode(ledBlue, OUTPUT);         
  pinMode(ledYellow, OUTPUT);         
  pinMode(buttonRight, INPUT_PULLUP);   
  pinMode(A0,INPUT);                    //Potentiometer
 
}


void loop() 
{
  buttonState = digitalRead(buttonRight);
  poti = analogRead(A0);
  Serial.println(mode);

  if (buttonState != lastButtonState) 
  {
    if (buttonState == LOW)
    {
      if (mode == 0)
      {
        Display.show("----");
        digitalWrite(ledYellow, HIGH);
        digitalWrite(ledBlue, HIGH);
        digitalWrite(ledGreen, HIGH);
        digitalWrite(ledRed, HIGH);
        delay(2000);
        Display.clear();
        digitalWrite(ledYellow, LOW);
        digitalWrite(ledBlue, LOW);
        digitalWrite(ledGreen, LOW);
        digitalWrite(ledRed, LOW);
      }
      mode++;
    }
    delay(50);
  }
  
  lastButtonState = buttonState; 
     
  if (mode == 1) 
  {
    digitalWrite(ledBlue, HIGH);
    value1 = map(poti,0,1023,-10,10);
    Display.show(value1);
  }
  if (mode == 2)
  {
    Display.clear();
    int firstValue = value1;
    Serial.print(firstValue);
    percentage = map(poti,0,1023,0,100);
    if (percentage < 25)
    {
     Display.showCharAt(0,a);
     char operatorsign = "+";
    }
    if (percentage > 25 && percentage < 50)
    {
     Display.showCharAt(0,s);
     char operatorsign = "-";
    }
    if (percentage > 50 && percentage < 75)
    {
     Display.showCharAt(0,t);
     char operatorsign = "*";
    }
    if (percentage > 75)
    {
     Display.showCharAt(0,d);
     char operatorsign = "/";
    }
  }
  if (mode == 3)
  {
    Display.clear();
    value2 = map(poti,0,1023,-10,10);
    Display.show(value2);
  }
  if (mode == 4)
  {
    int secondValue = value2;
    Display.clear();
    digitalWrite(ledBlue, LOW);
    result = firstValue "operatorsign" secondValue;
    Display.show(result);
    digitalWrite(ledGreen, HIGH);
  }


   
}
