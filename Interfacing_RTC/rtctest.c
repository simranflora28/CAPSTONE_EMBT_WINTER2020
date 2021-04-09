#include <stdio.h> // Standard IO library
#include <unistd.h> //defines miscellaneous symbolic constants and types, and d$
#include <stdlib.h> //Includes some Standard C Libraries used for trigerring Co$



int main(void)  
{  

        while(1)
        {      
        system("hwclock -r -f /dev/rtc0"); // Ping the Web link using Command l$
        printf("Above is the RTC Time \n");
        }

        return(0);  
 
   
}
