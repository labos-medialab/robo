#define red 5
#define grn 6

String inputString="", dataString="", tempString="", nullString="", returnString="none";

int latchPin = 8;
int clockPin = 13;
int dataPin = 11;

int rad=12, pauza=5, zag=3;
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
  else if(mode==3) setZag();
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
  if(inputString=="+" && mode==1) rad++;
  if(inputString=="+" && mode==2) pauza++;
  if(inputString=="-" && mode==1) if(rad>0)rad--;
  if(inputString=="-" && mode==2) if(pauza>0)pauza--;
}

void workMode(){
  analogWrite(6,255);
  analogWrite(red,100);
  for (int j = zag; j > 0; j--){
    digitalWrite(latchPin, LOW);
    if(j<=9)shiftOut(dataPin, clockPin, LSBFIRST, sh[j]);
    else shiftOut(dataPin, clockPin, LSBFIRST, sh[j%10]);
    digitalWrite(latchPin, HIGH);
    if (Serial.available()>0) break;
    delay(1000);
  }
  analogWrite(6,0);
  for (int j = rad; j > 0; j--){
    digitalWrite(latchPin, LOW);
    if(j<=9)shiftOut(dataPin, clockPin, LSBFIRST, sh[j]);
    else shiftOut(dataPin, clockPin, LSBFIRST, sh[j%10]);
    digitalWrite(latchPin, HIGH);
    if (Serial.available()>0) break;
    delay(1000);
  }
  analogWrite(red,0);
  analogWrite(grn,255);
  for (int j = pauza; j > 0; j--){
    digitalWrite(latchPin, LOW);
    if(j<=9)shiftOut(dataPin, clockPin, LSBFIRST, sh[j]);
    else shiftOut(dataPin, clockPin, LSBFIRST, sh[j%10]);
    digitalWrite(latchPin, HIGH);
    if (Serial.available()>0) break;
    delay(1000);
  }
  analogWrite(grn,0);
}

void setMode(){
  mode++;
}

void setRad(){
  digitalWrite(latchPin, LOW);
  if(rad<=9)shiftOut(dataPin, clockPin, LSBFIRST, sh[rad]);
  else shiftOut(dataPin, clockPin, LSBFIRST, sh[rad%10]);
  digitalWrite(latchPin, HIGH);
  analogWrite(red,255);delay(500);
  analogWrite(red,0);delay(500);
}

void setPauza(){
  digitalWrite(latchPin, LOW);
  if(pauza<=9)shiftOut(dataPin, clockPin, LSBFIRST, sh[pauza]);
  else shiftOut(dataPin, clockPin, LSBFIRST, sh[pauza%10]);
  digitalWrite(latchPin, HIGH);
  analogWrite(grn,255);delay(500);
  analogWrite(grn,0);delay(500);
}

void setZag(){
  digitalWrite(latchPin, LOW);
  if(zag<=9)shiftOut(dataPin, clockPin, LSBFIRST, sh[zag]);
  else shiftOut(dataPin, clockPin, LSBFIRST, sh[zag%10]);
  digitalWrite(latchPin, HIGH);
  analogWrite(grn,255);delay(500);
  analogWrite(grn,0);delay(500);
}
