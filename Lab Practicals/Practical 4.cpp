/*Experiment No. 4
Title: Write an Arduino / Raspberry Pi Program for Interfacing PIR Sensor

Objective
To interface a PIR (Passive Infrared) motion sensor with Arduino.
To detect human motion and perform an action such as turning ON an LED.
To understand how PIR sensors work and how digital input signals are handled in microcontroller systems.

Materials Required
- Arduino UNO / Nano / Mega
- PIR Sensor (HC-SR501 or similar)
- LED
- Jumper wires
- USB cable for programming*/

int pirPin = 2;
int ledPin = 13;

void setup() {
    pinMode(pirPin, INPUT);
    pinMode(ledPin, OUTPUT);

    Serial.begin(9600);

    Serial.println("PIR Sensor Initializing...");
    delay(5000);
    Serial.println("System Ready");
}

void loop() {

    int motion = digitalRead(pirPin);

    if(motion == HIGH) {
        digitalWrite(ledPin, HIGH);

        Serial.println("Motion Detected!");
    }
    else {
        digitalWrite(ledPin, LOW);

        Serial.println("No Motion");
    }

    delay(1000);
}

/*Circuit Connections
PIR Sensor Connections
PIR Sensor Pin	  Arduino Connection
VCC	              5V
GND	              GND
OUT	              Pin 2

LED Connections
LED Pin	         Arduino Connection
Anode	           Pin 13
Cathode	         GND*/
