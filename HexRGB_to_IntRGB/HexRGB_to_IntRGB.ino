
int tempIntArray[6];
boolean flag = 0;

//stringovi
String inputString = "";//string koji učita sa serijskog
String nullString = "";//string za reset

void setup() {
  Serial.begin(9600);//serijska veza na 9600bps
}

void loop(){
  if(inputString != nullString){
    //pvdje počinje
    for(int i=0;i<6;i++){
      int tempInt=0;
      tempInt=inputString.charAt(i);
      if(tempInt<=57) tempIntArray[i]=tempInt - 48;
      if(tempInt>64 && tempInt<71) tempIntArray[i]=tempInt - 55;
      if(tempInt>95 && tempInt<103) tempIntArray[i]=tempInt - 87;
    }
    
    int redInt = tempIntArray[0]*16 + tempIntArray[1];
    int greenInt = tempIntArray[2]*16 + tempIntArray[3];
    int blueInt =tempIntArray[4]*16 + tempIntArray[5];
    
    Serial.println(redInt);
    Serial.println(greenInt);
    Serial.println(blueInt);
    
    //ovdje završava
    inputString = nullString;
  }
}


void serialEvent() {
  while (Serial.available() > 0) {
    inputString += (char)Serial.read();
    delay(10);
  }
}
