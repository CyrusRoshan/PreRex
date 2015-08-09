#include <Servo.h>

Servo lightMotor;

boolean triggeredA = false;
boolean triggeredB = false;

boolean waitForA = false;
boolean waitForB = false;
int waitTimeA = 0;
int waitTimeB = 0;

boolean rewaitingA = false;
boolean rewaitingB = false;

int bodyCount = 0;
int errorBodyCount = 0;

int triggerTimeout = 2000;
//after triggering one sensor then waiting this many ms,
//triggering the next sensor won't change body count,
//but will be shown as an error

int sensorPinA = 12;
int sensorPowerA = 11;

int sensorPinB = 10;
int sensorPowerB = 9;

int lightMotorPin = 13;

int angle;

int tempTime;

void setup(){
	lightMotor.attach(lightMotorPin);
	Serial.begin(9600);

	pinMode(sensorPinA, INPUT);
	pinMode(sensorPowerA, OUTPUT);
	digitalWrite(sensorPowerA, HIGH);

	pinMode(sensorPinB, INPUT);
	pinMode(sensorPowerB, OUTPUT);
	digitalWrite(sensorPowerB, HIGH);

	Serial.println("");
	Serial.println("Rex is awake...");

	delay(5000);
	//you can take this out if you want, but it helps make sure the
	//sensors don't output bad data for the first few seconds

	Serial.println("Rex is Running!");
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
			triggeredA = true;
			rewaitingA = false;
			Serial.print("Start Trigger A: ");
			Serial.println(millis()/1000);
		}
	}
	if(digitalRead(sensorPinA) == LOW){
		if(triggeredA){
			triggeredA = false;
			Serial.print("End Trigger A: ");
			Serial.println(millis()/1000);
		}
	}
	if(triggeredA && !triggeredB && !rewaitingB){
		waitForB = true;
		waitTimeB = millis() + triggerTimeout;
	}


	if(digitalRead(sensorPinB) == HIGH){
		if(!triggeredB){
			triggeredB = true;
			rewaitingB = false;
			Serial.print("Start Trigger B: ");
			Serial.println(millis()/1000);
		}
	}
	if(digitalRead(sensorPinB) == LOW){
		if(triggeredB){
			triggeredB = false;
			Serial.print("End Trigger B: ");
			Serial.println(millis()/1000);
		}
	}
	if(triggeredB && !triggeredA && !rewaitingA){
		waitForA = true;
		waitTimeB = millis() + triggerTimeout;
	}


	if(waitForB && (millis() > waitTimeB) && (waitTimeB != 0)){
		waitForB = false;
		rewaitingB = false;
		errorBodyCount ++;
		Serial.print("ErrorBodyCount: ");
		Serial.println(errorBodyCount);
	}
	if(waitForB && triggeredB){
		waitForB = false;
		rewaitingB = true;
		if(millis() < waitTimeB){
			bodyCount ++;
			Serial.print("bodyCount: ");
			Serial.println(bodyCount);
		}
	}
	if(waitForA && (millis() > waitTimeA) && (waitTimeA != 0)){
		waitForA = false;
		rewaitingA = false;
		errorBodyCount ++;
		Serial.print("vars: ");
		Serial.println(waitForA);
		Serial.println(waitForB);
		Serial.println(triggeredA);
		Serial.println(triggeredB);
		Serial.println(millis());
		Serial.println(waitTimeB);
		Serial.print("ErrorBodyCount: ");
		Serial.println(errorBodyCount);
	}
	if(waitForA && triggeredA){
		waitForA = false;
		rewaitingA = true;
		if(millis() < waitTimeA){
			bodyCount --;
			Serial.print("bodyCount: ");
			Serial.println(bodyCount);
		}
	}
	//the bodyCount calculations assume that passing through A
	//then passing through B means that another person
	//has entered the room
}
