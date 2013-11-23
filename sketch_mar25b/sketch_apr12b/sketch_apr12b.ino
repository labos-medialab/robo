void setup () {
pinMode (11, OUTPUT);
} void loop ()

{
  for(int i=500;i<2000;i++){
    tone (11,i);
    delay (1);
  }
    for(int i=2000;i>500;i--){
    tone (11,i);
    delay (1);
  }
}
