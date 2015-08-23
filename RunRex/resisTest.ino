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
	Serial.print("Voltage: ");
	Serial.println(vOut);
	Serial.print("Resistance: ");
	Serial.println(raw);
	delay(1000);
}
