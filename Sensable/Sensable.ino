int s0 = A3;         // Control pin A
int s1 = A2;         // Control pin B
int s2 = A1;         // Control pin C 
int inhibit = A0;    // Inhibit Line

char stamp_data[50];
byte holding;
int PH = 1;
int ORP = 2;
int EC = 3;
int DO = 4;

void setup(){     
  Serial3.begin(38400);
  Serial.begin(38400);
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(inhibit, OUTPUT); 
  digitalWrite(inhibit, LOW);
}
void getProbe(int probe) {
    int i;
    openProbeChannel(probe);
    delay(750);
    Serial3.print("R\r");
    delay(1100);
    holding = 0;
    if(Serial3.available() > 1) {
      holding=Serial3.available();  
      for(i=0; i<holding; i++)
        stamp_data[i]= Serial3.read();
      Serial.print(probe);
      Serial.print(": ");
      for(i=0; i<holding; i++)        
        Serial.print(stamp_data[i]);
      Serial.println(""); 
    }
    else {
      Serial.println("probe not available"); 
    }   
}

void openProbeChannel(int channel){
    digitalWrite(inhibit, HIGH);
    delay(5);
    switch (channel) {
      case 0:                         //open channel Y0
        digitalWrite(s0, LOW);        //S0=0
        digitalWrite(s1, LOW);        //S1=0
        digitalWrite(s2, LOW);        //S2=0
      break;

      case 1:                         //open channel Y1
        digitalWrite(s0, HIGH);       //S0=1    
        digitalWrite(s1, LOW);        //S1=0
        digitalWrite(s2, LOW);        //S2=0
      break;

      case 2:                         //open channel Y2   
        digitalWrite(s0, LOW);        //S0=0   
        digitalWrite(s1, HIGH);       //S1=1
        digitalWrite(s2, LOW);        //S2=0
      break;

      case 3:                         //open channel Y3
        digitalWrite(s0, HIGH);       //S0=1    
        digitalWrite(s1, HIGH);       //S1=1
        digitalWrite(s2, LOW);        //S2=0
      break;
      case 4:                         //open channel Y4
        digitalWrite(s0, LOW);        //S0=0  
        digitalWrite(s1, LOW);        //S1=0
        digitalWrite(s2, HIGH);       //S2=1
      break;

      case 5:                         //open channel Y5
        digitalWrite(s0, HIGH);       //S0=1    
        digitalWrite(s1, LOW);        //S1=0
        digitalWrite(s2, HIGH);       //S2=0
      break;

      case 6:                         //open channel Y6   
        digitalWrite(s0, LOW);        //S0=0    
        digitalWrite(s1, HIGH);       //S1=1
        digitalWrite(s2, HIGH);       //S2=0
      break;

      case 7:                         //open channel Y7
        digitalWrite(s0, HIGH);       //S0=1    
        digitalWrite(s1, HIGH);       //S1=1
        digitalWrite(s2, HIGH);       //S2=0
      break;
      default:
      break;
    }
    digitalWrite(inhibit, LOW);
    delay(5);
    Serial1.print("\r");  //Get rid of errant data
    delay(50);
}   

void loop() {
  delay(2000);
  getProbe(PH);  

}
