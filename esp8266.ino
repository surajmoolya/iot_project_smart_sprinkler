#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <time.h>
#include "secrets.h"
#include "DHT.h"
#include "fuzzylogic.h"
 
#define DHTPIN 4        // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11
#define soil_sensor_pin A0
#define sprinkler_pin D6 
# define led_pin D7
DHT dht(DHTPIN, DHTTYPE);
 
int h ;
int t;
int soil_moisture;
unsigned long lastMillis = 0;
unsigned long previousMillis = 0;
const long interval = 5000;
unsigned long time_counter = -1;
unsigned long sprinkler_time = -1;
int auto_set = 1;
int on_state = 0;
unsigned short change = 0;
//PubSubClient::setKeepAlive(15*60);
#define AWS_IOT_PUBLISH_TOPIC   "esp8266/data"
#define AWS_IOT_SUBSCRIBE_TOPIC "esp8266/control"
#define AWS_REFRESH_TOPIC "gui/refresh"
 
WiFiClientSecure net;
 
BearSSL::X509List cert(cacert);
BearSSL::X509List client_crt(client_cert);
BearSSL::PrivateKey key(privkey);
 
PubSubClient client(net);
 
time_t now;
time_t nowish = 1510592825;
 
 
void NTPConnect(void)
{
  Serial.print("Setting time using SNTP");
  configTime(TIME_ZONE * 3600, 0 * 3600, "0.in.pool.ntp.org", "1.in.pool.ntp.org");
  now = time(nullptr);
  while (now < nowish)
  {
    delay(500);
    Serial.print(".");
    now = time(nullptr);
  }
  Serial.println("done!");
  struct tm timeinfo;
  gmtime_r(&now, &timeinfo);
  Serial.print("Current time: ");
  Serial.print(asctime(&timeinfo));
}
 
 
void messageReceived(char *topic, byte *payload, unsigned int length)
{
  Serial.println("command recievd");
  StaticJsonDocument<256> doc;
  deserializeJson(doc, payload, length);
//  Serial.print("Received [");
//  Serial.print(topic);
//  char message[200];
//  strlcpy(message, doc["message"] | "default", sizeof(message));
//  Serial.println(message);
    if (doc["action"] == 1){
//     h = doc["humidity"];
//     t = doc["temperature"];
//     soil_moisture = doc["soil_moisture"];
     auto_set = doc["auto"];
     on_state = doc["on_state"];
     change = 1;
    }
    refresh();
    
}
 
 
void connectAWS()
{
  delay(3000);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
 
  Serial.println(String("Attempting to connect to SSID: ") + String(WIFI_SSID));
 
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(1000);
  }
 
  NTPConnect();
 
  net.setTrustAnchors(&cert);
  net.setClientRSACert(&client_crt, &key);
 
  client.setServer(MQTT_HOST, 8883);
  client.setCallback(messageReceived);
//  client.KeepAlive()
 
 
  Serial.println("Connecting to AWS IOT");
 
  while (!client.connect(THINGNAME))
  {
    Serial.print(".");
    delay(1000);
  }
 
  if (!client.connected()) {
    Serial.println("AWS IoT Timeout!");
    return;
  }
  // Subscribe to a topic
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);
 
  Serial.println("AWS IoT Connected!");
}
 
 
void publishData()
{
  StaticJsonDocument<200> doc;
  doc["time"] = millis();
  doc["humidity"] = h;
  doc["temperature"] = t;
  doc["soil_moisture"] = soil_moisture;
  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer); // print to client
  Serial.println();
 
  client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
}
void refresh(){
//  Serial.println("sending state");
  h = dht.readHumidity();
  t = dht.readTemperature();
  soil_moisture =  100.00 - ( (analogRead(soil_sensor_pin)/1023.00) * 100.00 ) ;
  StaticJsonDocument<200> doc;
//  doc["time"] = millis();
  doc["humidity"] = h;
  doc["temperature"] = t;
  doc["soil_moisture"] = soil_moisture;
  doc["auto"] = auto_set;
  if (digitalRead(led_pin) == HIGH) doc["state"] = 1;
  else doc["state"] = 0;
  doc["on_state"] = on_state;
  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer); // print to client
  client.publish(AWS_REFRESH_TOPIC, jsonBuffer);
  
}
 
void setup()
{
  Serial.begin(115200);
  pinMode(DHTPIN,INPUT);
  pinMode(soil_sensor_pin,INPUT);
  pinMode(sprinkler_pin,OUTPUT);
  pinMode(led_pin,OUTPUT);
  digitalWrite(sprinkler_pin,HIGH);
  connectAWS();
  dht.begin();
  fuzzySetup();
  readata();
  
}
 
 
//void loop()
//{
////  client.loop();
//  h = dht.readHumidity();
//  t = dht.readTemperature();
//  soil_moisture =  100.00 - ( (analogRead(soil_sensor_pin)/1023.00) * 100.00 ) ;
//  
// 
//  if (isnan(h) || isnan(t) )  // Check if any reads failed and exit early (to try again).
//  {
//    Serial.println(F("Failed to read from DHT sensor!"));
//    return;
//  }
// Serial.print(F("Soil Moisture: "));
//  Serial.print(soil_moisture);
//  Serial.print(F("% Humidity: "));
//  Serial.print(h);
//  Serial.print(F("%  Temperature: "));
//  Serial.print(t);
//  Serial.println(F("°C "));
//  delay(2000);
// 
//  now = time(nullptr);
// 
//  if (!client.connected())
//  {
//    connectAWS();
//  }
//  else
//  {
//    client.loop();
//    if (millis() - lastMillis > 5000)
//    {
//      lastMillis = millis();
//      publishData();
//    }
//  }
//}
void readata(){
  h = dht.readHumidity();
     t = dht.readTemperature();
     soil_moisture =  100.00 - ( (analogRead(soil_sensor_pin)/1023.00) * 100.00 ) ;
  
 
      if (isnan(h) || isnan(t) )  // Check if any reads failed and exit early (to try again).
      {
        Serial.println(F("Failed to read from DHT sensor!"));
        return ;
      }
      Serial.print(F("Soil Moisture: "));
      Serial.print(soil_moisture);
      Serial.print(F("% Humidity: "));
      Serial.print(h);
      Serial.print(F("%  Temperature: "));
      Serial.print(t);
      Serial.println(F("°C "));
      publishData();
      sprinkler_time = fuzzyDecission(soil_moisture,t)*60*1000;
      refresh();
}
void loop(){
  
  if (!client.connected())connectAWS();
  else client.loop();
  if(millis() - time_counter >= 900000){ //900000
    time_counter = millis();
    readata();
  }
  if (auto_set == 1){
    if (millis() - time_counter <= sprinkler_time) {
      digitalWrite(led_pin,HIGH);
      digitalWrite(sprinkler_pin,LOW);
      }
    else{
      digitalWrite(led_pin,LOW);
      digitalWrite(sprinkler_pin,HIGH);
      } 
    
  }
  else{
    if (on_state == 1){
      digitalWrite(led_pin,HIGH);
      digitalWrite(sprinkler_pin,LOW);
      } 
    else {
      digitalWrite(led_pin,LOW);
      digitalWrite(sprinkler_pin,HIGH);
      }
  }
  Serial.print(digitalRead(sprinkler_pin));
  Serial.print("Auto : ");
  Serial.print(auto_set);
  Serial.print(" On_state : ");
  Serial.println(on_state);
  if (change == 1){
    refresh();
    change = 0;
  }
  delay(1000);
  
}
