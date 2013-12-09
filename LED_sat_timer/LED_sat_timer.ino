#define red 5
#define grn 6

String inputString="", dataString="", tempString="", nullString="", returnString="none";

int latchPin = 8;
int clockPin = 13;
int dataPin = 11;

int rad=8, pauza=5;
int mode=0;

byte sh[10]={
 //87654321 
  B01110111,    //0
  B01000001,    //1
  B01101110,    //2
  B01101011,    //3
  B01011001,    //4
  B00111011,    //5
  B00111111,    //6
  B01100001,    //7
  B01111111,    //8
  B01111011};   //9

void setup(){
  Serial.begin(9600);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop(){
  if(mode==0) workMode();
  else if(mode==1) setRad();
  else if(mode==2) setPauza();
  else mode=0;
}

void serialEvent(){
  inputString=nullString;
  while(Serial.available()>0){
    inputString+=(char)Serial.read();
    delay(10);
  }
  stringHandle();
}

void stringHandle(){
  if(inputString=="0") setMode();
}

void workMode(){
  analogWrite(red,255);
  for (int j = rad; j >= 0; j--){
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, sh[j]);
    digitalWrite(latchPin, HIGH);
    if (Serial.available()>0) break;
    delay(1000);
  }
  analogWrite(red,0);
  analogWrite(grn,255);
  for (int j = pauza; j >= 0; j--){
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, sh[j]);
    digitalWrite(latchPin, HIGH);
    if (Serial.available()>0) break;
    delay(1000);
  }
  analogWrite(grn,0);
}

void setMode(){
  mode++; Serial.println(mode);
}

void setRad(){
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, sh[rad]);
  digitalWrite(latchPin, HIGH);
  analogWrite(red,255);delay(500);
  analogWrite(red,0);delay(500);
}

void setPauza(){
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, sh[pauza]);
  digitalWrite(latchPin, HIGH);
  analogWrite(grn,255);delay(500);
  analogWrite(grn,0);delay(500);
}
