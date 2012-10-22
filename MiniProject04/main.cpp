#include "../Resources/adafruit/HT1632/HT1632.h"
#include <stdio.h>
#include <unistd.h>
#include "icons.c"

/* 
This demo outputs the data fed into stdin to the HT1632 for the 16x24 LED matrix
*/

#define BANK 1
#define DATA 28 //1_28
#define WR 17 //1_17
#define CS 16 //1_16

unsigned char data[48];

main(int argc, char *argv[]) {
  if (argc != 49) {
    return 1;
  } else {
    printf("Starting...\n");
    HT1632LEDMatrix matrix = HT1632LEDMatrix(BANK, DATA, WR, CS);
    matrix.begin(HT1632_COMMON_16NMOS);
    
    printf("Clear\n");
    matrix.clearScreen();
    for (int i = 0; i < 48; i++) {
      sscanf(argv[i+1], "%hhu", &data[i]);
    }
    printf("Drawing\n");
    matrix.drawBitmap(0, 0, data, matrix.width(), matrix.height(), 1);  
    matrix.writeScreen();
    usleep(2000000);

    // Blink!
    matrix.blink(true);
    usleep(2000000);
    matrix.blink(false);

    // Dim down and then up
    for (int8_t i = 15; i >= 0; i--) {
      matrix.setBrightness(i);
      usleep(100000);
    }
    for (int8_t i = 0; i < 16; i++) {
      matrix.setBrightness(i);
      usleep(100000);
    }

    // Blink again!
    matrix.blink(true);
    usleep(2000000);
    matrix.blink(false);
    printf("Done!\n");
    return 0;
  }
}
