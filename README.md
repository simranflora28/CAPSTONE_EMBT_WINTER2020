# CAPSTONE_EMBT_WINTER2020
This is repository to store every single detail of capstone project, as this plays an essential role towards the course completion for Winter 2021. This is a 4 month project starting from January 18, 2021 till April 30, 2021.

The contributors to this repository: Simran,Amandeep Singh, Gurpreet Singh, Kiranpreet Kaur Gill, Jasmeet Singh

This Capstone Project is being guided under the supervision of Dr.Mike Aleshams

Hardware Skills: Exploring BB; Exploring LPC1769; Exploring Arduino Uno; Interfacing using UART, SPI, I2C;

Operating System: LINUX, Windows

Software Skills: MULTISIM,PSPICE,HTML,VHDL,ECLIPSE,MCUxpresso,QT CREATOR

Programming Language: C, C++

We are very excited to work on the Capstone Project

In this ESE 4009_2 Capstone project, we are using best of our knowledge to make the project, IOT BASED BANK LOCKER SECURITY. Here, the bank locker is being secured using 3 layers of security: touchscreen as the first layer, and the finger print sensor is used as the 2nd layer security for authentication purposes. Camera is being used in the project as the 3rd layer security, as if any wrong thing occured then then camera will take picture and send it to cloud which is GMAIL for this project as, in gmail we can store unlimited data. Vibrator sensor, is used to determine the if any person tries to open the looker using some force. Buzzer is used as an alert. RTC determines the real time for the internet. GSM module is used to send the msg.

This IOT based project is used to improvise the Bank locker security system as it uses various peripherals and sensors for this purpose. The IOT based Bank locker security system uses an automated Safety vault with triple layer defense mechanism therefore, the components are finalised accordingly.

# HARDWARE COMPONENTS AND ITS SPECIFICATIONS:

Beaglebone black: It is the 5V main microcontroller unit and all the components are connected to it directly or indirectly.
Arduino Mega: It is a 5V slave device for connecting GSM Module and fingerprint sensor.
GSM Module: The GSM 900  is used to send SMS (Short Service Message) to the user whenever the locker is opened.
ESP32 CAM Module: This is used for internet connectivity and taking picture and sending mail.
ESP8266 Module: This module is used for touchscreen interface.
RTC Module: Used for keeping track or real time.
Vibration sensor: It is used to detect vibration when any unauthorized person will try to open the bank locker forcefully, this sensor will start vibrating.
Fingerprint sensor: For biometric finger authentication this sensor is used.
Servo motor: It is used to lock open and close mechanism.
Touchscreen: It is required to enter the passcode. 
Buzzer: It beeps when unauthorised person tries to open the locker.
Soldering kit: This kit consists of soldering iron which is used for soldering components to PCB. And there is a digital multimeter that comes with this kit that can be used for testing of components, power supply etc.
Wires and Breadboard: Wires are used for connecting components in breadboard.
Zero PCB: Used to place the Components on the board.
SD card: To Flash Beaglebone with latest Debian image SD card can be used.
Resistor/Capacitor Kit: It consists of different types of resistors and capacitors used in the project.
Power Supply: 9V is required to Power Up GSM Module and 5V to power up Beagle bone without Laptop.

Testing Hardware Component:Testing of hardware components is done mainly by the arduino board using arduino IDE. we test servo motor, vibrator sensor, Beaglebone Black, Arduino Mega and GSM. 
For BBB: we login in to debian and test few command to show its working properly.
For Arduino Mega: we test the example code using arduino ide to show its working.
For GSM testing: we test GSm testing with arduino uno, for GSM testing we are making a call through the sim we inserted in the GSM module.
For Servo motor: we test the servo motor using arduino uno.
For Vibrator Sensor: we test the Vibfrator sensor using arduino uno.
