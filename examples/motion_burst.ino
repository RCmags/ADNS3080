/*
 This sketch shows how to retrieve motion burst data and explains the output.
 */

#include <ADNS3080.h>

#define PIN_RESET     45        // SPI pins:
#define PIN_CS        47
#define LED_MODE      false     // Enable LED Mode
#define RESOLUTION    false     // Enable high resolution mode 

ADNS3080 <PIN_RESET, PIN_CS> sensor;

// Initial position
int x = 0;
int y = 0;

void setup() {
  sensor.setup( LED_MODE, RESOLUTION );
  Serial.begin(9600);
}

void loop() {
  uint8_t  motion;      // Did motion occur? true or false
  uint8_t  over_flow;   // Did the displacement registers overflow? true of false. Occurs if |dx| > 125 or |dy| > 125
  int8_t   dx, dy;      // Displacement since last function call
  uint8_t  squal;       // Surface quality value - Larger value means better tracking. If below ~15 the displacement is dissabled. Adjust focus for 30 or more.
  uint16_t shutter;     // Camera shutter rate in clock cycles.
  uint8_t  max_pixel;   // Maximum pixel value of current frame (max brightness)

  sensor.motionBurst( &motion, &over_flow, &dx, &dy, &squal, &shutter, &max_pixel );

  // Integrate displacements
  x += dx;
  y += dy;

  // Other values:
  Serial.print( motion );
  Serial.print( " " );
  Serial.print( over_flow );
  Serial.print( " " );
  Serial.print( squal );
  Serial.print( " " );
  Serial.print( shutter );
  Serial.print( " " );
  Serial.print( max_pixel );
  Serial.print( " " );

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
