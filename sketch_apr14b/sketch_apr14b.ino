int ledPin = 13;
int inPin = A5;
int lockPin = A4;

String inputString = "";
String nullString = "";
String keyString = "0300C49D207A";

boolean flag1 = false;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(lockPin, INPUT_PULLUP);
  pinMode(inPin, INPUT_PULLUP);
}

void loop(){
  
  if(Serial.available()>0){
    serial1();
    if(Serial.available()==0 && inputString!=nullString){
      flag1=false;
      if(inputString == keyString){
        Serial.println("Autorizacija uspjesna!");
        Serial.println("Alarm deaktiviran!");
        digitalWrite(ledPin, 0);
        while(!flag1){
          Serial.read();
          if(digitalRead(lockPin)==0) flag1=true;
        }
        inputString=nullString;
        Serial.println("Alarm aktivan!");
      }
    }
  }
  delay(10);
  
  if (digitalRead(inPin) == HIGH) digitalWrite(ledPin, 1); 
  else digitalWrite(ledPin, 0);

}//loop

void serial1() { 
  Serial.read();
  delay(10);
  while(inputString.length()<12){
    inputString +=char(Serial.read());
    delay(10);
  } 
  Serial.read();
}
