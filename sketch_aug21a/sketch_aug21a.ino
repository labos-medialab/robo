#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 10);

String inputString = "";
String nullString = "";

void setup(){
  mySerial.begin(9600);
  pinMode(13,1);
}

void loop(){
  while (mySerial.available() > 0) {
    inputString +=char(mySerial.read());
    delay(10);
    if(mySerial.available()==0){
      if(inputString=="1"){
        digitalWrite(13,1);
        mySerial.println(inputString);
        inputString=nullString;
      }
      else if(inputString=="0"){
        digitalWrite(13,0);
        mySerial.println(inputString);
        inputString=nullString;
      }
      else {
        mySerial.println(inputString);
        inputString=nullString;
      }
    }
  }
}
