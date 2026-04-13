/*
Problem Statement:
Write an Arduino program to create a Birthday Celebration system using OLED display,
buzzer, push button, and LEDs. When the button is pressed, a countdown is shown on
the OLED, followed by a "Happy Birthday" message with particle effects, a melody played
on the buzzer, and LED animation.
*/

/*
Connections:

OLED Display (I2C):
VCC -> 5V
GND -> GND
SCL -> A5
SDA -> A4

Push Button:
One terminal -> Pin 2
Other terminal -> GND (using INPUT_PULLUP)

Buzzer:
Positive (+) -> Pin 8
Negative (-) -> GND

LEDs:
LED1 Anode (+) -> Pin 9 (via 220Ω resistor)
LED2 Anode (+) -> Pin 10 (via 220Ω resistor)
LED3 Anode (+) -> Pin 11 (via 220Ω resistor)
LED4 Anode (+) -> Pin 12 (via 220Ω resistor)
All LED Cathodes (-) -> GND
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

/* Hardware Pins */
const byte buzzer = 8;
const byte button = 2;
const byte leds[] = {9, 10, 11, 12};

/* Notes */
#define G4 392
#define A4 440
#define B4 494
#define C5 523
#define D5 587
#define E5 659
#define F5 698
#define G5 784

/* Melody */
const int melody[] = {
  G4, G4, A4, G4, C5, B4,
  G4, G4, A4, G4, D5, C5,
  G4, G4, G5, E5, C5, B4, A4,
  F5, F5, E5, C5, D5, C5
};

/* Durations */
const int durations[] = {
  300, 300, 600, 600, 600, 1200,
  300, 300, 600, 600, 600, 1200,
  300, 300, 600, 600, 600, 600, 1200,
  300, 300, 600, 600, 600, 1200
};

const int totalNotes = sizeof(melody) / sizeof(melody[0]);

/* Play tone with LED animation */
void playTone(int note, int duration) {
  tone(buzzer, note, duration);

  int ledDelay = duration / 10;
  for (int i = 0; i < 4; i++) {
    digitalWrite(leds[i], HIGH);
    delay(ledDelay);
    digitalWrite(leds[i], LOW);
  }

  delay(duration - (ledDelay * 4));
  noTone(buzzer);
}

/* Center text on OLED */
void showCentered(String text, int size) {
  display.clearDisplay();
  display.setTextSize(size);
  display.setTextColor(SSD1306_WHITE);

  int16_t x1, y1;
  uint16_t w, h;
  display.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);

  int x = (128 - w) / 2;
  int y = (64 - h) / 2;

  display.setCursor(x, y);
  display.print(text);
  display.display();
}

/* Particle effect */
void particles(int count) {
  for (int i = 0; i < count; i++) {
    display.drawPixel(random(0, 128), random(0, 64), SSD1306_WHITE);
  }
}

void setup() {
  pinMode(button, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);

  for (int i = 0; i < 4; i++) {
    pinMode(leds[i], OUTPUT);
  }

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();
}

void loop() {
  if (digitalRead(button) == LOW) {
    delay(50);

    if (digitalRead(button) == LOW) {

      /* Countdown */
      showCentered("3", 4);
      tone(buzzer, G4, 200);
      delay(1000);

      showCentered("2", 4);
      tone(buzzer, A4, 200);
      delay(1000);

      showCentered("1", 4);
      tone(buzzer, B4, 300);
      delay(1000);

      /* Boom */
      showCentered("BOOM!", 2);
      delay(800);

      /* Birthday Message */
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);

      particles(80);

      String msg = "HAPPY BIRTHDAY";
      int16_t x1, y1;
      uint16_t w, h;
      display.getTextBounds(msg, 0, 0, &x1, &y1, &w, &h);
      display.setCursor((128 - w) / 2, (64 - h) / 2);
      display.print(msg);
      display.display();

      delay(1000);

      /* Play Song */
      for (int i = 0; i < totalNotes; i++) {
        playTone(melody[i], durations[i]);
      }

      /* Confetti */
      for (int i = 0; i < 60; i++) {
        display.clearDisplay();
        particles(60);
        display.display();
        delay(50);
      }

      delay(3000);

      display.clearDisplay();
      display.display();
    }
  }
}
