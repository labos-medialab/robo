boolean s=1;
int T=4,Tc=0,t=5,tc=0;

unsigned int stotinka=0,sekunda=0,minuta=0;

void setup(){
  pinMode(4,OUTPUT);pinMode(5,OUTPUT);pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);pinMode(8,OUTPUT);pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);
  Tc=T; tc=t;
  digitalWrite(6, bitRead(Tc,2));
  digitalWrite(5, bitRead(Tc,1));
  digitalWrite(4, bitRead(Tc,0));
  digitalWrite(9, bitRead(tc,2));
  digitalWrite(8, bitRead(tc,1));
  digitalWrite(7, bitRead(tc,0));
}

void loop(){
  if(digitalRead(2)==0){
    delay(10);
    if(digitalRead(2)==0){
      T++;
      if(T==8) T=1;
      Tc=T;
      digitalWrite(6, bitRead(Tc,2));
      digitalWrite(5, bitRead(Tc,1));
      digitalWrite(4, bitRead(Tc,0));
    }
  }
  if(digitalRead(3)==0){
    delay(10);
    if(digitalRead(3)==0){
      t++;
      if(T==8) t=1;
      tc=t;
      digitalWrite(9, bitRead(tc,2));
      digitalWrite(8, bitRead(tc,1));
      digitalWrite(7, bitRead(tc,0));
    }
  }
  if(Tc==0){
    s=1;
    Tc=T;
    digitalWrite(10,s);
  }
  if(tc==0){
    s=0;
    tc=t;
    digitalWrite(10,s);
  }
  if(minuta==30){
    minuta=1;
    Tc--;
    digitalWrite(6, bitRead(Tc,2));
    digitalWrite(5, bitRead(Tc,1));
    digitalWrite(4, bitRead(Tc,0));
  }
  if(sekunda==12){
    sekunda=1;
    minuta++;
  }
  if(stotinka==500){
    stotinka=1;
    sekunda++;
    if(s)tc--;
    digitalWrite(9, bitRead(tc,2));
    digitalWrite(8, bitRead(tc,1));
    digitalWrite(7, bitRead(tc,0));
  }
  stotinka++;
  delay(10);
}
