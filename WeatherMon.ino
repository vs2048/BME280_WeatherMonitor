/* ClimateMonitor.ino
 * Uses a BME280 to monitor temp, pressure, and humidity
 *
 * Vladimir Samokhin
 */

#include <LiquidCrystal.h>
#include <stdint.h>
#include "BMEInterface.h"

#define BUTTON_PIN 8
#define NUM_MODES 2
#define DELAY 500
 
BMEInterface* BMEsensor;
LiquidCrystal lcd(7,6,5,4,3,2);

char displayMode = 0;
char buttonPress = 0;

void setup() {
	pinMode(BUTTON_PIN, INPUT_PULLUP);
	lcd.begin(16,2);
	lcd.clear();

  BMEsensor = new BMEInterface();
}

void loop() {
	// Interrogate input
	BMEsensor->poll();
	
	// Update mode if nessisary
	if(digitalRead(BUTTON_PIN) == 0) {
		if(buttonPress == 0) {
			buttonPress = 1;
			displayMode++;
		}
	}
	else {
		buttonPress = 0;
	}
	
	if(displayMode >= NUM_MODES) {
		displayMode = 0;
	}
	
	lcd.clear();
	switch (displayMode) {
		case 0:
			lcd.setCursor(0,0);
			lcd.print("Temp: ");
			lcd.print((uint32_t)BMEsensor->tempC);
			lcd.print(".");
			lcd.print((uint32_t)(BMEsensor->tempC*10)%10);
			lcd.print(" C");

			lcd.setCursor(0,1);
			lcd.print("Humid: ");
			lcd.print((uint8_t)BMEsensor->humidPct);
			lcd.print(" %");
			break;
		case 1:
			lcd.setCursor(0,0);
			lcd.print("Press:");
			if(BMEsensor->pressPa < 100000) {
				lcd.print(" ");
			}
			lcd.print((uint32_t)BMEsensor->pressPa/1000);
		  lcd.print(".");
		  lcd.print((uint32_t)BMEsensor->pressPa/10 %100);
			lcd.print(" kPa");
			
			lcd.setCursor(0,1);
			lcd.print("Alt: ");
			lcd.print((uint8_t)BMEsensor->altFt);
			lcd.print(" ft");
	}
	delay(DELAY);
}
