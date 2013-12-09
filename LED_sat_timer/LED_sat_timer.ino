int latchPin = 8;
int clockPin = 13;
int dataPin = 11;

byte sh[10]={
 //87654321 
  B00000001,    //0
  B00000010,    //1
  B00000100,    //2
  B00001000,    //3
  B00010000,    //4
  B00100000,    //5
  B01000000,    //6
  B00000000,    //7
  B01111111,    //8
  B00000000};   //9

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
    delay(1000);
  }
} 
