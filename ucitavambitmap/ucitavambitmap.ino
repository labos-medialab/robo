#include <avr/pgmspace.h>
#include "SPI.h"
#include <UTFT.h>

extern unsigned int 
  Fore[0x400],
  temp[0x400];


extern uint8_t SmallFont[];

UTFT myGLCD(CTE70,38,39,40,41);

void setup()
{
  myGLCD.SPI_Flash_init(45);
  SPI.begin();
  
  myGLCD.InitLCD();
  myGLCD.setFont(SmallFont);
    myGLCD.clrScr();
}

void loop()
{

  myGLCD.drawBitmap(100,100,32,32,temp);
  /*
  myGLCD.show_color_bar();
  myGLCD.Load_image(0,0,287);
*/}
