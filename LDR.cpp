/*
Problem Statement:
Write an Arduino program using an LDR (Light Dependent Resistor) such that
when the light intensity drops below a threshold value (~350), all 4 LEDs turn ON.
Otherwise, all LEDs remain OFF.
*/

/*
Connections:

LDR (Voltage Divider):
One end of LDR  -> 5V
Other end of LDR -> A0 and to one end of 10kΩ resistor
Other end of resistor -> GND

LEDs:
LED1 Anode (+) -> Pin 2 (via 220Ω resistor)
LED2 Anode (+) -> Pin 3 (via 220Ω resistor)
LED3 Anode (+) -> Pin 4 (via 220Ω resistor)
LED4 Anode (+) -> Pin 5 (via 220Ω resistor)
All LED Cathodes (-) -> GND
*/

const int ldrPin = A0;
const int threshold = 350;

int ledPins[] = {2, 3, 4, 5};

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  Serial.begin(9600); // Optional: for monitoring LDR values
}

void loop() {
  int ldrValue = analogRead(ldrPin);

  // Debugging (optional)
  Serial.println(ldrValue);

  if (ldrValue < threshold) {
    // Low light → Turn all LEDs ON
    for (int i = 0; i < 4; i++) {
      digitalWrite(ledPins[i], HIGH);
    }
  } else {
    // Bright light → Turn all LEDs OFF
    for (int i = 0; i < 4; i++) {
      digitalWrite(ledPins[i], LOW);
    }
  }

  delay(200);
}
