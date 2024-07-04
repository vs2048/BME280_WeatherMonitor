/* BMEInterface.h
 * 
 * More user friendly interface to sparkfun's bme library
 */
 
#ifndef BMEINTRERFACE_H
#define BMEINTRERFACE_H

#include "SparkFunBME280.h"
#include "Wire.h"
#include "Arduino.h"

class BMEInterface
{
	public:
		BMEInterface();
		void poll();
		float pressPa;
		float humidPct;
		float tempC;
		float altFt;
	private:
		BME280 BMESensor;
};


#endif
