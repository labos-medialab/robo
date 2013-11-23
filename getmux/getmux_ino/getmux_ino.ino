#include "DHT.h"
#include <OneWire.h>
#include <DallasTemperature.h>

int inh = A0;    // Inhibit Line
int A = A3;         // Control pin C 
int B = A2;         // Control pin A
int C = A1;         // Control pin B
// y -> TX
// x -> RX,,,

float PH=0;
float AH=0;
float AT=0;
float WT1=0;
float WT2=0;


char stamp_data[50];
byte holding;
int AHT = 0;
int gPH = 1;
int ORP = 2;
int EC = 3;
int DO = 4;
int DT = 5;

void setup(){ 
  Serial.begin(9600);
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(inh, OUTPUT); 
  digitalWrite(inh, LOW);
  
  Serial.println("getmuxBETA 2.0");
}
void getProbe(int probe) {
  Serial3.begin(38400);
    openProbeChannel(probe);
    delay(10);
    Serial3.print("R\r");
    delay(200);
    holding = 0;
    if(Serial3.available() > 1) {
      holding=Serial3.available();  
      for(int i=0; i<holding; i++)
        stamp_data[i]= char(Serial3.read());
        
      PH = atof(stamp_data);
    }
    else {
      PH=0; 
    }
  Serial3.end();  
}

void getWaterTemp(int probe){
  
  openProbeChannel(probe);
  delay(10);  
  OneWire oneWire(15);
  DallasTemperature sensors(&oneWire);
  int numberOfDevices; 
  DeviceAddress tempDeviceAddress;
  sensors.begin();
  delay(10);
  numberOfDevices = sensors.getDeviceCount();

  
  sensors.requestTemperatures();
  for(int i=0;i<numberOfDevices; i++){
    if(sensors.getAddress(tempDeviceAddress, i)){
      float tempC = sensors.getTempC(tempDeviceAddress);
      if(i == 0){
        WT1=tempC;
      }
      else if (i == 1){
        WT2=tempC;
      }
      delay(100);
    }
  }
}

void getAirHumTemp(int probe){
  DHT dht(15, DHT22);
  dht.begin();
  openProbeChannel(probe);
  delay(10);
  AH = dht.readHumidity();
  AT = dht.readTemperature();
  
  if (isnan(AT) || isnan(AH)) {
    Serial.println("Failed to read from DHT");
  }
}


void openProbeChannel(int channel){
    digitalWrite(inh, HIGH);
    delay(5);
    switch (channel) {
      case 0:                         //open channel Y0
        digitalWrite(A, LOW);        //S0=0
        digitalWrite(B, LOW);        //S1=0
        digitalWrite(C, LOW);        //S2=0
      break;

      case 1:                         //open channel Y1
        digitalWrite(A, HIGH);       //S0=1    
        digitalWrite(B, LOW);        //S1=0
        digitalWrite(C, LOW);        //S2=0
      break;

      case 2:                         //open channel Y2   
        digitalWrite(A, LOW);        //S0=0   
        digitalWrite(B, HIGH);       //S1=1
        digitalWrite(C, LOW);        //S2=0
      break;

      case 3:                         //open channel Y3
        digitalWrite(A, HIGH);       //S0=1    
        digitalWrite(B, HIGH);       //S1=1
        digitalWrite(C, LOW);        //S2=0
      break;
      case 4:                         //open channel Y4
        digitalWrite(A, LOW);        //S0=0  
        digitalWrite(B, LOW);        //S1=0
        digitalWrite(C, HIGH);       //S2=1
      break;

      case 5:                         //open channel Y5
        digitalWrite(A, HIGH);       //S0=1    
        digitalWrite(B, LOW);        //S1=0
        digitalWrite(C, HIGH);       //S2=0
      break;

      case 6:                         //open channel Y6   
        digitalWrite(A, LOW);        //S0=0    
        digitalWrite(B, HIGH);       //S1=1
        digitalWrite(C, HIGH);       //S2=0
      break;

      case 7:                         //open channel Y7
        digitalWrite(A, HIGH);       //S0=1    
        digitalWrite(B, HIGH);       //S1=1
        digitalWrite(C, HIGH);       //S2=0
      break;
      default:
      break;
    }
    digitalWrite(inh, LOW);
    delay(5);
//    Serial1.print("\r");  //Get rid of errant data
//    delay(5);
}

void getData(){
  int i=0;
 /* do{
    getProbe(gPH);
    i++;
  }
  while(PH==0 || i<3);
  i=0;
  
  do{
    getAirHumTemp(AHT);
    i++;
  }
  while(PH==0 || i<3);
  i=0;
  */
  do{
    getWaterTemp(DT);
    i++;
  }
  while(PH==0 || i<3);
  i=0;
  
  /*
  Serial.print("PH: ");
  if(PH==0) Serial.println("E404");
  else Serial.println(PH);
  
  Serial.print("AH: ");
  if(AH==0) Serial.println("E404");
  else Serial.println(AH);
  
  Serial.print("AT: ");
  if(AT==0) Serial.println("E404");
  else Serial.println(AT);
  */
  Serial.print("WT1: ");
  if(WT1==0) Serial.println("E404");
  else Serial.println(WT1);
  
  Serial.print("WT2: ");
  if(WT2==0) Serial.println("E404");
  else Serial.println(WT2);
  
}

void loop() {
  
  getData();
}
