#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

#define I2CAddress 0x3F
#define backlightPin 3
#define EnPin 2
#define RwPin 1
#define RsPin 0
#define D4Pin 4
#define D5Pin 5
#define D6Pin 6
#define D7Pin 7


LiquidCrystal_I2C	lcd(I2CAddress, EnPin, RwPin, RsPin, D4Pin, D5Pin, D6Pin, D7Pin);

void setup()
{
	lcd.begin (16, 2);
	lcd.setBacklightPin(backlightPin, POSITIVE);
	lcd.setBacklight(LOW);
	lcd.home ();

	lcd.setCursor (0, 0);
	lcd.print("1234567890123456");
	lcd.setCursor (0, 1);
	lcd.print("Line 2");
}

void loop()
{

}
