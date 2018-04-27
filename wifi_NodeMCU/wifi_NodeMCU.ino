#include <SoftwareSerial.h>
#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>
#include <time.h>

#define WIFI_ID        "Clack01"
#define WIFI_PASSWORD  "aibot2017"
#define FIREBASE_HOST  "automatic-watering-32c2e.firebaseio.com"
#define FIREBASE_KEY   "jHi7mtMoxRcTpwTGkbFk6WKTMyOv36EJzUp5pTjs"

int timezone = 7 * 3600;
int dst = 0;
int sprinkler = 0;
int spray = 0;

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
  Firebase.setFloat("Humidity/Humidity 1",0);
  Firebase.setFloat("Humidity/Humidity 2",0);
  Firebase.setFloat("Humidity/Percentage",0);
  Firebase.setString("Humidity/Time","");
  
  Firebase.setFloat("Temperature/Temperature",0);
  Firebase.setString("Temperature/Time","");
  
  delay(5000);
}

void loop() {
  while(Node.available() > 0){
    float soil_1 = Node.parseFloat();
    float soil_2 = Node.parseFloat();
    float temperature_air = Node.parseFloat();
    int sts = Node.parseInt();

    float percentage = (abs(abs(((((soil_1 + soil_2) / 2) / 1023) * 100) - 100)));
    
    if(Node.read() == '\n'){

      if(sts == 11){
        sprinkler = 1;
      }
      else if(sts == 10){
        sprinkler = 0;
      }
      
      if(sts == 21){
        spray = 1;
      }
      else if(sts == 20){
        spray = 0;
      }
      
      time_t now = time(nullptr);
      String time1 = ctime(&now);

      StaticJsonBuffer<200> jsonBuffer;
        JsonObject& root = jsonBuffer.createObject();
        root["Sensor 1"] = soil_1;
        root["Sensor 2"] = soil_2;
        root["Percentage"] = percentage;
        root["Temperature air"] = temperature_air;
        root["Sprinkler Sts"] = sprinkler;
        root["Spray Sts"] = spray;
        root["Time"] = time1;
          
        // append a new value to /logDHT
        String name = Firebase.push("logDHT", root);

      Firebase.setInt("Status/Sprinkler", sprinkler);
      Firebase.setInt("Status/Spray", spray);
      
      Firebase.setFloat("Humidity/Humidity 1",soil_1);
      Firebase.setFloat("Humidity/Humidity 2",soil_2);
      Firebase.setFloat("Humidity/Percentage",percentage);
      Firebase.setString("Humidity/Time", time1);
      
      Firebase.setFloat("Temperature/Temperature",temperature_air);
      Firebase.setString("Temperature/Time",time1);
      
      Serial.print("Humidity 1: ");
      Serial.println(soil_1);
      Serial.print("Humidity 2: ");
      Serial.println(soil_2);
      Serial.print("Percentage: ");
      Serial.println(percentage);
      Serial.print("Temperature: ");
      Serial.println(temperature_air);
      Serial.print("Sprinkler Sts: ");
      Serial.println(sprinkler);
      Serial.print("Spray Sts: ");
      Serial.println(spray);
      Serial.println(time1);
    }
  }
  delay(500);
}
