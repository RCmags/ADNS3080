//------------ Read and write registers --------------
 
template<TEMPLATE_TYPE>
void ADNS3080<TEMPLATE_INPUTS>
::writeRegister( const uint8_t reg, uint8_t output ) {
  // Enable communication
  digitalWrite( PIN_NCS, LOW );
  SPI.transfer( reg | B10000000 );
  
  // Send value
  SPI.transfer( output );
  
  // Disable communcation
  digitalWrite( PIN_NCS, HIGH );
  delayMicroseconds( ADNS3080_T_SWW );
}

template<TEMPLATE_TYPE>
uint8_t ADNS3080<TEMPLATE_INPUTS>
::readRegister( const uint8_t reg ) {
  // Enable communication
  digitalWrite( PIN_NCS, LOW );
  SPI.transfer( reg );
  delayMicroseconds( ADNS3080_T_SRAD_MOT );
  
  // Receive value
  uint8_t output = SPI.transfer(0x00);
  
  // Dissable communication
  digitalWrite( PIN_NCS, HIGH ); 
  return output;
}

//------------ Miscellaneous functions ---------------

// Cycle reset pin
template<TEMPLATE_TYPE>
void ADNS3080<TEMPLATE_INPUTS>
::reset() {
  digitalWrite( PIN_RESET, HIGH );
  delayMicroseconds( ADNS3080_T_PW_RESET );                  
  digitalWrite( PIN_RESET, LOW );
  delayMicroseconds( ADNS3080_T_IN_RST );              
}

// Initialize and configure sensor
template<TEMPLATE_TYPE>
bool ADNS3080<TEMPLATE_INPUTS>
::setup( const bool led_mode, const bool resolution ) {
  
  // Configure SPI
  SPI.begin();
  SPI.setClockDivider( SPI_CLOCK_DIV32 );
  SPI.setDataMode( SPI_MODE3 );
  SPI.setBitOrder( MSBFIRST );  
  
  // Set sensor pins
  pinMode( PIN_RESET, OUTPUT );
  pinMode( PIN_NCS,   OUTPUT );

  // Disable communication and reset 
  digitalWrite( PIN_NCS, HIGH );
  reset();
 
  // Configure sensor:
  //                          LED Shutter    High resolution
  uint8_t mask = B00000000 | led_mode << 6 | resolution << 4;      
  writeRegister( ADNS3080_CONFIGURATION_BITS, mask );

  // Check Connection
  if( readRegister(ADNS3080_PRODUCT_ID) == ADNS3080_PRODUCT_ID_VALUE ) {
    return true;
  } else {
    return false;
  } 
}

// Clear DELTA_X, DELTA_Y and motion registers
template<TEMPLATE_TYPE>
void ADNS3080<TEMPLATE_INPUTS>
::motionClear() {
  writeRegister( ADNS3080_MOTION_CLEAR, 0x00 );
}

//----------------- Major outputs --------------------

// Get motion burst data
template<TEMPLATE_TYPE>
void ADNS3080<TEMPLATE_INPUTS>
::motionBurst( uint8_t *motion, int8_t *dx, int8_t *dy, 
               uint8_t *squal, uint16_t *shutter, uint8_t *max_pix ) {
  
  // Enable communication
  digitalWrite( PIN_NCS, LOW );
  SPI.transfer( ADNS3080_MOTION_BURST );
  delayMicroseconds( ADNS3080_T_SRAD_MOT );

  // Receieve data:
  uint8_t motion_byte = SPI.transfer(0x00);
  *motion     = (motion_byte & B10000000) >> 7;
  //
  *dx      = SPI.transfer(0x00);
  *dy      = SPI.transfer(0x00);
  *squal   = SPI.transfer(0x00);
  *shutter = SPI.transfer16(0x00);
  *max_pix = SPI.transfer(0x00);

  // Disable communication
  digitalWrite( PIN_NCS, HIGH ); 

  // Zero displacement if motion did not occur
  if( *motion == false ) {
    *dx = 0;
    *dy = 0;
  }
}

// Get displacement data from motion burst
template<TEMPLATE_TYPE>
void ADNS3080<TEMPLATE_INPUTS>
::displacement( int8_t *dx, int8_t *dy ) {
  
  // Enable communication
  digitalWrite( PIN_NCS, LOW );
  SPI.transfer( ADNS3080_MOTION_BURST );
  delayMicroseconds( ADNS3080_T_SRAD_MOT );

  // Check if motion occured
  uint8_t motion  = (SPI.transfer(0x00) & B10000000) >> 7;
 
  if( motion == true ) {
    *dx = SPI.transfer(0x00);
    *dy = SPI.transfer(0x00);
  } else {
    *dx = 0;
    *dy = 0;
  }

  // Disable communication
  digitalWrite( PIN_NCS, HIGH ); 
}  

// Retreive pixels of next frame:
template<TEMPLATE_TYPE>
void ADNS3080<TEMPLATE_INPUTS>
::frameCapture( uint8_t output[ADNS3080_PIXELS][ADNS3080_PIXELS] ) {  
  
  // Store pixel values
  writeRegister( ADNS3080_FRAME_CAPTURE, 0x83 );
  
  // Enable communication
    digitalWrite( PIN_NCS, LOW );
  SPI.transfer( ADNS3080_PIXEL_BURST );
  delayMicroseconds( ADNS3080_T_SRAD );

  //-- First pixel:
  uint8_t pixel = 0;

  // Recieve pixels until first is found 
  while( (pixel & B01000000) == 0 ) {
      pixel = SPI.transfer(0x00);
      delayMicroseconds( ADNS3080_T_LOAD );  
  }
  
  //-- Scan first frame:
  for( int y = 0; y < ADNS3080_PIXELS; y += 1 ) {
    for( int x = 0; x < ADNS3080_PIXELS; x += 1 ) {  
      
      // Store and scale past pixel
      output[x][y] = pixel << 2; 
      
      // Receive new pixel
      pixel = SPI.transfer(0x00);
      delayMicroseconds( ADNS3080_T_LOAD );  
    }
  }
  // Disable communication
  digitalWrite( PIN_NCS, HIGH ); 
  delayMicroseconds( ADNS3080_T_LOAD + ADNS3080_T_BEXIT );
}    
