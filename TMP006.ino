// This #include statement was automatically added by the Spark IDE.
#include "TMP006.h"

uint8_t sensor1 = 0x40; // I2C address of TMP006, can be 0x40-0x47
uint16_t samples = TMP006_CFG_8SAMPLE; // # of samples per reading, can be 1/2/4/8/16

char szInfo[128];

void setup(){
    Serial.begin(9600);
    Serial.println("TMP006 Example");

    config_TMP006(sensor1, samples);
}

void loop()
{
    float object_temp = readObjTempC(sensor1);
    Serial.print("Object Temperature: "); 
    Serial.print(object_temp); Serial.println("*C");

    float sensor_temp = readDieTempC(sensor1);
    Serial.print("Sensor Temperature: "); 
    Serial.print(sensor_temp); Serial.println("*C");
    
    sprintf(szInfo, "Object Temperature: %2.2f, Sensor Temperature: %2.2f", object_temp, sensor_temp);
    
    Spark.publish("tmp006info", szInfo);

    delay(2000); // delay 1 second for every 4 samples per reading
}