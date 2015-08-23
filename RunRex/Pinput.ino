int analogPin = 0;
int raw = 0;
float vOut = 0;

void setup()
{
	Serial.begin(9600);
	digitalWrite(13, HIGH);
}

void loop()
{
	raw = analogRead(analogPin);
	if(64<=raw<=68){
		Serial.println("*");
	}
	else if(69<=raw<74){
		Serial.println("7");
	}
	else if(75<=raw<79){
		Serial.println("4");
	}
	else if(80<=raw<88){
		Serial.println("1");
	}
	//everything above was for the first column, which had to pass through a 10kohm resistor
	delay(1000);
}
