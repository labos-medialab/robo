//outputs
const int G[10]={3,5,6,9,10,11,4,7,8,13};

#define latch 4
#define clock 7
#define sdata 8
#define ledP 13

//shift bytes
byte sh[12]={B01010001,B01010010,B01010100,
             B01010101,B01010110,B01011100,
             B01011001,B01011010,B01011100,
             B11111111,B01010101,B01010110};

//inputs
const int A[6]={14,15,16,17,18,19};

//buttons
const int plusB=1, minusB=0, okB=2;

//temperatures
int Temp[6]={250,76,84,22,-25,63};
byte setTemp[6]={150,200,150,200,150,200};

//flags
byte flag = B00111111;

void setup(){
  /**/
  Serial.begin(9600);/*serial cinection*/
  /**/
  for(byte i=0; i<10; i++)
  pinMode(G[i], OUTPUT);/*Set outputs as output*/
  /**/
  for(byte i=0; i<3; i++)
  pinMode(i, INPUT_PULLUP);/*Set buttons as inputs*/
}

void loop(){
  /**/
  digitalWrite(ledP, LOW);
  digitalWrite(latch, LOW);
  for(byte i=0; i<6; i++){
    if(bitRead(flag, i)){
      Temp[i]=map(analogRead(A[i]),0,1024,-99,500);
      if(Temp[i]>=setTemp[i]+2)digitalWrite(G[i],0);
      if(Temp[i]<=setTemp[i]-2)digitalWrite(G[i],1);
      shiftOut(sdata,clock,LSBFIRST,sh[Temp[i]%10]);
      shiftOut(sdata,clock,LSBFIRST,sh[(Temp[i]/10)%10]);
      shiftOut(sdata,clock,LSBFIRST,sh[Temp[i]/100]);
      shiftOut(sdata,clock,LSBFIRST,sh[setTemp[i]%10]);
      shiftOut(sdata,clock,LSBFIRST,sh[(setTemp[i]/10)%10]);
      shiftOut(sdata,clock,LSBFIRST,sh[setTemp[i]/100]);
    }
  }
  digitalWrite(latch, HIGH);
  digitalWrite(ledP, HIGH);
  /**/
}
