int analogPin = 0;
int raw = 0;
float vOut = 0;

int i;
boolean exit;

//recorded = [66, 71, 77, 83, 213, 229, 248, 270, 298, 330, 370, 422, 490, 591, 735, 966]
int values = [64, 69, 75, 80, 190, 221, 240, 260, 285, 315, 350, 396, 456, 541, 666, 850, 1050];

char keys = ["*", "7", "4", "1", "0", "#", "D", "8", "9", "C", "5", "6", "B", "2", "3", "A"];

void setup(){
	Serial.begin(9600);
	digitalWrite(13, HIGH);
}

void loop(){
	raw = analogRead(analogPin);
	exit = false;
	while(exit === false){
		if(i<17){
			if(values[i]<=raw<values[i+1]){
				Serial.println(keys[i]);
			}
		}
		else{
			exit = true;
		}
		i++;
	}
	delay(1000);
}
