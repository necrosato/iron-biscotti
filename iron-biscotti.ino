#include "Keyboard.h"

void load_delay() {
  while(true) {
    delay(1000);
    Serial.println("Waiting for upload...");
  }
}

void typeKey(int key) {
  Keyboard.press(key);
  delay(50);
  Keyboard.release(key);
}

void InitMacOS() {
  // macOS prologue, escapes new keyboard setup (macOS Sierra+)
  delay(500);
  typeKey(KEY_ESC);
  delay(500);
  typeKey(KEY_ESC);
  delay(500);
  typeKey(KEY_RETURN);
  delay(500);
  typeKey(KEY_ESC);
  delay(500);
}

// This presses cmdd + shift + s for 10 seconds to initiate single user mode
void SingleUserMode() {
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press('s');
  delay(10000);
  Keyboard.releaseAll();
}

void setup() {
  // Begining the Keyboard stream
  Keyboard.begin();
  // pushbutton setup, check for new script
  pinMode(8, INPUT);
  delay(100);
  if(digitalRead(8) == HIGH) {
    Serial.begin(115200);
    load_delay();
  }
  SingleUserMode();
}

void loop() {
  delay(1000);
}
