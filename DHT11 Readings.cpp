/*
Problem Statement:
Write an Arduino program to display temperature and humidity readings
using a DHT11 sensor on an OLED display using Arduino UNO.
*/

/*
Connections:

DHT11 Sensor:
VCC  -> 5V
GND  -> GND
DATA -> Pin 2

OLED Display (I2C):
VCC -> 5V
GND -> GND
SCL -> A5
SDA -> A4
*/

#include <DHT.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

/* DHT11 Setup */
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

/* OLED Setup */
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(9600);

  dht.begin();

  /* Initialize OLED */
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED not found");
    while(true); // Stop if display not found
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  /* Check if readings are valid */
  if (isnan(temperature) || isnan(humidity)) {
    display.clearDisplay();
    display.setCursor(0, 10);
    display.println("Sensor Error!");
    display.display();
    delay(2000);
    return;
  }

  /* Display data on OLED */
  display.clearDisplay();

  display.setCursor(0, 10);
  display.println("Temperature:");
  display.setCursor(0, 25);
  display.print(temperature);
  display.println(" C");

  display.setCursor(0, 45);
  display.println("Humidity:");
  display.setCursor(0, 60);
  display.print(humidity);
  display.println(" %");

  display.display();

  delay(2000);
}
