#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <SoftwareSerial.h>

#define FIREBASE_HOST "tubes-iotxmicro.firebaseio.com"
#define FIREBASE_AUTH "oO3HeiVUxdKZsu6JAVD0tXgxi79EL2XHKg8pRkhZ"
#define WIFI_SSID "TELEKOMUNIKASI"
#define WIFI_PASSWORD "d3tt4203"

float measurement;
SoftwareSerial mySerial(D5, D6);

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  mySerial.write("mySerial");
  measurement=mySerial.read();
  float g = (measurement / 100);
  Firebase.setFloat ("/Monitoring/gempa",g );
  if (mySerial.available()>=0 ) {
    if (g >= 0){
      Serial.print("Kekuatan Gempa = ");
      Serial.print(g);
      Serial.println(" SR");
      delay(1000);
      }
    else {
      Serial.print("Kekuatan Gempa = ");
      Serial.print("0.00");
      Serial.println(" SR");
      delay(1000);
      }
  }
}
