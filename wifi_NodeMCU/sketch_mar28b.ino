#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>

#define WIFI_ID        "Clack01"
#define WIFI_PASSWORD  "aibot2017"
#define FIREBASE_HOST "automatic-watering-32c2e.firebaseio.com"
#define FIREBASE_KEY "jHi7mtMoxRcTpwTGkbFk6WKTMyOv36EJzUp5pTjs"


void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_ID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_KEY);
  Firebase.setInt("analog", 0);
  
}

void loop() {
  int val = analogRead(A0);
  Serial.println(val);
  Firebase.setInt("analog",val);
  delay(500);
}
