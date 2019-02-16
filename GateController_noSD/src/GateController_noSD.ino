/*
 * Project GateController_v1
 * Description: Brains of controller down at the gate, reads FIRE input and fires relay accordingly
 * Author: Steven Bucher
 * Date: 12-26-18
 */

#include "Adafruit_SSD1306.h"

#define OLED_RESET D8
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

// Pins on OLED board
const int aPin = 4;
const int bPin = 3;
const int cPin = 2;

// Pins for controlling relay and reading FIRE
const int relayPin = 5;
const int fireInput = 6;

// Variables for scheduling
int openTime;
int closeTime;

void setup() {

  // Setting up all necesarry pins
  pinMode(relayPin, OUTPUT);
  pinMode(fireInput, INPUT);
  pinMode(aPin, INPUT_PULLUP);
  pinMode(bPin, INPUT);
  pinMode(cPin, INPUT_PULLUP);

  // Setting up OLED display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)'
  display.display(); // show splashscreen
  delay(1000);
  display.clearDisplay();   // clears the screen and buffer
  display.display();

  Particle.syncTime();
  

  Particle.subscribe("gate", recieving);
}



void loop() {

  if(!digitalRead(fireInput)){
    digitalWrite(relayPin, HIGH);
    oledPrint(0,15, "OPEN", true, 3);
  }else{
    if(!digitalRead(aPin)){
      //Pulse for 3 seconds
      oledPrint(0,15, "One car", true, 3);
      digitalWrite(relayPin, HIGH);
      delay(3000);
      digitalWrite(relayPin, LOW);
    } else if(!digitalRead(cPin)) {
      //alwasy keep off 
      oledPrint(0,15, "KEEP CLOSE", true, 3);
      digitalWrite(relayPin, LOW);
    } else if(!digitalRead(bPin)){
      // always keep on
      oledPrint(0,15, "KEEP OPEN", true, 3);
      digitalWrite(relayPin, HIGH);

    } else{
      digitalWrite(relayPin, LOW);
    }
  }

}

bool checkSchedule(void){

}

void recieving(const char *event, const char *data){
  int alwaysOn;
  int alwaysOff;
  int pulseOnce;
}

void oledPrint(int row, int col, String value, bool clear, float size){
    if(clear)
        display.clearDisplay();
    display.setTextColor(WHITE);
    display.setCursor(row, col);
    display.setTextSize(size);
    display.println(value);
    display.display();
}
