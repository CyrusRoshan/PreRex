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

//

int analogPin = 0;
int raw = 0;
float vOut = 0;

int keyPos = 10;
bool timeSet = false;

bool exitNow;
char lastPushed;

//recorded = [66, 71, 77, 83, 213, 229, 248, 270, 298, 330, 370, 422, 490, 591, 735, 966]
int values[17] = {64, 69, 75, 80, 190, 221, 240, 260, 285, 315, 350, 396, 456, 541, 666, 850, 1050};

char keys[16] = {'*', '7', '4', '1', '0', '#', 'D', '8', '9', 'C', '5', '6', 'B', '2', '3', 'A'};

LiquidCrystal_I2C lcd(I2CAddress, EnPin, RwPin, RsPin, D4Pin, D5Pin, D6Pin, D7Pin);

void setup(){
	Serial.begin(9600);
	digitalWrite(13, HIGH);
	lcd.begin (16, 2);
	lcd.setBacklightPin(backlightPin, POSITIVE);
	lcd.setBacklight(LOW);
	lcd.home ();

	lcd.setCursor (0, 0);
	//lcd.print("1234567890123456");
	lcd.print("Mode: None");
	lcd.setCursor (0, 1);
	lcd.print("Key Code: ");
}

void lcdWrite(char key){
	if(key == '*'){
		if(timeSet == false){
			timeSet = true;
			lcd.setCursor (6, 0);
			lcd.print("          ");
			lcd.setCursor (6, 0);
			lcd.print("Time Set");
		}
		else{
			timeSet = false;
			lcd.setCursor (6, 0);
			lcd.print("          ");
			lcd.setCursor (6, 0);
			lcd.print("None");
		}
	}
	else{
		if(keyPos > 15){
			lcd.setCursor (10, 1);
			lcd.print("      ");
			keyPos = 10;
		}
		lcd.setCursor (keyPos, 1);
		lcd.print(key);
		keyPos++;
	}
}

void pinPut(){
	raw = analogRead(analogPin);
	exitNow = false;
	for(int i = 0; exitNow == false; i++){
		if(raw < 10){
			exitNow = true;
			lastPushed = 'none';
		}
		if(i<17){
			if(values[i] <= raw && raw <values[i+1]){
				if(lastPushed != keys[i]){
					lcdWrite(keys[i]);
					lastPushed = keys[i];
				}
			}
		}
		else{
			exitNow = true;
		}
	}
	delay(50);
}

void loop(){
	pinPut();
}
