#include <Servo.h>

Servo lightMotor;

boolean triggeredA = false;
boolean triggeredB = false;

int sensorPinA = 12;
int sensorPowerA = 11;

int sensorPinB = 10;
int sensorPowerB = 9;

int lightMotorPin = 13;

int angle;

void setup(){
	lightMotor.attach(lightMotorPin);
	Serial.begin(9600);

	pinMode(sensorPinA, INPUT);
	pinMode(sensorPowerA, OUTPUT);
	digitalWrite(sensorPowerA, HIGH);

	delay(5000);
	//you can take this out if you want, but it helps make sure the
	//sensors don't output bad data for the first few seconds

	Serial.print("Rex is Running!");
}

void turnOn(){
	tempTime = millis();
	while(angle < 130){
		if (millis() > (tempTime + 50)){
			lightMotor.write(angle);
			tempTime = millis();
			angle = angle + 1;
		}
	}
}

void turnOff(){
	tempTime = millis();
	while(angle > 50){
		if (millis() > (tempTime + 20)){
			lightMotor.write(angle);
			tempTime = millis();
			angle = angle - 1;
		}
	}
}

void loop(){
	if(digitalRead(sensorPinA) == HIGH){
		if(!triggeredA){
			turnOn();
			triggeredA = true;
			Serial.print("Start Trigger A: ");
			Serial.println(millis()/1000);
		}
	}

	if(digitalRead(sensorPinA) == LOW){
		if(triggeredA){
			turnOff();
			triggeredA = false;
			Serial.print("End Trigger A: ");
			Serial.println(millis()/1000);
		}
	}

	if(digitalRead(sensorPinB) == HIGH){
		if(!triggeredB){
			turnOn();
			triggeredB = true;
			Serial.print("Start Trigger B: ");
			Serial.println(millis()/1000);
		}
	}

	if(digitalRead(sensorPinB) == LOW){
		if(triggered){
			turnOff();
			triggeredB = false;
			Serial.print("End Trigger B: ");
			Serial.println(millis()/1000);
		}
	}
}
