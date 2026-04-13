/*
Problem Statement:
Write an Arduino program to simulate space particle (starfield) animation
on an OLED display using Arduino UNO, where multiple particles move across
the screen to create a dynamic space effect.
*/

/*
Connections:

OLED Display (I2C):
VCC -> 5V
GND -> GND
SCL -> A5
SDA -> A4
*/

#include <Wire.h> 
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define NUM_STARS 40

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int starX[NUM_STARS];
int starY[NUM_STARS];
int starSpeed[NUM_STARS];

void setup() {

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  /* Initialize random seed for variation */
  randomSeed(analogRead(0));

  /* Initialize star positions and speeds */
  for(int i = 0; i < NUM_STARS; i++){
    starX[i] = random(0, SCREEN_WIDTH);
    starY[i] = random(0, SCREEN_HEIGHT);
    starSpeed[i] = random(1, 4);
  }
}

void loop() {

  display.clearDisplay();

  /* Update and draw each star */
  for(int i = 0; i < NUM_STARS; i++){

    display.drawPixel(starX[i], starY[i], SSD1306_WHITE);

    /* Move star from right to left */
    starX[i] -= starSpeed[i];

    /* Reset star when it goes off screen */
    if(starX[i] < 0){
      starX[i] = SCREEN_WIDTH;
      starY[i] = random(0, SCREEN_HEIGHT);
      starSpeed[i] = random(1, 4);
    }
  }

  display.display();
}
