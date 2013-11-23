int a,avg=0,min=10000,max=0;
unsigned long k=0,sum=0;
void setup(){
  Serial.begin(115200);
}
void loop(){
  a=analogRead(A0);
  if(a<min) min=a;
  if(a>max) max=a;
  sum+=a;
  k++;
  avg=sum/k;
  if(a!=min && a!=avg && a!=max){
  Serial.print(k);
  Serial.print(" ");
  Serial.print(a);
  Serial.print(" ");
  Serial.print(min);
  Serial.print(" ");
  Serial.print(avg);
  Serial.print(" ");
  Serial.println(max);}
}
