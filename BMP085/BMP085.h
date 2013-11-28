#ifndef bmp085_h
#define bmp085_h

//#include <Wire.h>

void bmp085Calibration();
float bmp085GetTemperature(unsigned int ut);
long bmp085GetPressure(unsigned long up);

unsigned int bmp085ReadUT();
unsigned long bmp085ReadUP();
float calcAltitude(float pressure);

#endif
