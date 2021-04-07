#include <Adafruit_GFX.h>       // include Adafruit graphics library
#include <Adafruit_ILI9341.h>   // include Adafruit ILI9341 TFT library
#define TFT_CS    D2     // TFT CS  pin is connected to NodeMCU pin D2
#define TFT_RST   D3     // TFT RST pin is connected to NodeMCU pin D3
#define TFT_DC    D4     // TFT DC  pin is connected to NodeMCU pin D4
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
void setup() {
  tft.begin(); //Intializing the screen 
  tft.fillScreen(ILI9341_BLACK);//filling the screen with black colour
  tft.setCursor(10, 140); //setting the cursor for the desired output
  tft.setTextColor(ILI9341_RED); //setting the textcolour  
  tft.setTextSize(2.5);//setting the text size 
  tft.print(" !!GROUP 2 ROCKS!! ");//printing the text on touch screen

 tft.setCursor(15, 175);//setting the cursor
 tft.setTextColor(ILI9341_WHITE); //setting the textcolour
 tft.setTextSize(2.5);//setting the text size
 tft.println(" TOUCHSCREEN IS ON  ");//printing the text on screen
}
void loop(void) 
{
}
