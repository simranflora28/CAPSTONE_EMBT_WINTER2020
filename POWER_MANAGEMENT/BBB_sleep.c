#include<stdio.h> // Standard C input Output Library.
#include<stdlib.h> // defines four variable types, several macros, and various functions for performing general functions
#include <string.h> // C Library for various String Operations

char command[] = "rtcwake -m standby -s"; //to put beaglebone on sleep mode
char buffer[4];
int sec;

int main()
{	
	
	printf("Enter the Duration of Sleep (in seconds): "); //to print
	scanf("%d", &sec);
	sprintf(buffer, "%d", sec);
	strcat(command,buffer); // to concatenate the string
	printf("Calling Sleep for %d Seconds.\n", sec);
	printf("Notice that all Status Lights on Beaglebone will turn Off.\n\n");
	system(command);
	printf("\n\nWoke Up Again\n");

}
