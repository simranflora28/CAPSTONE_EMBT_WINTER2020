int received = 0;
void setup() {
  // initialize both serial ports:
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {
  // read from port 1, send to port 0:
  if (Serial1.available()) {
    int inByte = Serial1.read();
    Serial.write(inByte);
  }

  // read from port 0, send to port 3:
  if (Serial.available()) 
  {
    received = 1;
    while(Serial.available())
    {
      int inByte = Serial.read();
      Serial1.write(inByte);
      delay(2);
    }
  }
  
  if(received == 1)
  {
    Serial.println("Data Sent to Beaglebone.");
    Serial1.println();
    received = 0;
  }
  
}
