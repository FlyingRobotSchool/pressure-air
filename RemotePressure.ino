#include <Wire.h>
#include <BaroSensor.h>
#include "bitlash.h"

// RFD900
// pin 1 to GND
// pin 5 to 5V
// pin 7 to A* TX pin 1 (green)
// pin 9 to A* RX pin 0 (yellow)

// Baro sensor
// SDA to A* pin 2 (orange)
// SCL to A* pin 3 (green)

void serialHandler(byte b) {
  Serial1.write(b);
}

numvar pressure(void) {
  if (!BaroSensor.isOK()) {
    Serial1.print("Sensor not Found/OK. Error: "); 
    Serial1.println(BaroSensor.getError());
    BaroSensor.begin(); // Try to reinitialise the sensor if we can
  }
  else {
    Serial1.print("Temperature: "); 
    Serial1.print(BaroSensor.getTemperature());
    Serial1.print(", Pressure:    ");
    Serial1.println(BaroSensor.getPressure());
  }
  return 0;
}

numvar timer1(void) {
  return TCNT1;   // return the value of Timer 1
}

void setup()
{
  // initialize bitlash and set primary serial port baud
  // print startup banner and run the startup macro
  Serial1.begin(57600);
  while (!Serial1) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  initBitlash(57600);
  setOutputHandler(&serialHandler);

  BaroSensor.begin();
  
  addBitlashFunction("pressure", (bitlash_function)pressure);
  addBitlashFunction("timer1", (bitlash_function)timer1);
}

void loop()
{
  runBitlash();
  if (Serial1.available()) {
    doCharacter(Serial1.read());
  }
}
