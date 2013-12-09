//**************************************************************//
//  Name    : shiftOutCode, Hello World                         //
//  Author  : Carlyn Maw,Tom Igoe                               //
//  Date    : 25 Oct, 2006                                      //
//  Version : 1.0                                               //
//  Notes   : Code for using a 74HC595 Shift Register           //
//          : to count from 0 to 255                            //
//****************************************************************

//Pin connected to ST_CP of 74HC595
int latchPin = 8;
//Pin connected to SH_CP of 74HC595
int clockPin = 13;
////Pin connected to DS of 74HC595
int dataPin = 11;

byte sh[12]={
  B00000001,    //0
  B00000010,    //1
  B00000100,    //2
  B00001000,    //3
  B00010000,    //4
  B00100000,    //5
  B01000000,    //6
  B00000000,    //7
  B00000000,    //8
  B00000000};   //9

void setup(){
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop(){
  for (int j = 0; j < 12; j++){
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, sh[j]);
    digitalWrite(latchPin, HIGH);
    delay(1000);
  }
} 
