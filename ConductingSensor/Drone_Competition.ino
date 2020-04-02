/* 
 * Author: vahid Behtaji 
 * Description : If drone's probe touch sensor  Y_ledPin (Yellow Led) and BU_ledPin (Buzzer) 
 * switch on. If stay there more than 3sec B_ledPin (Blue Led ) switch on for 1 minute and 
 * Y_ledPin and BU_ledPin switch off. 
 * 
 * 
 */



const int sensorPin   = A5;     // select the input pin for the potentiometer
const int Y_ledPin    =  4;     // the number of the LED pin  relay NO4
const int BU_ledPin   =  5;     // the number of the LED pin  relay NO3
const int B_ledPin    =  6;     // the number of the LED pin relay NO2
const unsigned long event_1 = 2000;
const unsigned long event_2 = 60000;
unsigned long previousTime = 0;
int sensorValue = 0;            // variable to store the value coming from the sensor
int state = 0;
unsigned long currentTime = millis();

void setup() {
  // declare the ledPin and buzzerPin as an OUTPUT:
  pinMode(Y_ledPin,   OUTPUT);
  pinMode(BU_ledPin,  OUTPUT);
  pinMode(B_ledPin,   OUTPUT);
  pinMode (sensorPin, INPUT_PULLUP);
}
void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
  switch(state){
    case 0:
      digitalWrite(Y_ledPin,  LOW);
      digitalWrite(BU_ledPin, LOW);
      digitalWrite(B_ledPin,  LOW);
      if(sensorValue < 100 ) {
        state = 1;
        previousTime = millis();       
      }
      break;
    case 1:
      digitalWrite(Y_ledPin,  HIGH);
      digitalWrite(BU_ledPin, HIGH);
      digitalWrite(B_ledPin,  LOW);
      if(sensorValue > 100 ) {
        state = 0;
        break;       
      }
      currentTime = millis();
      if(currentTime -previousTime >=event_1 ) {
        state = 2;
        previousTime = millis();                     
      }
      break;
    case 2:
      digitalWrite(B_ledPin,  HIGH);
      digitalWrite(Y_ledPin,  LOW);
      digitalWrite(BU_ledPin, LOW);
      currentTime = millis();
      if(currentTime -previousTime >=event_2 ) {
        state = 0;
      }
      break;

     default:
        // turn all the LEDs off:
        digitalWrite(B_ledPin,  LOW);
        digitalWrite(Y_ledPin,  LOW);
        digitalWrite(BU_ledPin, LOW);

  }
}
