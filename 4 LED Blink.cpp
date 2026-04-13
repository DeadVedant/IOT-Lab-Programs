// Problem Statement:
// Write an Arduino program to blink 4 LEDs in sequence using Arduino UNO.

// Connections:
// LED1 Anode (+) -> Pin 2 (via 220Ω resistor)
// LED2 Anode (+) -> Pin 3 (via 220Ω resistor)
// LED3 Anode (+) -> Pin 4 (via 220Ω resistor)
// LED4 Anode (+) -> Pin 5 (via 220Ω resistor)
// All LED Cathodes (-) -> GND

int ledPins[] = {2, 3, 4, 5}; // Array of LED pins

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT); // Set all LED pins as output
  }
}

void loop() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(ledPins[i], HIGH); // Turn ON current LED
    delay(500);                     // Wait
    digitalWrite(ledPins[i], LOW);  // Turn OFF current LED
  }
}
