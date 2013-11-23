#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 3
OneWire oneWire(ONE_WIRE_BUS);
 
DallasTemperature sensors(&oneWire);
DeviceAddress thermometerAddress = { 0x28, 0x1F, 0x40, 0xA8, 0x04, 0x00, 0x00, 0xA3 };

int Temp=0;
volatile int setTemp=40; // željena temperatura, volatile? lptisti se u interuptu, zato!
boolean flag=0;


byte seven_seg_digits[10][7] = {
  { 1,0,0,0,0,0,0 },  // = 0
  { 1,1,1,1,0,0,1 },  // = 1
  { 0,1,0,0,1,0,0 },  // = 2
  { 0,1,1,0,0,0,0 },  // = 3
  { 0,0,1,1,0,0,1 },  // = 4
  { 0,0,1,0,0,1,0 },  // = 5
  { 0,0,0,0,0,1,0 },  // = 6
  { 1,1,1,1,0,0,0 },  // = 7
  { 0,0,0,0,0,0,0 },  // = 8
  { 0,0,1,1,0,0,0 }   // = 9
};

void setup() {
  
  pinMode(A0, OUTPUT);
  //prebacio sam grijač na A0 zato jer su na pinovima 2 i 3 interupti a na
  //0 i 1 je serijski... pa svkai put kad programiraš moraš otkačit sve 0 i 1
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
 
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT); 
  
  digitalWrite(4, HIGH);// neznam što je ovdje ali ako je cijelo vrijeme high... 
                        //možeš to prebacit na vcc i na taj pin stavit grijač
  
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
  
  //za više informacija http://arduino.cc/en/Reference/attachInterrupt
  //kad nabaviš buttone spoji ih na 2 i 3 i kondezatorom prebrikaš zbog debouncinga
  //ako nešljaka moraćemo stavit neki 74HC14 ili programski riješit bez delaya...
  pinMode(2, INPUT_PULLUP); // interni pullup
  pinMode(3, INPUT_PULLUP); // interni pullup
  attachInterrupt(0, decreaseTemp, FALLING); // pin 2 smanjuje temperaturu
  attachInterrupt(1, increaseTemp, FALLING); // pin 3 povaćava temperaturu
  
  sensors.begin();
  
  sensors.setResolution(thermometerAddress, 9);
}
void sevenSegWrite(byte digit) {
  byte pin = 7;
  for (byte segCount = 0; segCount < 10; ++segCount) {
    digitalWrite(pin, seven_seg_digits[digit][segCount]);
    ++pin;
  }
}

int getTemperature()
{
  int x;
  sensors.requestTemperatures();
  return x = sensors.getTempC(thermometerAddress); 
}

void displayWrite (int Data)
{
  byte jedinica = byte(Data) % 10;
  byte desetica = byte(Data) / 10; 
  digitalWrite(5,1);digitalWrite(6,0);
  sevenSegWrite(jedinica);
  digitalWrite(6,1);digitalWrite(5,0);
  sevenSegWrite(desetica);
}

void decreaseTemp(){
  flag=1;
  setTemp--; // smanjim željenu temperaturu za 1
  for(byte i=0; i < 200; i++){// i na kratko ispišem koja je to temperatura
    displayWrite(setTemp);
  }
}

void increaseTemp(){
  flag=1;
  setTemp++;// povećam željenu temperaturu za 1
  for(byte i=0; i < 200; i++){// i na kratko ispišem koja je to temperatura
    displayWrite(setTemp);
  }
}

void loop() {
  flag=0;
  Temp = getTemperature();
  if(Temp <= (setTemp-2)) digitalWrite(A0, HIGH);  //ako je temperatura za 2 i više stupnja niža od željene pali grijač
  if(Temp >= (setTemp+2)) digitalWrite(A0, LOW);   //ako je temperatura za 2 i više stupnja viša od željene gasi grijač
  for(byte i=0; i < 400; i++){
    if (flag) break;
    displayWrite(Temp);
    // nema delaya zato jer se interrupt i delay baš nepodnose
  }
}    // :)
