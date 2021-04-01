#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "basic-6a12f-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "NgYPIcvdfOw7tMdcueTt9UtZJUXpbCoeYlvibi9k"
#define WIFI_SSID "Digiace"
#define WIFI_PASSWORD "127616616ta"

String fireStatus = "";
int led = D8;

void setup()
{
  Serial.begin(9600);
  delay(1000);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(led, OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {


  fireStatus = Firebase.getString("LED_STATUS");
  if (fireStatus == "ON")
  { 
    // compare the input of led status received from firebase
    Serial.println("LED ON");
    digitalWrite(led, HIGH);                                                          // make external led ON
  }
  else if (fireStatus == "OFF")
  { 
    // compare the input of led status received from firebase
    Serial.println("LED OFF");
    digitalWrite(led, LOW);                                                        // make external led OFF
  }
  else {
    Serial.println("Wrong Credential! Please send ON/OFF");
  }

}
