#include <Wire.h>

String inputString="", dataString="", tempString="", nullString="";

int Address=9, Quantity=10, operation=1;
const int wire=1;

void setup(){Wire.begin();Serial.begin(115200);}

void loop(){}

void serialEvent() {
  inputString=nullString;while(Serial.available()>0){inputString+=(char)Serial.read();delayMicroseconds(100); }
  
  if(inputString.startsWith("wire"))operation=wire;
  
  dataString=inputString.substring(inputString.lastIndexOf(" ")+1,inputString.length());
  
  if(inputString.indexOf("-")>=0){ //ako je jedna opcija zadana
    if(inputString.charAt(inputString.indexOf("-")+1)=='a'){
      tempString=inputString.substring(inputString.indexOf("a")+1,inputString.indexOf(" ",inputString.indexOf("a")+2));
      if(tempString.toInt()>0)Address=tempString.toInt();
    }  
    if(inputString.charAt(inputString.indexOf("-")+1)=='q'){
      tempString = inputString.substring(inputString.indexOf("q")+1,inputString.indexOf(" ",inputString.indexOf("q")+2));
      if(tempString.toInt()>0)Quantity=tempString.toInt();
    }
  }
  
  if(inputString.indexOf("-",inputString.indexOf("-")+1)>=0){// ako su dvije
    if(inputString.charAt(inputString.indexOf("-",inputString.indexOf("-")+1)+1)=='a'){
      tempString = inputString.substring(inputString.indexOf("a")+1,inputString.indexOf(" ",inputString.indexOf("a")+2));
      if(tempString.toInt()>0)Address=tempString.toInt();
    }
    if(inputString.charAt(inputString.indexOf("-",inputString.indexOf("-")+1)+1)=='q'){
      tempString=inputString.substring(inputString.indexOf("q")+1,inputString.indexOf(" ",inputString.indexOf("q")+2));
      if(tempString.toInt()>0)Quantity=tempString.toInt();
    }
  }
  
  inputString=nullString;
  
  if(operation==wire){
    if(Address>0&&Address<50){
      byte data[dataString.length()];for(byte i=0;i<dataString.length();i++)data[i]=dataString.charAt(i);
      Wire.beginTransmission(Address);Wire.write(data,dataString.length());Wire.endTransmission();
      Wire.requestFrom(Address,Quantity,true);while(Wire.available()){byte c=Wire.read();if(c!=255)inputString+=(char)c;}
      Serial.print("Wire sent: ");Serial.println(dataString);
      Serial.print("Device: ");Serial.println(Address);
      Serial.print("Bytes to receive: ");Serial.println(Quantity);
      if(inputString=="yes")Serial.println("Transmission succeed");
      else if (inputString=="no"||inputString==nullString)Serial.println("Transmission failed");
      else Serial.println(inputString);
      Serial.println();
    }
    else{Serial.print("Address ");Serial.print(Address);Serial.println(" is invalid\nPlease select right address\n");}
  }
  else Serial.println("Unknown operation");
}
