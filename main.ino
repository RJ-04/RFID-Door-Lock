// Importing essential libraries for the project
#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>


// Defining the pins for the RFID module, Servo motor, Buzzer, and LEDs
#define SS_PIN 10
#define RST_PIN 9
#define Green 8
#define Red 4
#define Buzzer 6

// Creating an instance of the MFRC522 library
MFRC522 mfrc522(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2); // Setting the LCD address to 0x27

// Creating an instance of the Servo library
Servo servo;
int servoPin = 3;

// Defining the verified card
String verified_Card = "04b29e00f54c03"; // Change this to your card UID, check the serial monitor for the UID


// Setup function
void setup() {
    servo.attach(servoPin); // Attaching the servo motor to the servo pin
    Serial.begin(9600);     // Initializing the serial monitor

    // Setting the pins as output
    pinMode(Green, OUTPUT);
    pinMode(Red, OUTPUT);
    pinMode(Buzzer, OUTPUT);

    // Initializing the RFID module, LCD, and Servo motor
    SPI.begin();
    mfrc522.PCD_Init();
    lcd.init();
    lcd.backlight();
    delay(4);
}


// Loop function
void loop() {

    // Displaying the message on the LCD
    lcd.setCursor(0, 0);
    lcd.print("Put your card ->");
    lcd.setCursor(0, 1);
    lcd.print("for scanning  ->");

    // Checking if the card is present
    if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial())
    return;

    // Reading the card UID and storing it in the content variable
    String content = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
        content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""));   // Adding a 0 before the UID if it is less than 0x10
        content.concat(String(mfrc522.uid.uidByte[i], HEX));               // Converting the UID to HEX
    }

    // Displaying the card UID on the serial monitor
    Serial.println("Content: ");
    Serial.println(content);
    delay(1000);

    // Calling the cardVerification function defined below to verify the card
    cardVerification(content); 

    // Turning off the LEDs
    digitalWrite(Red, LOW);
    digitalWrite(Green, LOW);
}

// Function to verify the card and if verified, do the necessary actions
void cardVerification(String content) {

  if (verified_Card == content) { // Checking if the card is verified
    lcd.clear();
    servo.write(90); // Opening the door
    Serial.println("Card Authorized!");
    digitalWrite(Green, HIGH);
    digitalWrite(Red, LOW);
    onAuthorized(); // Calling the onAuthorized function defined below
    servo.write(0); // Closing the door
    
  } else {
    lcd.clear();
    Serial.println("Card Unauthorized!");
    digitalWrite(Red, HIGH);
    digitalWrite(Green, LOW);
    onUnauthorized(); // Calling the onUnauthorized function defined below
  }
}

// Function to play a pleasant sound, display a message on the LCD and count down of opening duration(5s)
void onAuthorized() {

    // Playing a pleasant sound
    int melody[] = { 32, 32, 32, 32 };
    int noteDurations[] = { 10, 10, 100, 200 };

    for (int i = 0; i < 4; i++) {
        tone(Buzzer, melody[i], noteDurations[i]);
        delay(noteDurations[i] * 1.3);
    }

    // Displaying the message on the LCD
    lcd.setCursor(1, 0);
    lcd.print("Card verified!");
    lcd.setCursor(4, 1);
    lcd.print("WELCOME!");
    delay(3000);
    lcd.clear();

    // Display before closing the door in LCD
    lcd.setCursor(1, 0);
    lcd.print("Door closes in");
    delay(1000);
    lcd.clear();

    // Counting down 5s before closing the door
    for (int i = 5; i > 0; i--) {
        lcd.setCursor(7, 0);
        lcd.print(i);
        delay(1000);
    }

    // Displaying "Door closed!" on the LCD after Closing the door
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Door closed!");
    delay(1000);
    lcd.clear();
}

// Function to play a dissonant sound, display a message on the LCD
void onUnauthorized() {

    // Playing a dissonant sound
    int dissonant[] = { 500, 500, 500, 500 };
    int noteDurations[] = { 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50 };

    for (int i = 0; i < 4; i++) {
        tone(Buzzer, dissonant[i], noteDurations[i]);
        delay(noteDurations[i] * 1.3);
    }

    // Displaying the message on the LCD
    lcd.setCursor(2, 0);
    lcd.print("WRONG card!");
    lcd.setCursor(2, 1);
    lcd.print("Door LOCKED.");
    delay(3000);
    lcd.clear();
}