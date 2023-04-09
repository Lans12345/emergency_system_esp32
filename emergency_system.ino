#include <AG9.h>

AG9 gps;
int buzzer = 7;
int button1 = 8;
int button2 = 9;

void setup() {
  pinMode(buzzer, OUTPUT);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  
  Serial.begin(9600);
  gps.begin();
}

void loop() {
  if (digitalRead(button1) == HIGH) {
    makeCall("+639xxxxxxxxx"); //replace with your desired phone number
  }
  
  if (digitalRead(button2) == HIGH) {
    sendSMS("+639xxxxxxxxx", "Help me, I'm in danger!"); //replace with your desired phone number and message
  }
}

void makeCall(String phoneNumber) {
  digitalWrite(buzzer, HIGH);
  delay(500);
  digitalWrite(buzzer, LOW);
  delay(500);
  
  gps.call(phoneNumber);
  
  delay(10000); //wait for 10 seconds before allowing another call
}

void sendSMS(String phoneNumber, String message) {
  digitalWrite(buzzer, HIGH);
  delay(500);
  digitalWrite(buzzer, LOW);
  delay(500);
  
  gps.sendSMS(phoneNumber, message);
  
  delay(10000); //wait for 10 seconds before sending another SMS
}
