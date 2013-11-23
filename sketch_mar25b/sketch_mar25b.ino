#include <SoftwareSerial.h>

String inputString = "";
String nullString = "";

int button1Pin = A5;
int button2Pin = A4;
int button3Pin = A3;
int button4Pin = A2;
int button5Pin = A1;
int button6Pin = A0;
int masterON = 7;
int masterOFF = 8;

int light1Pin = 3;
int light2Pin = 11;
int light3Pin = 5;
int light4Pin = 10;
int light5Pin = 6;
int light6Pin = 9;

int led1Pin = 13;

boolean light1Mode = 0;
boolean light2Mode = 0;
boolean light3Mode = 0;
boolean light4Mode = 0;
boolean light5Mode = 0;
boolean light6Mode = 0;

boolean button1State;
boolean button2State;
boolean button3State;
boolean button4State;
boolean button5State;
boolean button6State;
boolean masterONState;
boolean masterOFFState;

void setup() {
  Serial.begin(9600);
  inputString.reserve(200);
  
  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);
  pinMode(button3Pin, INPUT_PULLUP);
  pinMode(button4Pin, INPUT_PULLUP);
  pinMode(button5Pin, INPUT_PULLUP);
  pinMode(button6Pin, INPUT_PULLUP);
  pinMode(masterON, INPUT_PULLUP);
  pinMode(masterOFF, INPUT_PULLUP);
  
  pinMode(light1Pin, OUTPUT);
  pinMode(light2Pin, OUTPUT);
  pinMode(light3Pin, OUTPUT);
  pinMode(light4Pin, OUTPUT);
  pinMode(light5Pin, OUTPUT);
  pinMode(light6Pin, OUTPUT);
  
  pinMode(led1Pin, OUTPUT);
  
  boolean button1State = digitalRead(button1Pin);
  boolean button2State = digitalRead(button2Pin);
  boolean button3State = digitalRead(button3Pin);
  boolean button4State = digitalRead(button4Pin);
  boolean button5State = digitalRead(button5Pin);
  boolean button6State = digitalRead(button6Pin);
  boolean masterONState = digitalRead(masterON);
  boolean masterOFFState = digitalRead(masterOFF);
}

void loop(){
  if (inputString == "light1") fnc_light1Mode();
  else if (inputString == "light2") fnc_light2Mode();
  else if (inputString == "light3") fnc_light3Mode();
  else if (inputString == "light4") fnc_light4Mode();
  else if (inputString == "light5") fnc_light5Mode();
  else if (inputString == "light6") fnc_light6Mode();
  else if (inputString == "ON") fnc_lightON_Mode();
  else if (inputString == "OFF") fnc_lightOFF_Mode();
  else inputString=nullString;
  
  
  boolean val1 = digitalRead(button1Pin);
  delay(5);
  boolean val12 = digitalRead(button1Pin);
  if (val1 == val12) {
    if (val1 != button1State) {
      if (val1 == LOW) {
        fnc_light1Mode();
      }
    }
    button1State = val1;
  }
  
  boolean val2 = digitalRead(button2Pin);
  delay(5);
  boolean val22 = digitalRead(button2Pin);
  if (val2 == val22) {
    if (val2 != button2State) {
      if (val2 == LOW) {
        fnc_light2Mode();
      }
    }
    button2State = val2;
  }
  
  boolean val3 = digitalRead(button3Pin);
  delay(5);
  boolean val32 = digitalRead(button3Pin);
  if (val3 == val32) {
    if (val3 != button3State) {
      if (val3 == LOW) {
        fnc_light3Mode();
      }
    }
    button3State = val3;
  }
  
  boolean val4 = digitalRead(button4Pin);
  delay(5);
  boolean val42 = digitalRead(button4Pin);
  if (val4 == val42) {
    if (val4 != button4State) {
      if (val4 == LOW) {
        fnc_light4Mode();
      }
    }
    button4State = val4;
  }
  
  boolean val5 = digitalRead(button5Pin);
  delay(5);
  boolean val52 = digitalRead(button5Pin);
  if (val5 == val52) {
    if (val5 != button5State) {
      if (val5 == LOW) {
        fnc_light5Mode();
      }
    }
    button5State = val5;
  }
  
  boolean val6 = digitalRead(button6Pin);
  delay(5);
  boolean val62 = digitalRead(button6Pin);
  if (val6 == val62) {
    if (val6 != button6State) {
      if (val6 == LOW) {
        fnc_light6Mode();
      }
    }
    button6State = val6;
  }
  
  boolean val7 = digitalRead(masterON);
  delay(5);
  boolean val72 = digitalRead(masterON);
  if (val7 == val72) {
    if (val7 != masterONState) {
      if (val7 == LOW) {
        fnc_lightON_Mode();
      }
    }
    masterONState = val7;
  }
  
  boolean val8 = digitalRead(masterOFF);
  delay(5);
  boolean val82 = digitalRead(masterOFF);
  if (val8 == val82) {
    if (val8 != masterOFFState) {
      if (val8 == LOW) {
        fnc_lightOFF_Mode();
      }
    }
    masterOFFState = val8;
  }
  

}

void serialEvent() {
  while (Serial.available() > 0) {
    char inChar = (char)Serial.read();
    inputString += inChar;
    if (inChar == '\n') break; 
  }
}

void fnc_light1Mode(){
  light1Mode = !light1Mode;
  digital_Write();
}

void fnc_light2Mode(){
  light2Mode = !light2Mode;
  digital_Write();
}

void fnc_light3Mode(){
  light3Mode = !light3Mode;
  digital_Write();
}

void fnc_light4Mode(){
  light4Mode = !light4Mode;
  digital_Write();
}

void fnc_light5Mode(){
  light5Mode = !light5Mode;
  digital_Write();
}

void fnc_light6Mode(){
  light6Mode = !light6Mode;
  digital_Write();
}

void fnc_lightON_Mode(){
  light1Mode = 1;
  light2Mode = 1;
  light3Mode = 1;
  light4Mode = 1;
  light5Mode = 1;
  light6Mode = 1;
  digital_Write();
}

void fnc_lightOFF_Mode(){
  light1Mode = 0;
  light2Mode = 0;
  light3Mode = 0;
  light4Mode = 0;
  light5Mode = 0;
  light6Mode = 0;
  digital_Write();
}

void digital_Write()
{
  digitalWrite(light1Pin, light1Mode); 
  Serial.print("light1: "); Serial.println(light1Mode);
  digitalWrite(light2Pin, light2Mode);
  Serial.print("light2: "); Serial.println(light2Mode);
  digitalWrite(light3Pin, light3Mode);
  Serial.print("light3: "); Serial.println(light3Mode);
  digitalWrite(light4Pin, light4Mode);
  Serial.print("light4: "); Serial.println(light4Mode);
  digitalWrite(light5Pin, light5Mode);
  Serial.print("light5: "); Serial.println(light5Mode);
  digitalWrite(light6Pin, light6Mode);
  Serial.print("light6: "); Serial.println(light6Mode);
  inputString=nullString;
}
