/*
Problem Statement:
Write an Arduino program using 4 LEDs, 4 push buttons, and a buzzer such that
when any button is pressed, the corresponding LED turns ON and the buzzer beeps once.
When the button is released, the LED and buzzer turn OFF.
*/

/*
Connections:
LED1 Anode (+) -> Pin 2 (via 220Ω resistor)
LED2 Anode (+) -> Pin 3 (via 220Ω resistor)
LED3 Anode (+) -> Pin 4 (via 220Ω resistor)
LED4 Anode (+) -> Pin 5 (via 220Ω resistor)
All LED Cathodes (-) -> GND

Switch1 -> Pin 6
Switch2 -> Pin 7
Switch3 -> Pin 8
Switch4 -> Pin 9
Other terminal of all switches -> GND (using INPUT_PULLUP)

Buzzer (+) -> Pin 10
Buzzer (-) -> GND
*/

int ledPins[] = {2, 3, 4, 5};
int buttonPins[] = {6, 7, 8, 9};
int buzzer = 10;

bool lastState[4] = {HIGH, HIGH, HIGH, HIGH}; // To detect button press transition

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
  pinMode(buzzer, OUTPUT);
}

void loop() {
  for (int i = 0; i < 4; i++) {
    bool currentState = digitalRead(buttonPins[i]);

    if (currentState == LOW) { 
      digitalWrite(ledPins[i], HIGH);

      // Beep only once when button is newly pressed
      if (lastState[i] == HIGH) {
        digitalWrite(buzzer, HIGH);
        delay(100);
        digitalWrite(buzzer, LOW);
      }
    } else {
      digitalWrite(ledPins[i], LOW);
    }

    lastState[i] = currentState;
  }
}
