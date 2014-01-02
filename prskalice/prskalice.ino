boolean s=1;
int T=4,Tc=0,t=5,tc=0;

unsigned int stotinka=0,sekunda=0,minuta=0;

void setup(){
  Tc=T; tc=t;
  digitalWrite(6, bitRead(Tc,2));
  digitalWrite(5, bitRead(Tc,1));
  digitalWrite(4, bitRead(Tc,0));
  digitalWrite(9, bitRead(tc,2));
  digitalWrite(8, bitRead(tc,1));
  digitalWrite(7, bitRead(tc,0));
}

void loop(){
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
