#define pin D0    //setting the GPIO Pin
void setup() 
{
pinMode(pin,OUTPUT);      //setting the pin at output
Serial.begin(9600);            //setting the baund rate
}
void loop() 
{
digitalWrite(pin,HIGH);   //function used to write a high value to a digital pin
delay(2000);
digitalWrite(pin,LOW); //function used to write a low value to a digital pin
delay(2000);
}
