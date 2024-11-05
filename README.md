# RFID-based Door Access Control System

## Contributors

Thanks to the following people who have contributed to this project:

- [Aritra-Dey-117-XT](https://github.com/Aritra-Dey-117-XT)
- [audrijaishere](https://github.com/audrijaishere)
- [Saumyadip Kundu](https://github.com/Saumyadipkundu2101)
- [Riyansh Jain](https://github.com/RJ-04)

This Arduino-based project is designed to control access to a secured area using an RFID card system. The system includes an RFID reader, an LCD display, a servo motor for door control, and LED and buzzer indicators for access status.

Demo video:- [https://youtu.be/72wSdquTCw4](https://youtu.be/72wSdquTCw4)
Detailed PPT:- [https://www.canva.com/design/DAGVoATse2Y/TK8JkehLS_NxLI1v7QDbhQ/edit?utm_content=DAGVoATse2Y&utm_campaign=designshare&utm_medium=link2&utm_source=sharebutton](https://www.canva.com/design/DAGVoATse2Y/TK8JkehLS_NxLI1v7QDbhQ/edit?utm_content=DAGVoATse2Y&utm_campaign=designshare&utm_medium=link2&utm_source=sharebutton)

## Components Used
- **Arduino Uno**
- **RFID Reader (MFRC522)**
- **Servo Motor**
- **LCD Display (16x2 with I2C)**
- **Green and Red LEDs**
- **Buzzer**
  
## Setup and Pin Configuration
- **RFID Reader (MFRC522)**: `SS_PIN = 10`, `RST_PIN = 9`
- **Green LED**: `Pin 8`
- **Red LED**: `Pin 4`
- **Buzzer**: `Pin 6`
- **Servo Motor**: `Pin 3 (any PWM Pin)` 
- **LCD**: Address set to `0x27` on I2C, 16x2 configuration

## Code Description

### Libraries Included
- **SPI.h**: Enables SPI communication for RFID.
- **MFRC522.h**: Communicates with the RFID reader.
- **Wire.h**: Manages I2C communication for the LCD.
- **Servo.h**: Controls the servo motor for door operations.
- **LiquidCrystal_I2C.h**: Manages the I2C LCD display.

### Key Variables
- **`verified_Card`**: Contains the UID of the verified RFID card that grants access.
- **`servoPin`**: Configure the servo motor control pin and position.

### Functions

#### `setup()`
Initializes all components: RFID, LCD, and Servo. Sets the necessary pins for LEDs and Buzzer as outputs and prepares the serial monitor for UID debugging.

#### `loop()`
1. Displays a message on the LCD prompting the user to scan their RFID card.
2. Checks for a new RFID card and reads its UID if present.
3. Displays the UID on the serial monitor and calls the `cardVerification()` function.

#### `cardVerification(String content)`
- Compares the scanned card's UID with `verified_Card`.
- If authorized:
  - Displays "Card Authorized!" on the serial monitor.
  - Activates the Green LED and initiates the `onAuthorized()` function.
- If unauthorized:
  - Displays "Card Unauthorized!" on the serial monitor.
  - Activates the Red LED and initiates the `onUnauthorized()` function.

#### `onAuthorized()`
1. Plays a welcoming sound on the buzzer.
2. Displays a welcome message on the LCD.
3. Opens the door for 5 seconds, with a countdown shown on the LCD.
4. Closes the door and displays a "Door closed!" message on the LCD.

#### `onUnauthorized()`
1. Plays a dissonant warning sound on the buzzer.
2. Displays a "WRONG card!" and "Door LOCKED" message on the LCD.

### Usage
1. Power the Arduino and ensure all connections are secure.
2. Modify the `verified_Card` variable to match the UID of your authorized RFID card (check the serial monitor for UIDs).
3. Upload the code to the Arduino board.
4. Once the setup is complete, place your RFID card near the RFID reader to test the access control system.

### Notes
- Ensure the LCD I2C address matches your device's configuration.
- Customize the sound frequencies in the `onAuthorized()` and `onUnauthorized()` functions if desired.

This project provides a basic access control setup that can be expanded with additional security features or sensors as needed.
