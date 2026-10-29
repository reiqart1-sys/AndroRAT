#include <Servo.h>

Servo ServoMotor;
String inputString = "";
int RedpinLock = 12;
int GreenpinUnlock = 13;

void setup() {
  Serial.begin(9600);           // Start serial communication
  ServoMotor.attach(11);
  pinMode(RedpinLock, OUTPUT);
  pinMode(GreenpinUnlock, OUTPUT);
  
  LockedPosition(true);         // Start locked
  Serial.println("--- Laptop Control Ready ---");
  Serial.println("Type '1111' and press Enter to unlock.");
  Serial.println("Type '' and press Enter to lock.");
}

void loop() {
  // Read incoming characters from your laptop keyboard
  while (Serial.available() > 0) {
    char inChar = (char)Serial.read();
    
    // When you press Enter (newline/carriage return)
    if (inChar == '\n' || inChar == '\r') {
      inputString.trim(); // Clean up any extra spaces
      
      if (inputString == "5555") {
        Serial.println("Access Granted: Opening Door...");
        LockedPosition(false);
      } 
      else if (inputString == "b" || inputString == "B") {
        Serial.println("Locking Door...");
        LockedPosition(true);
      } 
      else if (inputString.length() > 0) {
        Serial.println("Incorrect code!");
      }
      
      inputString = ""; // Reset for next command
    } else {
      inputString += inChar; // Build the typed string
    }
  }
}

void LockedPosition(bool locked) {
  if (locked) {
    digitalWrite(RedpinLock, HIGH);
    digitalWrite(GreenpinUnlock, LOW);
    ServoMotor.write(0);   // Locked position (0 degrees)
  } else {
    digitalWrite(RedpinLock, LOW);
    digitalWrite(GreenpinUnlock, HIGH);
    ServoMotor.write(90);  // Unlocked position (90 degrees)
  }
}