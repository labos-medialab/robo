#include <Wire.h>
#include <ADXL345.h> //lib za akcelerometar
#include <BMP085.h> //lib za tlak i temperaturu

const float alpha = 0.2;

int rX=0, rY=0, rZ=0;
int X=0, Y=0, Z=0;
int Xo=0, Yo=0, Zo=0;
unsigned int t;
float temperature;

int inApin[2] = {7, 4};  // INA: Clockwise input
int inBpin[2] = {8, 9}; // INB: Counter-clockwise input
int pwmpin[2] = {5, 6}; // PWM input
int cspin[2] = {2, 3}; // CS: Current sense ANALOG input
int enpin[2] = {0, 1}; // EN: Status of switches output (Analog pin)

ADXL345 adxl; //ime akcelerometra u kodu

String inputString="", dataString="", tempString="", nullString="", returnString="none";

#define BRAKEVCC 0
#define CW   1
#define CCW  2
#define BRAKEGND 3
#define CS_THRESHOLD 100
#define LED 13
#define L 10

boolean led=0, stupid=1, f=0, b=0, tt=1;

void setup(){
  Serial.begin(115200);
  
  adxl.begin(); //započni akcelerometru!
  adxlSetup(); //setupiraj se!
  
  bmp085Calibration();
  
  for (int i=0; i<2; i++){
    pinMode(inApin[i], OUTPUT);
    pinMode(inBpin[i], OUTPUT);
    pinMode(pwmpin[i], OUTPUT);
  }
  
  for (int i=0; i<2; i++){
    digitalWrite(inApin[i], LOW);
    digitalWrite(inBpin[i], LOW);
  }
  
  pinMode(2,INPUT_PULLUP);
  attachInterrupt(0, getI, FALLING);
  
  pinMode(4,1);
  digitalWrite(4,0);
  
  Serial.println("bok ja sam cjevovdno vozilo");
  Serial.println("imam svjetlo, brzinu i nekalibriranu inklinaciju!");
  Serial.println("2.0.8");
}

void loop(){
  digitalWrite(LED,led);
  
  if(stupid && tt){
    t++;
    if(t>80){
      motorOff(0);
      motorOff(1);
      f=0,b=0;
      delay(500);
      t=0; tt=0;
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
  t=0;tt=1;
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
    f=1;
    tempString=inputString.substring(1,inputString.length());
    int temp = tempString.toInt();
    if(b){
      Serial.println("delay");
      motorOff(0);
      motorOff(1);
      delay(500);
    }
    
    motorGo(1, CW, temp);
    motorGo(0, CW, temp);
    b=0;
  }
  else if(inputString.startsWith("B")){
    b=1;
    tempString=inputString.substring(1,inputString.length());
    int temp = tempString.toInt();
    if(f){
      Serial.println("delay");
      motorOff(0);
      motorOff(1);
      delay(500);
    }
    motorGo(0, CCW, temp);
    motorGo(1, CCW, temp);
    f=0;
  }
  else if(inputString.startsWith("L")){
    tempString=inputString.substring(1,inputString.length());
    int temp = tempString.toInt();
    analogWrite(L,temp);
  }
  else if(inputString.startsWith("stop")){
    f=0,b=0;
    motorOff(0);
    motorOff(1);
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

void motorOff(int motor)
{
  // Initialize braked
  for (int i=0; i<2; i++)
  {
    digitalWrite(inApin[i], LOW);
    digitalWrite(inBpin[i], LOW);
  }
  analogWrite(pwmpin[motor], 0);
}

void motorGo(uint8_t motor, uint8_t direct, uint8_t pwm)
{
  if (motor <= 1)
  {
    if (direct <=4)
    {
      // Set inA[motor]
      if (direct <=1)
        digitalWrite(inApin[motor], HIGH);
      else
        digitalWrite(inApin[motor], LOW);

      // Set inB[motor]
      if ((direct==0)||(direct==2))
        digitalWrite(inBpin[motor], HIGH);
      else
        digitalWrite(inBpin[motor], LOW);

      analogWrite(pwmpin[motor], pwm);
    }
  }
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
