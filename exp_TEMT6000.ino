
#define CAYENNE_DEBUG
#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP8266.h>
#define LIGHTSENSORPIN A0
#define VIRTUAL_CHANNEL 0
#define VIRTUAL_CHANNEL 1
#define VIRTUAL_CHANNEL 2

// WiFi network info.
char ssid[] = "aizatwifi2.5@unifi";
char wifiPassword[] = "11Septem!";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "c52de9d0-2444-11ed-baf6-35fab7fd0ac8";
char password[] = "5e201434411aa623960a1978f92eb3c1a932ad4b";
char clientID[] = "cb0892f0-244a-11ed-baf6-35fab7fd0ac8";

float reading; float temperature;
unsigned long previousMillis = 0;
const long interval = 1000;

void setup() {
  Serial.begin(9600);
  pinMode(LIGHTSENSORPIN, INPUT);
  pinMode(2, OUTPUT);
  digitalWrite(2,HIGH);
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);
}

void loop() {
  Cayenne.loop();
}

// Default function for sending sensor data at intervals to Cayenne.
// You can also use functions for specific channels, e.g CAYENNE_OUT(1) for sending channel 1 data.
CAYENNE_OUT(VIRTUAL_CHANNEL)
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    float reading = analogRead(LIGHTSENSORPIN);
    float square_ratio = reading / 1023.0;
    square_ratio = pow(square_ratio, 2.0);
    temperature = random(20,40);
    Serial.println(reading);
    Cayenne.virtualWrite(1, reading, TYPE_LUMINOSITY, UNIT_LUX);
    Cayenne.virtualWrite(2, temperature, TYPE_TEMPERATURE, UNIT_CELSIUS);
    //Cayenne.virtualWrite(0, millis());
    //Cayenne.luxWrite(2, 700);
    //Cayenne.virtualWrite(3, 50, TYPE_PROXIMITY, UNIT_CENTIMETER);
  }
}

CAYENNE_IN(0)
{
  digitalWrite(2, !getValue.asInt());
}
