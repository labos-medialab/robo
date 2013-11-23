String inputString = "";
String nullString = "";

void setup(){
  Serial.begin(9600);
}

void loop(){
  while (Serial.available() > 0) {
    Serial.println("da");
    inputString +=char(Serial.read());
    delay(10);
    if(Serial.available()==0) {
      Serial.println("B1");
      int a=main();
      Serial.println(a);
    }
  }
}

int main(){
  Serial.println("B2");
  int i = 0;
  String *a = new String[10]();
  a[0]="A1";
  a[1]="A2";
  a[2]="A3";
  a[3]="A4";
  a[4]="A5";
  a[5]="A6";
  a[6]="A7";
  a[7]="A8";
  a[8]="A9";
  a[9]="A10";
  
  for(i=0;i<10;i++){
    if(inputString == a[i]); 
    return i;
  }
  inputString=nullString;
}
