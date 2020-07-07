
/* 

http://pulsedlight3d.com

This sketch demonstrates getting distance with the LIDAR-Lite Sensor

It utilizes the 'Arduino Wire Library'

*/

#include <Wire.h>
#define    LIDARLite_ADDRESS   0x62          // Default I2C Address of LIDAR-Lite.
#define    RegisterMeasure     0x00          // Register to write to initiate ranging.
#define    MeasureValue        0x04          // Value to initiate ranging.
#define    RegisterHighLowB    0x8f          // Register to get both High and Low bytes in 1 call.

int reading = 0;

void setup()
{
  Wire.begin(); // join i2c bus
  Serial.begin(9600); // start serial communication at 9600bps
  
  Wire.beginTransmission((int)LIDARLite_ADDRESS); // transmit to LIDAR-Lite
  Wire.write((int)RegisterMeasure); // sets register pointer to  (0x00)  
  Wire.write((int)MeasureValue); // sets register pointer to  (0x00)  
  Wire.endTransmission(); // stop transmitting

  Wire.beginTransmission((int)LIDARLite_ADDRESS); // transmit to LIDAR-Lite
  Wire.write(0x04); // sets register pointer to  (0x00)  
  Wire.write(0xa0); // sets register pointer to  (0x00)  
  Wire.endTransmission(); // stop transmitting

  Wire.beginTransmission((int)LIDARLite_ADDRESS); // transmit to LIDAR-Lite
  Wire.write(0x68); // sets register pointer to  (0x00)  
  Wire.write(0x50); // sets register pointer to  (0x00)  
  Wire.endTransmission(); // stop transmitting
}

void loop()
{
  Wire.beginTransmission((int)LIDARLite_ADDRESS); // transmit to LIDAR-Lite
  Wire.write((int)RegisterMeasure); // sets register pointer to  (0x00)  
  Wire.write((int)MeasureValue); // sets register pointer to  (0x00)  
  Wire.endTransmission(); // stop transmitting

  delay(20); // Wait 20ms for transmit

  //velocity
  Wire.beginTransmission((int)LIDARLite_ADDRESS); // transmit to LIDAR-Lite
  Wire.write(0x09); // sets register pointer to (0x8f)
  Wire.endTransmission(); // stop transmitting

  Wire.requestFrom((int)LIDARLite_ADDRESS, 1); // request 2 bytes from LIDAR-Lite
  if(1 <= Wire.available()) // if two bytes were received
  {
    int8_t velocity = Wire.read();
    velocity = velocity * 0.25;
    velocity = (velocity * 60*60)/1000;
    Serial.println(velocity); // print the reading
  }
  delay(100); // Wait 20ms for transmit

}
