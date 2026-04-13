/*
Problem Statement:
Write an Arduino program using an Ultrasonic Sensor, OLED display, and buzzer such that
when an object comes closer than ~25 cm, the buzzer beeps continuously indicating an intruder.
The OLED display should show the distance readings along with status as "SAFE" or "INTRUDER".
*/

/*
Connections:

Ultrasonic Sensor (HC-SR04):
VCC  -> 5V
GND  -> GND
TRIG -> Pin 9
ECHO -> Pin 10

Buzzer:
Positive (+) -> Pin 8
Negative (-) -> GND

OLED Display (I2C):
VCC -> 5V
GND -> GND
SCL -> A5
SDA -> A4
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

/* OLED Setup */
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

/* Pins */
const byte trigPin = 9;
const byte echoPin = 10;
const byte buzzer = 8;

/* Threshold Distance (cm) */
const int threshold = 25;

/* Function to measure distance */
long getDistance() {
  long duration, distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = duration * 0.034 / 2; // Convert to cm
  return distance;
}

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
}

/* Main Loop */
void loop() {

  long distance = getDistance();

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  /* Show Distance */
  display.setCursor(0, 10);
  display.print("Distance: ");
  display.print(distance);
  display.println(" cm");

  /* Condition Check */
  if (distance > 0 && distance < threshold) {

    /* Intruder Detected */
    display.setCursor(0, 30);
    display.setTextSize(2);
    display.println("INTRUDER!");

    /* Continuous Buzzer */
    tone(buzzer, 1000);

  } else {

    /* Safe State */
    display.setCursor(0, 30);
    display.setTextSize(2);
    display.println("SAFE");

    noTone(buzzer);
  }

  display.display();

  delay(200);
}
