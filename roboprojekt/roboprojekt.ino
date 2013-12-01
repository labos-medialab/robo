#include <Wire.h>
#include <ADXL345.h> //lib za akcelerometar
#include <BMP085.h> //lib za tlak i temperaturu

const float alpha = 0.2;

int rX=0, rY=0, rZ=0;
int X=0, Y=0, Z=0;
int Xo=0, Yo=0, Zo=0;
unsigned int t;
float temperature;

ADXL345 adxl; //ime akcelerometra u kodu

String inputString="", dataString="", tempString="", nullString="", returnString="none";

#define F 5 //pin za naprije
#define B 3 //pin za nazad
#define L 6 //svjetlno
#define LED 13

boolean led=0, stupid=1, f=0, b=0;

void setup(){
  Serial.begin(115200);
  
  adxl.begin(); //započni akcelerometru!
  adxlSetup(); //setupiraj se!
  
  bmp085Calibration();

  pinMode(2,INPUT_PULLUP);
  attachInterrupt(0, getI, FALLING);
  
  pinMode(4,1);
  digitalWrite(4,0);
  
  Serial.println("bok ja sam cjevovdno vozilo");
  Serial.println("imam svjetlo, brzinu i nekalibriranu inklinaciju!");
  Serial.println("2.0.5");
}

void loop(){
  digitalWrite(LED,led);
  
  if(stupid){
    t++;
    if(t>80){
      analogWrite(F,0);
      analogWrite(B,0);
      f=0,b=0;
      delay(500);
      t=0;
    }
  }
  double sX=0, sY=0, sZ=0,i;
  for(i=1; i<10; i++){
    adxl.readAccel(&rX, &rY, &rZ);
  //sX+=rX;
    sY+=rY;
  }
//X=sX/i;
  Y=sY/i;
//Serial.print(X-Xo);Serial.print(" ");
//Serial.println(Y-Yo);//Serial.print(" ");
//Serial.println(Z);

  temperature = bmp085GetTemperature(bmp085ReadUT());

  byte interrupts = adxl.getInterruptSource();
  if(adxl.triggered(interrupts, ADXL345_SINGLE_TAP)){
    Serial.println("tap");
  }
  if(adxl.triggered(interrupts, ADXL345_FREE_FALL)){
    Serial.println("freefall");
  }
  led=!led;
}

void serialEvent(){
  t=0;
  digitalWrite(LED,0);
  inputString=nullString;
  while(Serial.available()>0){
    inputString+=(char)Serial.read();
    delay(10);
  }
  stringHandle();
  digitalWrite(LED,1);
}

void stringHandle(){
  if(inputString.startsWith("F")){
    f=1;analogWrite(B,0);
    tempString=inputString.substring(1,inputString.length());
    int temp = tempString.toInt();
    if(b){
      Serial.println("delay");
      delay(500);
    }
    analogWrite(F,temp);
    b=0;returnString=inputString;
  }
  else if(inputString.startsWith("B")){
    b=1;analogWrite(F,0);
    tempString=inputString.substring(1,inputString.length());
    int temp = tempString.toInt();
    if(f){
      Serial.println("delay");
      delay(500);
    }
    analogWrite(B,temp);
    f=0;returnString=inputString;
  }
  else if(inputString.startsWith("L")){
    tempString=inputString.substring(1,inputString.length());
    int temp = tempString.toInt();
    analogWrite(L,temp);
    returnString=inputString;
  }
  else if(inputString.startsWith("stop")){
    f=0,b=0;
    analogWrite(F,0);
    analogWrite(B,0);
    returnString=inputString;
  }
  else if(inputString.startsWith("cADXL")) calibrateADXL();
  
  else if(inputString.startsWith("cBMP085")) bmp085Calibration();
  
  else if(inputString.startsWith("getI")) getI();
  
  else if(inputString.startsWith("notStupid")) stupid=0;
  
  Serial.println(inputString);
}

void adxlSetup(){
  adxl.setTapDetectionOnX(1);
  adxl.setTapDetectionOnY(1);
  adxl.setTapDetectionOnZ(1);
  
  adxl.setTapThreshold(255);
  adxl.setTapDuration(30);
  
  adxl.setFreeFallThreshold(5);
  adxl.setFreeFallDuration(20);
  
  adxl.setInterruptMapping(ADXL345_INT_SINGLE_TAP_BIT,  ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_FREE_FALL_BIT,  ADXL345_INT1_PIN );
  
  adxl.setInterrupt(ADXL345_INT_SINGLE_TAP_BIT, 1);
  adxl.setInterrupt(ADXL345_INT_FREE_FALL_BIT, 1);
}

void calibrateADXL(){
  double sX=0, sY=0, sZ=0, i=0;
  do{
    i++;
    adxl.readAccel(&rX, &rY, &rZ);
    sX+=rX;sY+=rY;
  }while(i<500);
  Xo=sX/i;Yo=sY/i;
  
  //zapiši u eprom
}

void getI(){
  Serial.print(Y-Yo);Serial.print(" ");
  Serial.println(temperature, 2);
}
