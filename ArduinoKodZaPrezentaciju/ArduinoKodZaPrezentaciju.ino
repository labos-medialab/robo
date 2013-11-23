//include stuff
#include <Servo.h>
#include <OneWire.h>
//define stuff
#define ledica 13
#define analog A0
#define onewire 4
const uint8_t* addr=0x1F2B3A; //0x1F2B3A
OneWire OneWireSomething(onewire);
void setup(){
  Serial.begin(115200);
  pinMode(ledica, OUTPUT);
}
void loop(){
  OneWireSomething.select(addr);
  byte data = OneWireSomething.read();
  int var = analogRead(analog);
  if(data == var) digitalWrite(ledica, HIGH);
  else digitalWrite(ledica, LOW);
}
