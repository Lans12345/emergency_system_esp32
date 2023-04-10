#include <SoftwareSerial.h>

SoftwareSerial mySerial(8, 9); // RX, TX

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);


  pinMode(11, OUTPUT);

  pinMode(12, INPUT); // Button for making phone call
  pinMode(13, INPUT); // Button for sending SMS message
}

void loop() {
  // Make phone call when button 1 is pressed
  if (digitalRead(12) == HIGH) {
mySerial.println("ATD+639639530422;");// Replace with the phone number you want to call
    delay(30000);
    mySerial.println("ATH"); // Hang up the call
  }

  // Send SMS message when button 2 is pressed
  if (digitalRead(13) == HIGH) {
    digitalWrite(11, HIGH);
    mySerial.println("AT+CMGF=1"); // Set the SMS mode to text
    delay(1000);
mySerial.print("AT+CMGS=\"+639639530422\"");// Replace with the phone number you want to send SMS to
    delay(10000);
    mySerial.print("Help! I need assistance."); // Replace with the message you want to send
    mySerial.write(26); // End the SMS message with Ctrl+Z
    delay(10000); // Wait for the message to be sent

    if (mySerial.find("OK")) {
      Serial.println("Text message sent successfully.");
    } else {
Serial.println(mySerial.readString().c_str());
      Serial.println("Error sending text message.");
    }
  }

  // Check for incoming data from the A9G module
  while (mySerial.available()) {
    Serial.write(mySerial.read());
  }
}
