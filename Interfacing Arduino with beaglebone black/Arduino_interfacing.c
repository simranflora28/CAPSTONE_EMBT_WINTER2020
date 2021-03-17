#include <stdio.h> //Standard C input Output Library
#include <unistd.h> //defines miscellaneous symbolic constants and types, and declares miscellaneous functions
#include <string.h> //C Library for various String Operations
#include <termios.h> // Contains the definitions used by the terminal I/O interfaces 
#include <fcntl.h> // FIle control, Open, close
#include <time.h>


#define BAUDRATE B9600

//Reference Link: https://electronics.trev.id.au/2018/02/09/get-uart-serial-ports-working-beaglebone-black/
// https://stackoverflow.com/questions/6947413/how-to-open-read-and-write-from-serial-port-in-c
// https://www.wikitechy.com/tutorials/linux/how-to-open-read-and-write-from-serial-port-in-c
// https://linux.die.net/man/3/open

 
 int main (void) // Main function
{
    int f1, i; // Variable integers
    char incomingbuffer[1000]; // declare a char array for receiving data
    char buf[20]; // A buffer char array to store temporary data
    
    size_t nbytes; //size_t is an unsigned integer data type used for storing size
    ssize_t outgoing_data; // //size_t is an signed integer data type used for storing size
	
	// /dev/ttyO4 is linked with UART4 Port of Beaglebone 
    if ((f1 = open("/dev/ttyO4", O_RDWR | O_NOCTTY | O_NONBLOCK))<0){ // Try opening the UART4 f1 in Read Write mod
		
        printf("UART: Failed to open the f1.\n"); //A message Print
        return 0;
    }
    
    else{	
    printf("UART: Started\n"); //A message Print
		
	}

    struct termios options;
    /* set new port settings for canonical input processing */
    options.c_cflag = BAUDRATE | CRTSCTS | CS8 | CLOCAL | CREAD; //  CLOCAL - It will ignore Data Carrier Signal
	//CS8 = Select 8 data bits
	// CREAD = Enable Receiving Characters
	// CRTSCTS = Automaticall handle RTS (Request to Send) and CTS(Clear to Send)
    options.c_iflag = IGNPAR | ICRNL; // IGNPAR = IGNORE PARITY, ICRNL - Use CR & NL as Break Line
    options.c_oflag = 0; //output mode flag
    options.c_lflag = ICANON; //Waits for complete line to come
    options.c_cc[VMIN]=2; // Minimum wait Time
    options.c_cc[VTIME]=20; //Maximum Wait Time
    tcflush(f1, TCIFLUSH); //Flush all the Input Data
    tcsetattr(f1,TCSANOW,&options);  // TCSANOW - Any change made should be applied immediately
    tcflush(f1, TCIOFLUSH); // Flush ALl the Input and Outputs
    sleep(1); // Wait for a second

    while(1)
    {

    	memset(buf, 0, sizeof(buf)); // Clear any old data in buffer
        strcpy(buf, "WE ARE GROUP 2\n"); // Copy a string in buf char array
        nbytes = strlen(buf); // Store size of buf array in nbytes
        outgoing_data = write(f1, buf, nbytes); // Sending message to Arduino Module
        printf("Sent Bytes: ");
        sleep(2);// Allowing time to make sure that ARduino has read the data
        printf("%d \n", outgoing_data);// print the bytes sent
    	int incoming_data = 0;
    	incoming_data = read(f1,&incomingbuffer,100); // Read the incoming Message from Arduino Module
    	//Read the f1 and store the data in incomingbuffer[, read 100 bytes max
    	//Will only execute if newline or carriage return is received
    	printf("\n\nBytes Received - %d",incoming_data); // Print how many bytes was incomingbuffer[
    	printf("\n");
    	
    	if(incoming_data > 1) //If no. of bytes are read is more than 1
    	{
    		for(i=0;i<incoming_data;i++) //a for loop to print data byte by byte
    		{
    			printf("%c",incomingbuffer[i]); //print a byte of message from Arduino Module
    		}
    		printf("\n");

            sleep(2);
    	}

	}
    close(f1); //Close the f1 at last
}
