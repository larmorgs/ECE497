#include "../Resources/adafruit/HT1632/HT1632.h"
#include <stdio.h>
#include <unistd.h>

/* 
This is a basic demo program showing how to write to a HT1632
These can be used for up to 16x24 LED matrix grids, with internal memory
and using only 3 pins - data, write and select.
Multiple HT1632's can share data and write pins, but need unique CS pins.
*/

#define DATA 117 //3_21
#define WR 49 //1_17
#define CS 48 //1_16

void testMatrix(HT1632 *matrix) {
  for (int i=0; i<24*16; i++) {
    matrix->setPixel(i);
    matrix->writeScreen();
  }
  
  // blink!
  matrix->blink(true);
  sleep(2000);
  matrix->blink(false);
  
  // Adjust the brightness down 
  for (int8_t i=15; i>=0; i--) {
   matrix->setBrightness(i);
   sleep(100);
  }
  // then back up
  for (uint8_t i=0; i<16; i++) {
   matrix->setBrightness(i);
   sleep(100);
  }

  // Clear it out
  for (int i=0; i<24*16; i++) {
    matrix->clrPixel(i);
    matrix->writeScreen();
  }
}

int main(void) {
  HT1632 matrix = HT1632(DATA, WR, CS);
  matrix.begin(HT1632_COMMON_16NMOS);
  
  sleep(100);
  matrix.clearScreen();
  
  testMatrix(&matrix);
}
