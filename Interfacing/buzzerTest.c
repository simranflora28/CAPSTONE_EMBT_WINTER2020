#include <iobb.h>  // Library to access GPIO
#include <stdio.h> // Standard IO library

//https://www.element14.com/community/community/designcenter/single-board-computers/next-genbeaglebone/blog/2019/08/15/beaglebone-black-bbb-io-gpio-spi-and-i2c-library-for-c-2019-edition


int main(void)  
{  
  iolib_init();   //Initializing the iobb library
  iolib_setdir(8, 12, DigitalOut);   //Setting Pin as Output of a specific port 
  while(1)  // Infinite Loop
  {  
    pin_high(8, 12);   // Making the connected pin high
    printf("BUZZER ON \n"); // Message Print
    iolib_delay_ms(500);  //A delay of 500 ms
    
    pin_low(8, 12);   // Making the connected pin low
    printf("BUZZER OFF \n"); // Message Print
    iolib_delay_ms(500);   //A delay of 500 ms
  }  
  iolib_free();  //Free up all the GPIOs
  return(0);  //End of Main Function
}  
