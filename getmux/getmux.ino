#include "DHT.h"

int inh = A0;    // Inhibit Line
int A = A3;         // Control pin C 
int B = A2;         // Control pin A
int C = A1;         // Control pin B


char stamp_data[50];
byte holding;
int AHT = 0;
int PH = 1;
int ORP = 2;
int EC = 3;
int DO = 4;

void setup(){ 
  Serial.begin(38400);
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(inh, OUTPUT); 
  digitalWrite(inh, LOW);
}
void getProbe(int probe) {
  Serial3.begin(38400);
    openProbeChannel(probe);
    delay(750);
    Serial3.print("R\r");
    delay(1100);
    holding = 0;
    if(Serial3.available() > 1) {
      holding=Serial3.available();  
      for(int i=0; i<holding; i++)
        stamp_data[i]= char(Serial3.read());
        
      float PHa = atof(stamp_data);
      Serial.println(PHa);
    }
    else {
      Serial.println("probe not available"); 
    }
  Serial3.end();  
}

void getWaterTemp(int probe){
  
}

void getAirHumTemp(int probe){
  DHT dht(15, DHT22);
  dht.begin();
  openProbeChannel(probe);
  delay(750);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  if (isnan(t) || isnan(h)) {
    Serial.println("Failed to read from DHT");
  } else {
    Serial.print("Humidity: "); 
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperature: "); 
    Serial.print(t);
    Serial.println(" *C");
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
    Serial1.print("\r");  //Get rid of errant data
    delay(50);
}

void loop() {
  getProbe(PH);
  getAirHumTemp(AHT);
  

}
