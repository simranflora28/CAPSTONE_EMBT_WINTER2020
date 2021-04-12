
#include <Arduino.h> //to handle functions and other stuff
#include <SPI.h> //for spi communication

#include "Adafruit_ILI9341esp.h" //for TFT screen 
#include "Adafruit_GFX.h"   //for graphics
#include "XPT2046.h" //touch screen controller

#define TFT_DC 2 // connections of screen with nodemcu
#define TFT_CS 15
int e = 0; //declaring the integer and string as variable
String d ;
/* UI details for buttons */
#define BUTTON_X 40
#define BUTTON_Y 100
#define BUTTON_W 60
#define BUTTON_H 25
#define BUTTON_SPACING_X 20
#define BUTTON_SPACING_Y 20
#define BUTTON_TEXTSIZE 2

// defining text box where numbers go
#define TEXT_X 10
#define TEXT_Y 10
#define TEXT_W 220
#define TEXT_H 50
#define TEXT_TSIZE 2.5
#define TEXT_TCOLOR ILI9341_GREEN

#define TEXT_LEN 12 //defining the length for text field
char textfield[TEXT_LEN + 1] = ""; 
uint8_t textfield_i = 0; //initializing text field with zero

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC); //making the tft obeject 
XPT2046 touch(/*cs=*/ 4, /*irq=*/ 5); // defining the parameters for touch

char buttonlabels[15][5] = {"ENT", "Clr", "-", "1", "2", "3", "4", "5", "6", "7", "8", "9", "*", "0", "#" }; //declaring the buttons 
uint16_t buttoncolors[15] = {ILI9341_DARKGREEN, ILI9341_DARKGREY, ILI9341_YELLOW, 
                             ILI9341_RED, ILI9341_RED, ILI9341_RED,
                             ILI9341_RED, ILI9341_RED, ILI9341_RED,
                             ILI9341_RED, ILI9341_RED, ILI9341_RED,
                             ILI9341_ORANGE, ILI9341_RED, ILI9341_ORANGE
                            }; // defining the colour
Adafruit_GFX_Button buttons[15]; // total count of buttons
  String c; // initializing the string
void setup() {
  delay(1000);

  Serial.begin(115200);
  //SPI.setFrequency(ESP_SPI_FREQ);
  fg(); // defining the function


}
void fg() {
  #define TEXT_LEN 12 ////defining the length for text field
char textfield[TEXT_LEN + 1] = "";  // entered content should increment by 1
uint8_t textfield_i = 0;
  tft.begin(); // initializing the screen 
  touch.begin(tft.width(), tft.height());  // Must be done before setting rotation
  Serial.print("tftx ="); Serial.print(tft.width()); Serial.print(" tfty ="); Serial.println(tft.height());
  tft.fillScreen(ILI9341_BLACK);

  // calibration values for my screen 
  touch.setCalibration(1832, 262, 264, 1782);
  // create buttons
  for (uint8_t row = 0; row < 5; row++) {
    for (uint8_t col = 0; col < 3; col++) {
      buttons[col + row * 3].initButton(&tft, BUTTON_X + col * (BUTTON_W + BUTTON_SPACING_X),
                                        BUTTON_Y + row * (BUTTON_H + BUTTON_SPACING_Y), // x, y, w, h, outline, fill, text
                                        BUTTON_W, BUTTON_H, ILI9341_WHITE, buttoncolors[col + row * 3], ILI9341_WHITE,
                                        buttonlabels[col + row * 3], BUTTON_TEXTSIZE);
      buttons[col + row * 3].drawButton(); 
    }
  }

  tft.drawRect(TEXT_X, TEXT_Y, TEXT_W, TEXT_H, ILI9341_WHITE); // creating the text field 

}
void loop() {
  uint16_t x, y;
  if (touch.isTouching())
    touch.getPosition(x, y);

  for (uint8_t b = 0; b < 15; b++) {
    if (buttons[b].contains(x, y)) {
      buttons[b].press(true);  // tell the button it is pressed
    } else {
      buttons[b].press(false);  // tell the button it is NOT pressed
    }
  }

  for (uint8_t b = 0; b < 15; b++) {
    if (buttons[b].justReleased()) {
      buttons[b].drawButton();  // draw normal
    }

    if (buttons[b].justPressed()) {
      buttons[b].drawButton(true);  // draw invert!

      if (b >= 3)// help in reading the values for screen  { 
        if (textfield_i < TEXT_LEN) {
          textfield[textfield_i] = buttonlabels[b][0];
          textfield_i++;
          textfield[textfield_i] = 0; // zero terminate
        }
      }
      if (b == 1) // required for the functioing of clr button  { 

        textfield[textfield_i] = 0;
        if (textfield > 0) {
          textfield_i--;
          textfield[textfield_i] = ' ';
        }
      }

      // update the current text field
      Serial.println(textfield);
      tft.setCursor(TEXT_X + 2, TEXT_Y + 10);
      tft.setTextColor(TEXT_TCOLOR, ILI9341_BLACK);
      tft.setTextSize(TEXT_TSIZE);
      tft.print(textfield);

     


       c = textfield;
      if (c == "690" || c == "137") // setting the password for two users {
         d = textfield;
        if (d == "690" || d == "137") {
          e += 1;
        }
      }
      else{
        if(c.length() >= 3){
          tft.fillScreen(ILI9341_BLACK);
            c = textfield;
          tft.print(" SORRY WRONG ONE");//msg display on screen 
          delay(5000); //delay of 5 secs
              
       int lengthr = c.length(); //help to clear the screen 
       Serial.print(lengthr);
        for(int j = 0;j<lengthr;j++){
        textfield[textfield_i] = 0;
        if (textfield > 0) {
          textfield_i--;
          textfield[textfield_i] = ' ';
        }  
          
        }
        fg();  // again the function is called 
      }
      }
      
      
    if (e >= 2) // here 2 means we are defining the two users  {
        e = 0;
        tft.setCursor(TEXT_X , TEXT_Y);
        tft.fillScreen(ILI9341_BLACK);
        if(d == "690") //first user 
        {
        tft.print(" WELCOME OWNER "); //msg printed on screen 
        }
        else if(d == "137") //second user 
        {
       tft.print(" WELCOME CO-OWNER "); //msg printed on screen 

        }
        delay(5000);  //delay of 5 secs 
       
       int lengthr = c.length(); // again update the screen with cleaaring everything 
       Serial.print(lengthr);
        for(int j = 0;j<lengthr;j++){
        textfield[textfield_i] = 0;
        if (textfield > 0) //text field is >zero 
        {
          textfield_i--; //decrement starts
          textfield[textfield_i] = ' ';
        }  
       
     
      }
      }

 
    }
  }
  
}
