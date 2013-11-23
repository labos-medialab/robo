#include <Wire.h>

boolean flag=0, led=0;
String inputString="";
String nullString="";

void setup(){
  Wire.begin(9);
  Wire.onReceive(reciveEvent);
  Wire.onRequest(requestEvent);
  
  pinMode(13, OUTPUT);
}
void loop(){
  if (inputString=="1" || inputString=="ledON"){
    flag=1;
    led=1;
    digitalWrite(13,led);
  }
  else if (inputString=="0" || inputString=="ledOFF"){
    flag=1;
    led=0;
    digitalWrite(13,led);
  }
  else if (inputString=="blink" || inputString=="2"){
    flag=1;
    led = !led;
    digitalWrite(13,led);
    delay(1000);
  }
  else flag=0;
}
void reciveEvent(int x){
  inputString=nullString;
  while(Wire.available() > 0){
    char c = Wire.read();
    inputString += c;
  }
}

void requestEvent(){
  if(flag) Wire.write("yes");
  else Wire.write("no");
}
