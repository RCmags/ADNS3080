/*
 This sketch shows how to retrieve motion burst data and explains the output.
 */

#include <ADNS3080.h>

// SPI pins
#define PIN_RESET     9         
#define PIN_CS        10        

// sensor configuration 
#define LED_MODE      false     // If true, enables LED Mode
#define RESOLUTION    false     // If true, enable high resolution mode 

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
  int8_t   dx, dy;      // Displacement since last function call
  uint8_t  squal;       // Surface quality value - Larger value means better tracking. If below ~15 the displacement is dissabled. Adjust focus for 30 or more.
  uint16_t shutter;     // Camera shutter rate in clock cycles.
  uint8_t  max_pixel;   // Maximum pixel value of current frame (max brightness)

  sensor.motionBurst( &motion, &dx, &dy, &squal, &shutter, &max_pixel );

  // Integrate displacements
  x += dx;
  y += dy;

  // Other values:
  Serial.print( "motn=" );
  Serial.print( motion );
  Serial.print( " squal=" );
  Serial.print( squal );
  Serial.print( " shutr=" );
  Serial.print( shutter );
  Serial.print( " maxpix=" );
  Serial.print( max_pixel );

  // Displacement:
  Serial.print( " dx=" );
  Serial.print( dx );
  Serial.print( " dy=" );
  Serial.print( dy );
  Serial.print( " x=" );
  Serial.print( x );
  Serial.print( " y=" );
  Serial.print( y );
  Serial.println();
}
