#include "BM.h"
#include "vars.h"
#include "micro_sd.h"
#include <DFRobot_BMP3XX.h>
#include "SD.h"
#include "string.h"
#include "vars.h"

using namespace std;

#define CALIBRATE_ABSOLUTE_DIFFERENCE

float max_alti = 0;

DFRobot_BMP388_I2C sensor(&Wire, sensor.eSDOVDD);

void setup_BM(){
    int rslt;
    while( ERR_OK != (rslt = sensor.begin()) ){
        if(ERR_DATA_BUS == rslt){
            Serial.println("Data bus error!!!");
        }else if(ERR_IC_VERSION == rslt){
            Serial.println("Chip versions do not match!!!");
        }
        delay(3000);
    }
    Serial.println("Begin ok!");

    while( !sensor.setSamplingMode(sensor.eUltraPrecision) ){
        Serial.println("Set samping mode fail, retrying....");
        delay(3000);
    }

    delay(100);
    //540.0
    #ifdef CALIBRATE_ABSOLUTE_DIFFERENCE
    if( sensor.calibratedAbsoluteDifference(80.0) ){
        Serial.println("Absolute difference base value set successfully!");
    }
    #endif

    float sampingPeriodus = sensor.getSamplingPeriodUS();
    Serial.print("samping period : ");
    Serial.print(sampingPeriodus);
    Serial.println(" us");

    float sampingFrequencyHz = 1000000 / sampingPeriodus;
    Serial.print("samping frequency : ");
    Serial.print(sampingFrequencyHz);
    Serial.println(" Hz");

    Serial.println();
}

void update_BM(){

    Pressure = sensor.readPressPa();
    altitude = sensor.readAltitudeM();
    temperature = sensor.readTempC();

    if(altitude>max_alti){
        max_alti = altitude;
    }

}


void print_BM(){

    // float sampingPeriodus = sensor.getSamplingPeriodUS();
    // Serial.print("samping period : ");
    // Serial.print(sampingPeriodus);
    // Serial.println(" us");

    // float sampingFrequencyHz = 1000000 / sampingPeriodus;
    // Serial.print("samping frequency : ");
    // Serial.print(sampingFrequencyHz);
    // Serial.println(" Hz");

    Serial.println();
    //update_BM(SD);
    Serial.print("temperature : ");
    Serial.print(temperature);
    Serial.println(" C");

    Serial.print("Pressure : ");
    Serial.print(Pressure);
    Serial.println(" Pa");

    Serial.print("Altitude : ");
    Serial.print(altitude);
    Serial.println(" m");

    Serial.print("Max altitude : ");
    Serial.println(max_alti);

    Serial.print("Started: ");
    Serial.println(started);



    Serial.println();
}