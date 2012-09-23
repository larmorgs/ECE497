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

void testMatrix(HT1632LEDMatrix *matrix) {
  //Display "A+"
  matrix->setTextSize(2);
  matrix->setTextColor(1);
  matrix->write('A');
  matrix->write('+');
  matrix->writeScreen();
  usleep(2000000);

  // Blink!
  matrix->blink(true);
  usleep(2000000);
  matrix->blink(false);

  // Dim down and then up
  for (int8_t i = 15; i >= 0; i--) {
    matrix->setBrightness(i);
    usleep(100000);
  }
  for (int8_t i = 0; i < 16; i++) {
    matrix->setBrightness(i);
    usleep(100000);
  }

  // Blink again!
  matrix->blink(true);
  usleep(2000000);
  matrix->blink(false);
}

int main(void) {
  printf("Starting...\n");
  HT1632LEDMatrix matrix = HT1632LEDMatrix(DATA, WR, CS);
  matrix.begin(HT1632_COMMON_16NMOS);
  
  usleep(100000);
  printf("Clear\n");
  matrix.clearScreen();
  
  printf("Test\n");
  testMatrix(&matrix);
  
  printf("Done!\n");
  return 0;
}
