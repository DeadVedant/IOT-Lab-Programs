/*Experiment No. 3
Title: Program an Arduino to Read Data from a Temperature Sensor and Display the Output on the Serial Monitor
Objective

The objective of this experiment is to interface a temperature sensor with an Arduino microcontroller, read temperature data, and display the output on the Serial Monitor.

Materials Required
- Arduino Board (Arduino Uno)
- Temperature Sensor (LM35 or DHT11)
- Jumper Wires
- Arduino IDE*/

#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {

    Serial.begin(9600);

    dht.begin();

    Serial.println("DHT11 Sensor Initialized");
}

void loop() {

    float temp = dht.readTemperature();

    if (isnan(temp)) {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }

    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.println(" °C");

    delay(2000);
}

/*Circuit Connections
DHT11 Pin	  Arduino Connection
VCC	        5V
GND	        GND
DATA	      Digital Pin 2*/
