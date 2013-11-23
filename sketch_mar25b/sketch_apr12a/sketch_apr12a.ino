int ledPin = 13;
int inPin = A5;
int lockPin = A4;

String inputString = "";
String nullString = "";
String keyString = "0300C49D207A";

boolean flag1 = false;
boolean flag2 = false;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(lockPin, INPUT_PULLUP);
  pinMode(inPin, INPUT);
}

void loop(){
  if(Serial.available()==0 && flag1){
    flag1=false;
    flag2=false;
    if(inputString == keyString){
      Serial.println("Autorizacija uspjesna!");
      Serial.println("Alarm deaktiviran!");
      digitalWrite(ledPin, 0);
      while(!flag2){
        Serial.read();
        if(digitalRead(lockPin)==0) flag2=true;
      }
      Serial.println("Alarm aktivan!");
    }
  }
  delay(10);
  if (digitalRead(inPin) == HIGH) digitalWrite(ledPin, 1); 
  else digitalWrite(ledPin, 0);
}
void serialEvent() {
  if(!flag1){
    flag1 = true;
    inputString=nullString;
    Serial.read();
    do{
      inputString +=char(Serial.read());
      delay(10);
    }while(inputString.length()<12);
  }else Serial.read();
}

