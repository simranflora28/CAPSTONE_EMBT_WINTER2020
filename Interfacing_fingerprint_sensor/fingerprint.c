#include <Adafruit_Fingerprint.h> // Adafruit Fingerprint Sensor Library

#define mySerial Serial2 //Serial Port where Fingerprint is connected

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);// Initialize Fingerprint Port

// Below 3 values needs to be updated manually
int pcount = 3; // Total Enrolled person
int ids[3] =          {1,      2,        3}; //Enrolled Fingerprint Id's of individual person in Serial order
String names[3] = {"Simran", "FLORA", "SAINI"}; // Name of Individuals in Serial order


uint8_t id = 0; //To store Finger ID
int mode = 0; //Mode to decide if Fingerprint Sensor is in enroll mode or detect mode
int detected = 0;
void setup()
{
  Serial.begin(9600);//Initialize Serial Communication
  delay(100);
  Serial.println("\n\nAdafruit Fingerprint sensor enrollment");

  // set the data rate for the sensor serial port
  finger.begin(57600);//Initialize Serial Communication with Fingerprint Module

  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!"); //FIngerprint Found
  } else {
    Serial.println("Did not find fingerprint sensor :("); //Fingerprint not Found
    while (1) { delay(1); } //Wait if Fingerprint not found
  }

  finger.getTemplateCount(); //Get how many fingerprints are enrolled till now

  if (finger.templateCount == 0) { //If Template Count is 0
    Serial.print("Sensor doesn't contain any fingerprint data. Please run the 'enroll' example.");
  }
  else {
      Serial.println("Waiting for valid finger...");
      Serial.print("Sensor contains "); 
      Serial.print(finger.templateCount); 
      Serial.println(" templates");
  }

  delay(100); // Wait for a second

  Serial.println("Enter 'enroll' for enrollment or 'detect' for detection."); // A message to USer
  
}

uint8_t readnumber(void) {
  uint8_t num = 0;

  while (num == 0) {
    while (! Serial.available());
    String input = Serial.readString();
    if(input.indexOf("enroll") != -1)
    {
      Serial.println("Enroll Mode Activated");
      mode = 1;
    }
    else if(input.indexOf("detect") != -1)
    {
      Serial.println("Detect Mode Activated");
      mode = 0;
    }
    else if(input.indexOf("delete") != -1)
    {
      Serial.println("Deleting all");
      mode = 2;
    }
    else
    {
      num = input.toInt();
    }
  }
  return num;
}

void loop()                     // run over and over again
{
  if (Serial.available())
  {
    String input = Serial.readString();
    
    if(input.indexOf("enroll") != -1)
    {
      Serial.println("Enroll Mode Activated");
      mode = 1;
    }
    else if(input.indexOf("detect") != -1)
    {
      Serial.println("Detect Mode Activated");
      mode = 0;
    }
    else if(input.indexOf("delete") != -1)
    {
      Serial.println("Deleting all");
      mode = 2;
    }
  }

  if(mode == 0) //If Mode is 0 - means Detection mode
  {
    getFingerprintID();
    if(detected > 0)
    {
    for (int i = 0; i < pcount; i++)
    {
      if(ids[i] == detected)
      {
        Serial.print("Person Name is: ");
        Serial.println(names[i]);
        break;
      }
    }
    }
    detected = 0;
    delay(200);            //don't ned to run this at full speed.
  }


  if(mode == 1) // If mode is 1 - means enrollment mode
  {  
    Serial.println("Ready to enroll a fingerprint!");
    Serial.println("Please type in the ID # (from 1 to 127) you want to save this finger as...");
    id = readnumber();
    if (id == 0) {// ID #0 not allowed, try again!
       return;
    }
    Serial.print("Enrolling ID #");
    Serial.println(id);
  
    while (!  getFingerprintEnroll() );
 
  }

  if (mode == 2)
  {
    finger.emptyDatabase();
    Serial.println("Now database is empty :)");

    delay(1000);
    mode = 1;
  }
 
}

uint8_t getFingerprintEnroll() {
  int p = -1;
  Serial.print("Waiting for valid finger to enroll as #"); Serial.println(id);
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      break;
    default:
      Serial.println("Unknown error");
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      //Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      //Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      //Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  Serial.println("Remove finger");
  delay(2000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }
  Serial.print("ID "); Serial.println(id);
  p = -1;
  Serial.println("Place same finger again");
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.print(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      //Serial.println("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      break;
    default:
      Serial.println("Unknown error");
      break;
    }
  }

  // OK success!

 p = finger.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      //Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      //Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      //Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK converted!
  Serial.print("Creating model for #");  Serial.println(id);

  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    Serial.println("Prints matched!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
    Serial.println("Fingerprints did not match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }

  Serial.print("ID "); Serial.println(id);
  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
    Serial.println("Stored!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Could not store in that location");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error writing to flash");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }

  return true;
}

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      //Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      //Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      //Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK converted!
  p = finger.fingerSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    //Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }

  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID);
  Serial.print(" with confidence of "); Serial.println(finger.confidence);

  detected = finger.fingerID;
  return finger.fingerID;
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;

  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID);
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  return finger.fingerID;
}
