/*
  Arduino Yun Bridge example

 This example for the Arduino Yun shows how to use the
 Bridge library to access the digital and analog pins
 on the board through REST calls. It demonstrates how
 you can create your own API when using REST style
 calls through the browser.

 Possible commands created in this shetch:

 * "/arduino/digital/13"     -> digitalRead(13)
 * "/arduino/digital/13/1"   -> digitalWrite(13, HIGH)
 * "/arduino/analog/2/123"   -> analogWrite(2, 123)
 * "/arduino/analog/2"       -> analogRead(2)
 * "/arduino/mode/13/input"  -> pinMode(13, INPUT)
 * "/arduino/mode/13/output" -> pinMode(13, OUTPUT)

 This example code is part of the public domain

 http://arduino.cc/en/Tutorial/Bridge

 */
#include <Wire.h>
#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h>

// Listen on default port 5555, the webserver on the Yun
// will forward there all the HTTP requests for us.
YunServer server;

int blinkPin, fadePin, blinkDelay, i;
int brightness = 0, fadeAmount = 1;
boolean ledState = 0, fade = 0, blink = 0;

void setup() {
  // Bridge startup
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  Bridge.begin();
  Wire.begin();
  server.listenOnLocalhost();
  server.begin();
  digitalWrite(13, LOW);

  // Listen for incoming connection only from localhost
  // (no one from the external network could connect)
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
    if (brightness == 0 || brightness == 255) {
      fadeAmount = -fadeAmount ;
    }
  }
  // Get clients coming from server
  YunClient client = server.accept();

  // There is a new client?
  if (client) {
    // Process request
    process(client);

    // Close connection and free resources.
    client.stop();
  }

  delay(10); // Poll every 50ms
  i++;
}

void process(YunClient client) {
  fade=0; blink=0;
  // read the command
  String command = client.readStringUntil('/');

  // is "digital" command?
  if (command == "digital") {
    digitalCommand(client);
  }

  // is "analog" command?
  if (command == "analog") {
    analogCommand(client);
  }

  // is "mode" command?
  if (command == "mode") {
    modeCommand(client);
  }

  // is "blink" command?
  if (command == "blink") {
    blinkCommand(client);
  }

  // is "blink" command?
  if (command == "fade") {
    fadeCommand(client);
  }

  // is "wire" command?
  if (command == "wire") {
    wireCommand(client);
  }
}

void digitalCommand(YunClient client) {
  int pin, value;

  // Read pin number
  pin = client.parseInt();

  // If the next character is a '/' it means we have an URL
  // with a value like: "/digital/13/1"
  if (client.read() == '/') {
    value = client.parseInt();
    digitalWrite(pin, value);
  }
  else {
    value = digitalRead(pin);
  }

  // Send feedback to client
  client.print(F("Pin D"));
  client.print(pin);
  client.print(F(" set to "));
  client.println(value);
}

void analogCommand(YunClient client) {
  int pin, value;

  // Read pin number
  pin = client.parseInt();

  // If the next character is a '/' it means we have an URL
  // with a value like: "/analog/5/120"
  if (client.read() == '/') {
    // Read value and execute command
    value = client.parseInt();
    analogWrite(pin, value);

    // Send feedback to client
    client.print(F("Pin D"));
    client.print(pin);
    client.print(F(" set to analog "));
    client.println(value);
  }
  else {
    // Read analog pin
    value = analogRead(pin);

    // Send feedback to client
    client.print(F("Pin A"));
    client.print(pin);
    client.print(F(" reads analog "));
    client.println(value);
  }
}

void modeCommand(YunClient client) {
  int pin;

  // Read pin number
  pin = client.parseInt();

  // If the next character is not a '/' we have a malformed URL
  if (client.read() != '/') {
    client.println(F("error"));
    return;
  }

  String mode = client.readStringUntil('\r');

  if (mode == "input") {
    pinMode(pin, INPUT);
    // Send feedback to client
    client.print(F("Pin D"));
    client.print(pin);
    client.print(F(" configured as INPUT!"));
    return;
  }

  if (mode == "output") {
    pinMode(pin, OUTPUT);
    // Send feedback to client
    client.print(F("Pin D"));
    client.print(pin);
    client.print(F(" configured as OUTPUT!"));
    return;
  }
  client.print(F("error: invalid mode "));
  client.print(mode);
}

void blinkCommand(YunClient client) {
  blink=1;
  blinkPin = client.parseInt();

  // If the next character is a '/' it means we have an URL
  // with a value like: "/digital/13/1"
  if (client.read() == '/') {
    blinkDelay = client.parseInt();
  }
  else {
    blinkDelay = 100;
  }

  // Send feedback to client
  client.print(F("Pin D"));
  client.print(blinkPin);
  client.println(F(" set to blink"));
}

void fadeCommand(YunClient client) {
  // Read pin number
  fadePin = client.parseInt();
  brightness = 1;
  if(digitalRead(fadePin)) brightness = 254;
  client.print(F("Pin D"));
  client.print(fadePin);
  client.println(F(" set to fade"));
  fade=1;
}

void wireCommand(YunClient client) {
  byte error;
  int nDevices = 0, address = client.parseInt();
  if(address==0){
    client.print(F("Getting all available addresses:"));
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
    if(nDevices == 0) client.print(F(" No I2C devices found\n"));
    else client.print(F(", done\n"));
  }
  else if(client.read() == '/'){
    String comand = client.readStringUntil('\r');
    byte l=comand.length(), data[l];
    for(byte i=0;i<l;i++) data[i]=comand.charAt(i);
    Wire.beginTransmission(address);
    Wire.write(data,l);
    error = Wire.endTransmission();
    
    client.print(F("Comand: "));
    client.print(comand);
    client.print(F("\nAddress: "));
    client.println(address);
    if(error!=0)client.println(F("FAILED!"));
  }
}
