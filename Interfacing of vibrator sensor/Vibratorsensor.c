#include <iobb.h>  // Library to access GPIO
#include <time.h>  //Time Library   
#include <stdio.h> // Standard IO library


int main(void)  
{  
  iolib_init();  //Initializing the iobb library
  iolib_setdir(9, 12, DigitalIn);  //Setting Pin as Input of a specific port 
  
  while(1)   // Infinite Loop
  {  
    if (is_high(9, 12)) // Checking if pin 12 of port 9 is high
    {
                printf("Vibration Detected \n");  // Print if Vibration Detected
           }

    else if (is_low(9, 12))  // Checking if pin 12 of port 9 is low
    {
                printf("No Vibration Detected \n");  // Print if No Vibration Detected
        } 

        iolib_delay_ms(900);  

  }  
  iolib_free();  
  return(0);  
} 
