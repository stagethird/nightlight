/* Night light program 
   for Arduino Uno
*/

const int LED1 = 3; // these 6 DIO pin #s are all of
const int LED2 = 5; // the PWM capable pins on the UNO
const int LED3 = 6;
const int LED4 = 9;
const int LED5 = 10;
const int LED6 = 11;
const int lightpin = A0; // light sensor pin
const int motionpin = 2; // motion sensor pin
bool isDark = false; // state of lightPin
bool hasMotion = false; // state of motionPin
int lightReading; // get lightpin state
int motionReading = LOW; // get motionpin state
unsigned long turnOnMillis; // Time at light activation
const unsigned long duration = 300000; // length of time light is on
bool groupOneOn = false; // These next 3 vars store the state
bool groupTwoOn = false; // of the 3 LED groups.
bool groupThreeOn = false; // True == ON, false == OFF.

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);
  pinMode(lightpin, INPUT);
  pinMode(motionpin, INPUT);
  for (int pinNumber = 2; pinNumber < 12; pinNumber++) {
    digitalWrite(pinNumber, LOW);
  }  
  Serial.begin(9600);
}

void loop() {
  lightReading = analogRead(lightpin);
  if (lightReading < 200) { // light threshold. Default to 200, 700 for testing
    isDark = true;
  } else {
    isDark = false;
  }
  motionReading = digitalRead(motionpin);
  if (motionReading == HIGH) {
    hasMotion = true;
  } else {
    hasMotion = false;
  }
  if (isDark == true && hasMotion == true) {
    groupOneOn = lightsOn(LED1, LED2, 20);
    groupTwoOn = lightsOn(LED3, LED4, 20);
    groupThreeOn = lightsOn(LED5, LED6, 20);
    turnOnMillis = millis();
    monitorWhileOn();
  }
}

void monitorWhileOn() {
  while (turnOnMillis + duration > millis()) {
    motionReading = digitalRead(motionpin);
    if (motionReading == HIGH) {
      turnOnMillis = millis();
      if (groupOneOn == false) groupOneOn = lightsOn(LED1, LED2, 0);
      if (groupTwoOn == false) groupTwoOn = lightsOn(LED3, LED4, 0);
      if (groupThreeOn == false) groupThreeOn = lightsOn(LED5, LED6, 0);
    }    
    if ((millis() + 20000) > (turnOnMillis + duration) && groupThreeOn == true) {
      groupThreeOn = lightsOff(LED5, LED6, 2);
    }
    if ((millis() + 10000) > (turnOnMillis + duration) && groupTwoOn == true) {
      groupTwoOn = lightsOff(LED3, LED4, 2);
    }
  }
  groupOneOn = lightsOff(LED1, LED2, 2);
}

bool lightsOn(int a, int b, int time) {
  for (int i = 0; i < 256; i++) {
    analogWrite(a, i);
    analogWrite(b, i);
    delay(time);
  }
  return true;
}

bool lightsOff(int a, int b, int time) {
  for  (int i = 255; i >= 0; i--) {
    analogWrite(a, i);
    analogWrite(b, i);
    delay(time);
  }
  return false;
}
