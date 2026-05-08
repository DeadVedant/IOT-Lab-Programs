/*Experiment No. 5
Title: Design a Simple IoT System Using Ultrasonic Sensor and IR Sensor
Objective

Design an IoT system where:

An Ultrasonic Sensor detects if an object is within a specific range and triggers a buzzer.
An IR Sensor detects motion and turns ON an LED.

Materials Required
- Arduino Uno
- Ultrasonic Sensor (HC-SR04)
- IR Motion Sensor (HC-SR501)
- Buzzer
- LED
- 220Ω Resistor
- Breadboard and Jumper Wires
- USB Cable / Power Supply
- Arduino IDE*/

#define trigPin 9
#define echoPin 10

#define irSensor 7
#define buzzer 8
#define led 6

long duration;
int distance;

void setup() {

    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    pinMode(irSensor, INPUT);

    pinMode(buzzer, OUTPUT);
    pinMode(led, OUTPUT);

    Serial.begin(9600);
}

void loop() {

    // Ultrasonic Sensor
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);

    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);

    distance = duration * 0.034 / 2;

    Serial.print("Distance: ");
    Serial.println(distance);

    if(distance < 15) {
        digitalWrite(buzzer, HIGH);
    }
    else {
        digitalWrite(buzzer, LOW);
    }

    // IR Sensor
    int motion = digitalRead(irSensor);

    if(motion == LOW) {
        digitalWrite(led, HIGH);
        Serial.println("Object Detected");
    }
    else {
        digitalWrite(led, LOW);
        Serial.println("No Object");
    }

    delay(1000);
}

/*Circuit Connections
Ultrasonic Sensor (HC-SR04)
Sensor Pin	  Arduino Connection
VCC	          5V
GND	          GND
TRIG	        Pin 9
ECHO	        Pin 10

IR Sensor
IR Pin	      Arduino Connection
VCC	          5V
GND	          GND
OUT	          Pin 7

Buzzer
Buzzer Pin	  Arduino Connection
VCC	          5V
GND	          GND
OUT	          Pin 8

LED
LED Pin	      Arduino Connection
Positive	    Pin 6
Negative	    GND through resistor*/
