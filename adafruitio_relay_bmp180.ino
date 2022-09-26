//sensor
#include <Adafruit_BMP085.h>

#include "AdafruitIO_WiFi.h"
#define IO_USERNAME "ismailsa"
#define IO_KEY "aio_dBPi179YKyS7kVIemoktSjFGhXOy"
#define WIFI_SSID "aizatwifi2.5@unifi"
#define WIFI_PASS "11Septem!"

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

Adafruit_BMP085 bmp;

int Temperature = 30;
int last = -1;
int led=0;

// set up the 'analog' feed my feeds name gas
AdafruitIO_Feed *Temp = io.feed("room.temperature");
AdafruitIO_Feed *Switch = io.feed("room.switch");

void setup() {
  Serial.begin(115200);
  if (!bmp.begin()) {
  Serial.println("Could not find a valid BMP085 sensor, check wiring!");
  while (1) {}
  }
  while(! Serial);
  Serial.print("Connecting to Adafruit IO");
  io.connect();
  pinMode(D8,INPUT);
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println(io.statusText());
}

void loop() 
{
  io.run();
  //Read Sensor
  Temperature = bmp.readTemperature();
  
  led = digitalRead(D8);
  if(Temperature == last)
  return;

  Serial.print("sending -> ");
  Serial.println(Temperature);
  Serial.print("LED STATE -> ");
  Serial.println(led);
  
  Temp->save(Temperature);
  Switch->save(led);//send data
  last = Temperature;
  delay(15000);
}
