#include "fbDb.h"
/* 1. Define the WiFi credentials */
#define WIFI_SSID "RoodRouter"
#define WIFI_PASSWORD ""

Database *db;
unsigned long sendDataPrevMillis = 0;
int count = 0;


void setup()
{
  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  db  = new Database();
  db->initDb();
}

void loop()
{

  if (db->databaseReady() && (millis() - sendDataPrevMillis > 900000 || sendDataPrevMillis == 0))
  {
    sendDataPrevMillis = millis();
    count++;
    String path = "/test/stream/data/json";
    FirebaseJson json;
    json.add("data", "hello");
    json.add("num", count);
    db->putData(path,json);   
    FirebaseJson *jsn = db->getJson(path);
    Serial.println(jsn->raw());
    db->putFloat("skippy/float",99.9);
    Serial.println(db->getFloat("skippy/float"));
    db->putString("skippy/string","A String");
    Serial.println(db->getStr("skippy/string"));
    db->putBool("skippy/bool",false);
    Serial.println(db->getBool("skippy/bool"));
    db->putInt("skippy/int",count);
    Serial.println(db->getInt("skippy/int"));
    count++;
  }
}
