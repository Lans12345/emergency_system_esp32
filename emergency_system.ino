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
    makeCall("+639639530422"); //replace with your desired phone number
  }
  
  if (digitalRead(button2) == HIGH) {
    sendSMS("+639639530422", getLocationMessage()); //replace with your desired phone number
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
  
  gps.enableGPS();
  delay(2000); //wait for GPS to stabilize
  
  float latitude = gps.getLatitude();
  float longitude = gps.getLongitude();
  
  gps.disableGPS();
  
  String location = String(latitude, 6) + "," + String(longitude, 6);
  message = message + " My location is: " + location;
  
  gps.sendSMS(phoneNumber, message);
  
  delay(10000); //wait for 10 seconds before sending another SMS
}

String getLocationMessage() {
  //customize your message here
  return "Help me, I'm in danger!";
}
