#include "application.h"
#include "TMP006.h"
#include <math.h>

// Read 16 bit int from I2C address addr and register reg
uint16_t read16(uint8_t addr, uint8_t reg) {
  uint16_t data;

  Wire.beginTransmission(addr);
  Wire.write(reg); // send register address to read from
  Wire.endTransmission();
  
  Wire.beginTransmission(addr);
  Wire.requestFrom((uint8_t)addr, (uint8_t)2); // request 2 bytes of data
  data = Wire.read(); // receive data
  data <<= 8;
  data |= Wire.read();
  Wire.endTransmission();

  return data;
}

// Write data to I2C address addr, register reg
void write16(uint8_t addr, uint8_t reg, uint16_t data) {
  Wire.beginTransmission(addr);
  Wire.write(reg); // sends register address to write to
  Wire.write(data>>8);  // write data
  Wire.write(data); 
  Wire.endTransmission();
}


// Configures sensor, use before reading from it
void config_TMP006(uint8_t addr, uint16_t samples)
{
  Wire.begin();
  write16(addr, TMP006_CONFIG, samples | TMP006_CFG_MODEON | TMP006_CFG_DRDYEN);
}

// Read raw sensor temperature
int16_t readRawDieTemperature(uint8_t addr)
{
  int16_t raw = read16(addr, TMP006_TAMB);

  raw >>= 2;
  return raw;
}

// Read raw thermopile voltage
int16_t readRawVoltage(uint8_t addr) 
{
  int16_t raw = read16(addr, TMP006_VOBJ);
  return raw;
}

// Calculate object temperature based on raw sensor temp and thermopile voltage
double readObjTempC(uint8_t addr) 
{
  double Tdie = readRawDieTemperature(addr);
  double Vobj = readRawVoltage(addr);
  Vobj *= 156.25;  // 156.25 nV per LSB
  Vobj /= 1000000000; // nV -> V
  Tdie *= 0.03125; // convert to celsius
  Tdie += 273.15; // convert to kelvin

  // Equations for calculating temperature found in section 5.1 in the user guide
  double tdie_tref = Tdie - TMP006_TREF;
  double S = (1 + TMP006_A1*tdie_tref + 
      TMP006_A2*tdie_tref*tdie_tref);
  S *= TMP006_S0;
  S /= 10000000;
  S /= 10000000;

  double Vos = TMP006_B0 + TMP006_B1*tdie_tref + 
    TMP006_B2*tdie_tref*tdie_tref;

  double fVobj = (Vobj - Vos) + TMP006_C2*(Vobj-Vos)*(Vobj-Vos);

  double Tobj = sqrt(sqrt(Tdie * Tdie * Tdie * Tdie + fVobj/S));

  Tobj -= 273.15; // Kelvin -> *C
  return Tobj;
}

// Caculate sensor temperature based on raw reading
double readDieTempC(uint8_t addr) 
{
  double Tdie = readRawDieTemperature(addr);
  Tdie *= 0.03125; // convert to celsius
  return Tdie;
}