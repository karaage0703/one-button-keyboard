#include "Keyboard.h"
#define PIN_KEYSW (9)
const int SHORT_TIME = 20;
const int LONG_TIME = 1000;

int val;
int lastVal;
int timer;
int once;

int key_numb = 0;
const int MAX_KEY_NUMB = 3;
const int ASCII_OFFSET = 48;  // for '0'
int mode = 0;  // 0: Skeleton Sequencer  1: Normal Mode

void setup() {
  pinMode(PIN_KEYSW, INPUT_PULLUP);
  val = HIGH;
  lastVal = HIGH;
  timer = 0;
  once = 0;
  Keyboard.begin();
}

void loop() {
  val = digitalRead(PIN_KEYSW);
  if (val == LOW) {
    timer++;
    lastVal = LOW;
    delay(1);
  } else {
    if(lastVal == LOW && !once){
      if(timer > SHORT_TIME){
        key_numb = key_numb % MAX_KEY_NUMB;
        Keyboard.press(key_numb + ASCII_OFFSET);
        key_numb++;
        delay(10);
        Keyboard.releaseAll();
      }
    }
    lastVal = HIGH;
    timer = 0;
    once = 0;
  }
  if (timer > LONG_TIME) {
    timer = LONG_TIME + 1;
    if (!once) {
      if (mode == 0){
        Keyboard.press('s');
        mode = 1;
      }else{
        Keyboard.press('m');
        mode = 0;
      }
        
      once = 1;
      delay(10);
      Keyboard.releaseAll();
    }
  }
}
