#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#define BLYNK_TEMPLATE_ID "#" //change
#define BLYNK_DEVICE_NAME "#" //change
#define BLYNK_AUTH_TOKEN "#" //change

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "#"; //change
char pass[] = "#"; //change
int ss;
const int LED = 0;
const long utcOffsetInSeconds = 3600;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);
int ukluci;
int iskluci;

BLYNK_WRITE(V4)
{
  ss = param.asInt(); 
  ukluci = ss;
}

BLYNK_WRITE(V0)
{
  ss = param.asInt(); 
  iskluci = ss;
}

void setup()
{
  Serial.begin(9600);
  WiFi.begin(ssid, pass);
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  timeClient.begin();

  ukluci = 7;
  iskluci = 11;

  pinMode(LED, OUTPUT);

  digitalWrite (LED, LOW);

  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);

  delay(2000); 
}

void loop()
{
  Blynk.run();
  timeClient.update();
  if (timeClient.getHours() == ukluci) {
    digitalWrite (LED, HIGH);  // vkluci ja grealkata
  } else if (timeClient.getHours() == iskluci) {
    digitalWrite (LED, LOW); // iskluci ja grealkata
  }
  delay(1000);
}
