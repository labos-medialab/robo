byte state=0;
byte r=0, nr=0, red=255;
byte g=0, ng=0, grn=255;
byte b=0, nb=0, blu=255;

int R=9, G=10, B=11;

void setup(){
  Serial.begin(115200);
  pinMode(13, OUTPUT);
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(8, OUTPUT);
  digitalWrite(8, LOW);
}
void loop(){
  int avg=0, sum=0, avg1=0;
  
  for(int i=1; i<100; i++){
    int a=analogRead(A0);
    if(a==0) i--; 
    sum+=a;
    avg=sum/i;
  }
  sum=0;
  Serial.println(avg);
  for(int i=1; i<100; i++){
    int a=analogRead(A0);
    if(a==0) i--; 
    sum+=a;
    avg1=sum/i;
  }
  Serial.println(avg1);
  if(avg != avg1) state++;
  
  if(state==0){nr=0;ng=0;nb=0;}
  if(state==1){nr=255;nb=255;ng=255;}
  if(state==2){nb=0;ng=0;}//r=255
  if(state==3){nb=255;}//r,b=255
  if(state==4){nr=0;}//b=255
  if(state==5){ng=255;}//b,g=255
  if(state==6){nb=0;}//g=255
  if(state==7){nr=255;}//g,r=255
  if(state==8){state=0;}//0
  
  while(nr != r || ng != g || nb != b){
    digitalWrite(13,1);
    if(r < nr) r++; if(r > nr) r--;
    if(g < ng) g++; if(g > ng) g--;
    if(b < nb) b++; if(b > nb) b--;
    
    delay(5);
    
    analogWrite(R, map(r, 0, 255, 0, red));Serial.print(r);Serial.print(" ");
    analogWrite(G, map(g, 0, 255, 0, grn));Serial.print(g);Serial.print(" ");
    analogWrite(B, map(b, 0, 255, 0, blu));Serial.println(b);
    digitalWrite(13,0);
  }  
}
