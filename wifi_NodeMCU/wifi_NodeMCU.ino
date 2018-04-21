#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>

#define WIFI_ID        "Lerdsurut"
#define WIFI_PASSWORD  "5316038285"
#define FIREBASE_HOST  "automatic-watering-32c2e.firebaseio.com"
#define FIREBASE_KEY   "jHi7mtMoxRcTpwTGkbFk6WKTMyOv36EJzUp5pTjs"

SoftwareSerial Node(D1,D2); //(RX,TX)

void setup() {
  Serial.begin(9600);
  Node.begin(4800);

  pinMode(D1, INPUT);
  pinMode(D2, OUTPUT);
  
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
  Firebase.setInt("humid 1",0);
  Firebase.setInt("humid 2",0);
  Firebase.setInt("temperature",0);
  
}

void loop() {
  while(Node.available() > 0){
    int humid_1 = Node.parseInt();
    int humid_2 = Node.parseInt();
    float temperature_air = Node.parseFloat();
    float percentage = Node.parseFloat();
    
    if(Node.read() == '\n'){
      Firebase.setInt("humid 1",humid_1);
      Firebase.setInt("humid 2",humid_2);
      Firebase.setFloat("Percentage",percentage);
      Firebase.setFloat("temperature",temperature_air);

      Serial.print("Humid 1: ");Serial.println(humid_1);
      Serial.print("Humid 2: ");Serial.println(humid_2);
      Serial.print("Percentage: ");Serial.println(percentage);
      Serial.print("Temperature: ");Serial.println(temperature_air);
    }
  }
  delay(100);
}
