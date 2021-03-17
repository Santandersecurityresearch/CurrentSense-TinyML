// Dirrrrty Haxx...
#define private public
#define protected public

#include <Wire.h>
#include <Adafruit_INA219.h>

Adafruit_INA219 ina219;

int16_t curr_array[16];
int8_t ctr;
int i;

void setup(void) 
{
  Serial.begin(9600);
  while (!Serial) {
      // will pause Zero, Leonardo, etc until serial console opens
      delay(1);
  }

  uint32_t currentFrequency;
    
  Serial.println("Hello!");

  if (! ina219.begin()) {
    Serial.println("Failed to find INA219 chip");
    while (1) { delay(10); }
  }
  // To use a slightly lower 32V, 1A range (higher precision on amps):
  //ina219.setCalibration_32V_1A();
  // Or to use a lower 16V, 400mA range (higher precision on volts and amps):
  //ina219.setCalibration_16V_400mA();

  Serial.println("Measuring voltage and current with INA219 ...");
}

void loop(void) 
{

  for(i=0;i<16;i++){
    curr_array[i] = ina219.getCurrent_raw();
  }

  Serial.print("[");
  for(i=0; i<15; i++){
    Serial.print(curr_array[i]);
    Serial.print(",");
  }
  Serial.print(curr_array[15]);
  Serial.println("]");
}
