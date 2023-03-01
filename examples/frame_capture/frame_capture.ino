/*
 This sketch shows how to retrieve frame capture data. It generates an asci image of what the camera sees.
 */

#include <ADNS3080.h>

// SPI pins:
#define PIN_RESET     9        
#define PIN_CS        10

ADNS3080 <PIN_RESET, PIN_CS> sensor;

// Convert a pixel into a character
char pixelSymbol(int k) {
  constexpr char scale[] = "#987654321-,.'` ";        // 16 characters
  return scale[k >> 4];                               // Divide uint8_t by 4
}

void setup() {
  sensor.setup();
  Serial.begin(9600);
}

void loop() {
  // Array to store frame
  uint8_t frame[ADNS3080_PIXELS][ADNS3080_PIXELS];    // The number of pixels are included in the header file. Nx = Ny = 30

  // Retrieve frame
  sensor.frameCapture( frame );

  // Scan axes and display pixel
  for(int x = 0; x < ADNS3080_PIXELS; x += 1 ) {
    for(int y = 0; y < ADNS3080_PIXELS; y += 1 ) {
      Serial.print( pixelSymbol( frame[x][y] ) );
      Serial.print(' ');
    }
    Serial.println();
  }
  Serial.println();
}
