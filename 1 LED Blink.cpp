// Problem Statement:
// Write an Arduino program to blink an LED at a fixed interval using Arduino UNO.

// Connections:
// LED Anode (+)  -> Digital Pin 13 (via 220Ω resistor)
// LED Cathode (-) -> GND

void setup() {
  pinMode(13, OUTPUT); // Set pin 13 as output
}

void loop() {
  digitalWrite(13, HIGH); // Turn LED ON
  delay(1000);            // Wait for 1 second

  digitalWrite(13, LOW);  // Turn LED OFF
  delay(1000);            // Wait for 1 second
}
