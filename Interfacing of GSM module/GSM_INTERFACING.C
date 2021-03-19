#define GSMS Serial3 // Storing Serial3 value in GSMS
#define message "YOUR BANK LOCKER DOOR IS OPENED!!!" //Storing message

String number1 = "+12269898619"; // Mobile number 

//https://randomnerdtutorials.com/sim900-gsm-gprs-shield-arduino/

void setup() {

  // Open serial communications and wait for port to open:
  Serial.begin(19200); // BAud Rate for Arduino Mega is 19200
  GSMS.begin(19200); //Baud Rate for GSM Module is 19200

  Serial.println("STARTING"); //A message to User

  delay(20000); //Delay for GSM Module to get connected to Network

  Serial.println("STARTED\n\n"); ////A message to User

  Serial.print("Number 1: ");
  Serial.println(number1); //A message to User

}

void loop() 
{

  sendSMS(); // Calling SMS sending Function
  delay(60000); // delay of 1 minute
 
}


/////////////// Function to Send SMS ///////////////////////////

void sendSMS() 
{
  
  Serial.print("Trying to send SMS to : ");
  Serial.println(number1);//A message to User
  
  GSMS.println("AT+CMGS=\""+number1+"\""); // Command to start making SMS for given number
  delay(100); // A small delay
  
  GSMS.print(message); //text content for the message
  delay(100); // A small delay
  
  GSMS.write(26); // Sending 26 will make GSM module to send the SMS
  delay(100); // A small delay
  
  Serial.println("SMS sending Done");//A message to User
  
// delay(5000); //Small delay before making Call 
//  Serial.print("Making a Call to: ");
//  Serial.println(number1);
//  
//  GSMS.println("ATD + " + number1+";");
//
//  delay(30000);
//  // AT command to hang up
//  Serial.println("Hanging the Call");
//  GSMS.println("ATH"); // hang up
  
}
