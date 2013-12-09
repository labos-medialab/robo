int latchPin = 8;
int clockPin = 13;
int dataPin = 11;

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
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop(){
  analogWrite(5,255);
  for (int j = 0; j < 10; j++){
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, sh[j]);
    digitalWrite(latchPin, HIGH);
    delay(500);
  }
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, 0);
  digitalWrite(latchPin, HIGH);
  delay(1000);
} 
