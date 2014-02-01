#include <Wire.h>
#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h>

YunServer server;

int blinkPin, fadePin, blinkDelay, i;
int brightness = 0, fadeAmount = 1;
boolean ledState = 0, fade = 0, blink = 0;

void setup() {
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  Bridge.begin();
  Wire.begin();
  server.listenOnLocalhost();
  server.begin();
  digitalWrite(13, LOW);
}

void loop() {

  if(i<0)i=0;
  if(blink && i>=blinkDelay){
    ledState=!ledState;
    digitalWrite(blinkPin,ledState);
    i=0;
  }

  if(fade){
    analogWrite(fadePin, brightness);
    brightness = brightness + fadeAmount;
    if (brightness == 0 || brightness == 255){
      fadeAmount = -fadeAmount ;
    }
  }

  YunClient client=server.accept();
  if (client){
    int pin, value;
    fade=0; blink=0;
    char command = client.read();

    if (command == 'd'){
      pin = client.parseInt();
      if (client.read() == '/'){
        value = client.parseInt();
        digitalWrite(pin, value);
      }
      else value = digitalRead(pin);
      client.print(F("D"));
      client.println(pin);
      client.println(value);
    }

    if (command == 'a') {
      pin = client.parseInt();
      if (client.read() == '/'){
        value = client.parseInt();
        analogWrite(pin, value);
        client.print(F("D"));
        client.println(pin);
        client.println(value);
      }
      else{
        value = analogRead(pin);
        client.print(F("A"));
        client.println(pin);
        client.println(value);
      }
    }

    if (command == 'b'){
      blink=1;
      blinkPin = client.parseInt();
      if (client.read() == '/') blinkDelay = client.parseInt();
      else blinkDelay = 50;
      client.print(F("D"));
      client.println(blinkPin);
      client.println(F("blink"));
    }

    if (command == 'f'){
      fadePin = client.parseInt();
      brightness = 1;
      if(digitalRead(fadePin)) brightness = 254;
      client.print(F("D"));
      client.println(fadePin);
      client.println(F("fade"));
      fade=1;
    }

    if (command == 'w'){
      byte error;
      int nDevices = 0, address = client.parseInt();
      if(address==0){
        client.print(F("Available addresses:"));
        for(int i=1; i<127; i++){
          Wire.beginTransmission(i);
          error = Wire.endTransmission();
          if(error==0){
            if(nDevices==0){
              client.print(F(" "));
              client.print(i);
            }
            else{
              client.print(F(", "));
              client.print(i);
            }
            nDevices++;
          }
        }
        if(nDevices == 0)
        client.print(F(" No I2C devices\n"));
      }
      else if(client.read() == '/'){
        String comand = client.readStringUntil('\r');
        byte l=comand.length(), data[l];
        for(byte i=0;i<l;i++) data[i]=comand.charAt(i);
        Wire.beginTransmission(address);
        Wire.write(data,l);
        error = Wire.endTransmission();
        client.print(address);
        client.print(F(": "));
        client.println(comand);
        if(error!=0)client.println(F("E404"));
      }
    }
    client.stop();
  }
  delay(10);
  i++;
}
