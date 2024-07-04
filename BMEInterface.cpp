/* BMEInterface.cpp
 * 
 * More user friendly interface to sparkfun's bme library
 */
 
#include "BMEInterface.h"
 
BMEInterface::BMEInterface() {
	pressPa = 0;
	humidPct = 0;
	tempC = 0;
	altFt = 0;
	
	
	//***Driver settings********************************//
	//commInterface can be I2C_MODE or SPI_MODE
	//specify chipSelectPin using arduino pin names
	//specify I2C address.  Can be 0x77(default) or 0x76
	
	//For I2C, enable the following and disable the SPI section
	BMESensor.settings.commInterface = I2C_MODE;
	BMESensor.settings.I2CAddress = 0x77;
	
	//For SPI enable the following and dissable the I2C section
	//BMESensor.settings.commInterface = SPI_MODE;
	//BMESensor.settings.chipSelectPin = 10;


	//***Operation settings*****************************//
	
	//renMode can be:
	//  0, Sleep mode
	//  1 or 2, Forced mode
	//  3, Normal mode
	BMESensor.settings.runMode = 3; //Forced mode
	
	//tStandby can be:
	//  0, 0.5ms
	//  1, 62.5ms
	//  2, 125ms
	//  3, 250ms
	//  4, 500ms
	//  5, 1000ms
	//  6, 10ms
	//  7, 20ms
	BMESensor.settings.tStandby = 0;
	
	//filter can be off or number of FIR coefficients to use:
	//  0, filter off
	//  1, coefficients = 2
	//  2, coefficients = 4
	//  3, coefficients = 8
	//  4, coefficients = 16
	BMESensor.settings.filter = 0;
	
	//tempOverSample can be:
	//  0, skipped
	//  1 through 5, oversampling *1, *2, *4, *8, *16 respectively
	BMESensor.settings.tempOverSample = 1;

	//pressOverSample can be:
	//  0, skipped
	//  1 through 5, oversampling *1, *2, *4, *8, *16 respectively
    BMESensor.settings.pressOverSample = 1;
	
	//humidOverSample can be:
	//  0, skipped
	//  1 through 5, oversampling *1, *2, *4, *8, *16 respectively
	BMESensor.settings.humidOverSample = 1;

	BMESensor.begin();
  
	delay(10);  //Use delay if reading directly after .begin is called.  BME280 requires 2ms to start up.
}

void BMEInterface::poll() {
	pressPa = BMESensor.readFloatPressure();
	humidPct = BMESensor.readFloatHumidity();
	tempC = BMESensor.readTempC();
	altFt = BMESensor.readFloatAltitudeFeet();
}
