#include "esp_camera.h" //Camera Library for ESP
#include "SPI.h" //SPI Library
#include "driver/rtc_io.h" //Library for Time, Time sync is needed for sending mail
#include "ESP32_MailClient.h" //Mail Library to Send Mail
#include <FS.h> //File System Library to acess files
#include <SPIFFS.h>// SPI File System Library to access files from SD Card
#include <WiFi.h> //WiFi Library to access WiFi 

const char* ssid = "gaetonde"; //WiFi SSID
const char* password = "Trivedii"; //WIFi Password

//Reference: https://randomnerdtutorials.com/esp32-cam-send-photos-email/
//Reference: https://www.instructables.com/ESP32-CAM-Capture-Photos-and-Send-Through-E-mail-U/

#define emailSenderAccount    "@gmail.com"
#define emailSenderPassword   ""
#define smtpServer            "smtp.gmail.com"
#define smtpServerPort        465
#define emailSubject          "ESP32-CAM Photo Captured"
#define emailRecipient        "@gmail.com"

#define CAMERA_MODEL_AI_THINKER //Defining Camera Model

#if defined(CAMERA_MODEL_AI_THINKER)
  #define PWDN_GPIO_NUM     32 //Defining all the pins for the Camera
  #define RESET_GPIO_NUM    -1
  #define XCLK_GPIO_NUM      0
  #define SIOD_GPIO_NUM     26
  #define SIOC_GPIO_NUM     27
  
  #define Y9_GPIO_NUM       35
  #define Y8_GPIO_NUM       34
  #define Y7_GPIO_NUM       39
  #define Y6_GPIO_NUM       36
  #define Y5_GPIO_NUM       21
  #define Y4_GPIO_NUM       19
  #define Y3_GPIO_NUM       18
  #define Y2_GPIO_NUM        5
  #define VSYNC_GPIO_NUM    25
  #define HREF_GPIO_NUM     23
  #define PCLK_GPIO_NUM     22
#else
  #error "Camera model not selected" //If no camera Model defined, Error message
#endif

SMTPData smtpData; //Initializing Smtp (Used for mail sending)

#define FILE_PHOTO "/photo.jpg" //Name of the Photo file
int button = 12; //Pin where input signal is given
bool takeNewPhoto = true; // flag for deciding whether to take new photo or not

void setup() {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);//Setting Register to disable Brownout detection 
  
  Serial.begin(115200); //Initializing Serial Communication
  Serial.println();
  pinMode(button,INPUT_PULLUP);// Initializing Input Pin as Input Pullup
  // Connect to Wi-Fi
  WiFi.begin(ssid, password); //Connecting to WiFi
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  
  if (!SPIFFS.begin(true)) {// Initializing SPIFFS
    Serial.println("An Error has occurred while mounting SPIFFS");
    ESP.restart(); //If Error, restart ESP
  }
  else {
    delay(500);
    Serial.println("SPIFFS mounted successfully");
  }//Print uccess message
  
  Serial.print("IP Address: http://");
  Serial.println(WiFi.localIP());//Print the IP Address
  
  //Configure all the Pins for Camera 
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  
  if(psramFound()){
    config.frame_size = FRAMESIZE_UXGA;
    config.jpeg_quality = 10;
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }

//Try initializing the camera
esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);//Error message
    return;
  }
////////////////////////////////////////////////////////////////////////////////////////////////////
 
////////////////////////////////////////////////////////////////////////////////////////////////////
 
  capturePhotoSaveSpiffs();//Call function to take picture and store in SPIFFS
}

void loop() {
  int a = digitalRead(button);
  Serial.println(a);//Read and Print the button Status
  
  
    capturePhotoSaveSpiffs(); //Call function to Capture and save Image
      SEND_TO_MAIL(); //Call Function to send mail
      delay(8000); //delay
      SPIFFS.remove(FILE_PHOTO);//Delete the photo
      delay(2000);//delay
}

bool checkPhoto( fs::FS &fs ) { //Function to Check if Photo is available
  File f_pic = fs.open( FILE_PHOTO ); //Open the File
  unsigned int pic_sz = f_pic.size(); //Read the size of Picture
  return ( pic_sz > 100 ); //Return if size is greater than 100 Bytes
}

// Capture Photo and Save it to SPIFFS
void capturePhotoSaveSpiffs( void ) {
  camera_fb_t * fb = NULL; // pointer
  bool ok = 0; 
    takeNewPhoto = true;

  do { 
    Serial.println("Taking a photo...");

    fb = esp_camera_fb_get(); //TAke a Picture
    if (!fb) {
      Serial.println("Camera capture failed");
      return;
    }

     File file = SPIFFS.open(FILE_PHOTO, FILE_WRITE); //Open the Photo File

    if (!file) {
      Serial.println("Failed to open file in writing mode");
    }
    else { //Write the Photo data in the file
      file.write(fb->buf, fb->len); 
      Serial.print("The picture has been saved in ");
      Serial.print(FILE_PHOTO);
      Serial.print(" - Size: ");
      Serial.print(file.size());
      Serial.println(" bytes");
     Serial.printf("Saved file to path: %s\n", FILE_PHOTO);
    }
    file.close(); //close the file
    esp_camera_fb_return(fb);//Return the Camera pointer to close camera

    ok = checkPhoto(SPIFFS); //Check if Photo was okay
  } while ( !ok ); //Wait if the photo is not okay
  
}


void  SEND_TO_MAIL( void ) { //FUnction to send Mail
  // Preparing email
  Serial.println("Sending email...");
  // Set the SMTP Server Email host, port, account and password
  smtpData.setLogin(smtpServer, smtpServerPort, emailSenderAccount, emailSenderPassword);
  
  // Set the sender name and Email
  smtpData.setSender("ESP32-CAM", emailSenderAccount);
  
  smtpData.setPriority("High"); //Set Email Priority as High

  // Set the subject
  smtpData.setSubject(emailSubject);
    
  // Set the email message in HTML format
  smtpData.setMessage("<h2>Photo captured with ESP32-CAM and attached in this email.</h2>", true);

  smtpData.addRecipient(emailRecipient);
  //smtpData.addRecipient(emailRecipient2);

  // Add attach files from SPIFFS
  smtpData.addAttachFile(FILE_PHOTO, "image/jpg");
  smtpData.setFileStorageType(MailClientStorageType::SPIFFS);

  smtpData.setSendCallback(sendCallback);//Bind the Callback Function
  //Call Back function will print Status of Mail
  
  // Start sending Email, can be set callback function to track the status
  if (!MailClient.sendMail(smtpData))
    Serial.println("Error sending Email, " + MailClient.smtpErrorReason());

  smtpData.empty();//Clear all the SMTP Data
}

// Callback function to get the Email sending status
void sendCallback(SendStatus msg) { //Function to Print Status of the Mail
  //Print the current status
  Serial.println(msg.info());
}
