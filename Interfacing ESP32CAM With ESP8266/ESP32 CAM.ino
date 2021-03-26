#include "WiFi.h" //library included
#define pin 16     // setting pin to connect GPIO Pins of ESP8266 With ESP32 CAM 
#define led 4      // setting pin to display output on LED
#define led_builtin 33 // LED at the back of ESP32 CAM
const char* ssid = "BELL400-Vignesh"; //Required WIFI
const char* password = "BDB@c@0l"; // PASSWORD
void setup() {
 
  Serial.begin(115200);  
 pinMode(pin,INPUT_PULLUP); ///Setting the Pin mode
  pinMode(led,OUTPUT);
    pinMode(led_builtin,OUTPUT);


  int numberOfNetworks = WiFi.scanNetworks(); //function to scan the nearby WIFI 
 
  for(int i =0; i<numberOfNetworks; i++){
 
      Serial.print("Network name: ");  //printed the output on serial monitor
      Serial.println(WiFi.SSID(i));
      Serial.print("Signal strength: "); 
      Serial.println(WiFi.RSSI(i));
      Serial.println("-----------------------");
 
  }
  WiFi.begin(ssid,password); // connect to the WIFI network that we defined above
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(ssid);
  Serial.println(WiFi.SSID());
  Serial.println("connected.");
  Serial.println(WiFi.localIP());
}
void loop() {
  int DATA = digitalRead(pin); //initializing the data to the digital pin
  if(DATA == 0) //if there is no data, LED is OFF
{
    digitalWrite(led,LOW);
    digitalWrite(led_builtin,LOW);
  }
  else //if Data is not Zero
{
     digitalWrite(led,HIGH);
    digitalWrite(led_builtin,HIGH);
  }
}
