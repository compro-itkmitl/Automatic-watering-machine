#include <SoftwareSerial.h>
#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>
#include <time.h>

#define WIFI_ID        "Lerdsurut"
#define WIFI_PASSWORD  "5316038285"
#define FIREBASE_HOST  "automatic-watering-32c2e.firebaseio.com"
#define FIREBASE_KEY   "jHi7mtMoxRcTpwTGkbFk6WKTMyOv36EJzUp5pTjs"

int timezone = 7 * 3600;
int dst = 0;

SoftwareSerial Node(D1,D2); //(RX,TX)

void setup() {
  Serial.setDebugOutput(true);
  Serial.begin(115200);
  Node.begin(4800);
  
  WiFi.begin(WIFI_ID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  configTime(timezone, dst, "pool.ntp.org", "time.nist.gov");
  Serial.println("\nLoading time");
  while (!time(nullptr)) {
    Serial.print("*");
    delay(1000);
  }
  Serial.println("");

  Firebase.begin(FIREBASE_HOST, FIREBASE_KEY);
  Firebase.setFloat("Humid 1",0);
  Firebase.setFloat("Humid 2",0);
  Firebase.setFloat("Percentage",0);
  Firebase.setFloat("Temperature",0);
  Firebase.setFloat("hour",0);
}

void loop() {
  while(Node.available() > 0){
    float humid_1 = Node.parseFloat();
    float humid_2 = Node.parseFloat();
    float percentage = Node.parseFloat();
    float temperature_air = Node.parseFloat();
    
    
    if(Node.read() == '\n'){
      time_t now = time(nullptr);
      struct tm* p_tm = localtime(&now);
      Firebase.setFloat("Sensor/Humid 1",humid_1);
      Firebase.setFloat("Sensor/Humid 2",humid_2);
      Firebase.setFloat("Sensor/Percentage",percentage);
      Firebase.setFloat("Sensor/Temperature",temperature_air);
      Firebase.setFloat("Sensor/hour", p_tm->tm_hour);
      Firebase.setFloat("Sensor/min",p_tm->tm_min);
      Firebase.setFloat("Sensor/sec", p_tm->tm_sec);

      Serial.print("Humid 1: ");
      Serial.println(humid_1);
      Serial.print("Humid 2: ");
      Serial.println(humid_2);
      Serial.print("Percentage: ");
      Serial.println(percentage);
      Serial.print("Temperature: ");
      Serial.println(temperature_air);
    }
  }
  delay(100);
}
