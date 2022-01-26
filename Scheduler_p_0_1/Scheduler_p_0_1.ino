#include "scheduler.h"
#include "notification.h"

Scheduler *sched;
unsigned long sendDataPrevMillis = 0;
int count = 0;
#define WIFI_SSID "RoodRouter"
#define WIFI_PASSWORD ""

void setup() {
  // put your setup code here, to run once:
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
  Notification *n = new Notification();
  AtoAwc *a = NULL;
  Doser *d = NULL;
  sched  = new Scheduler(d,n,a);
}

void loop() {
  // put your main code here, to run repeatedly:
  Alarm.delay(1000); // wait one second between clock display
  //Serial.print(".");

}
