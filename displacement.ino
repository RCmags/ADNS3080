/*
 This sketch shows how to retrieve displacement data.
 */

#include <ADNS3080.h>

// SPI pins:
#define PIN_RESET     45        
#define PIN_CS        47

ADNS3080 <PIN_RESET, PIN_CS> sensor;

// Initial position
int x = 0;
int y = 0;

void setup() {
  sensor.setup( false, false );
  Serial.begin(9600);
}

void loop() {
  int8_t dx, dy;      // Displacement since last function call
  
  sensor.displacement( &dx, &dy );

  // Integrate displacements
  x += dx;
  y += dy;

  // Displacement:
  Serial.print( dx );
  Serial.print( " " );
  Serial.print( dy );
  Serial.print( " " );
  Serial.print( x );
  Serial.print( " " );
  Serial.print( y );
  Serial.println();
}
