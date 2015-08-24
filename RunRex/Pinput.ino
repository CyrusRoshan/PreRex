int analogPin = 0;
int raw = 0;
float vOut = 0;

int i;
boolean exitNow;
char lastPushed;

//recorded = [66, 71, 77, 83, 213, 229, 248, 270, 298, 330, 370, 422, 490, 591, 735, 966]
int values[17] = {64, 69, 75, 80, 190, 221, 240, 260, 285, 315, 350, 396, 456, 541, 666, 850, 1050};

char keys[16] = {'*', '7', '4', '1', '0', '#', 'D', '8', '9', 'C', '5', '6', 'B', '2', '3', 'A'};

void setup(){
	Serial.begin(9600);
	digitalWrite(13, HIGH);
}

void loop(){
	raw = analogRead(analogPin);
	exitNow = false;
	i = 0;
	while(exitNow == false){
		if(raw < 10){
			exitNow = true;
			lastPushed = 'none';
		}
		if(i<17){
			if(values[i] <= raw && raw <values[i+1]){
				if(lastPushed != keys[i]){
					Serial.println(keys[i]);
					lastPushed = keys[i];
				}
			}
		}
		else{
			exitNow = true;
		}
		i++;
	}
	delay(50);
}
