/*
  Ultrasonic Sensor HC-SR04 and Arduino Tutorial

  by Dejan Nedelkovski,
  www.HowToMechatronics.com

*/
// defines pins numbers
const int trigPin = 0;
const int echoPin = 1;
int lowest = 71;
int highest = 150;
// defines variables
long duration;
int distance;
void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
}


long previousMillis = millis();
long currentMillis = millis();
int averageX = 0;
int averageY = 0;
int averageZ = 0;
int count = 1;
boolean pastTriggerBuffer = true;
boolean stutterOn = false;
void loop() {
  // Clears the trigPin

  ////////////////////  ////////////////////
  // ultrasound related code 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  //Serial.print("Touch cap : ");
  ////////////////////  ////////////////////

  ////////////////////  ////////////////////
  // Look for Cap Touch
  int capTouchVal1 = touchRead(23);
  int capTouchVal2 = touchRead(23);
  int mappedValue = map(distance, lowest, highest, 0, 127);

  currentMillis = millis();


  // Keeping this in here for now
  if (currentMillis - previousMillis > 600) {
    pastTriggerBuffer = true;

  }
  int capTouchVal2 = touchRead(24);


  //Modulate Speed
  if (capTouchVal2 > 6100) {
    usbMIDI.sendControlChange(3, mappedValue, 1);
    Serial.println("Turning on modulat for track 1 ");

  } else {



  }


  if (capTouchVal1 > 6100 && pastTriggerBuffer) {
    Serial.println(touchRead(23));
    // Start Stutter for Track 1
    usbMIDI.sendControlChange(2, 1, 1);
    usbMIDI.sendControlChange(2, 2, 1);

    stutterOn = true;

    pastTriggerBuffer = false;
    previousMillis = millis();
  }

  if (distance < 90) {
    //usbMIDI.sendNoteOn(distance-50, 127, 1);
    // Turn on Modulat for Track 1
    usbMIDI.sendControlChange(3, mappedValue, 1);
    Serial.println("Turning on modulat for track 1 ");


  }


  if (distance < 160) {
    // Change Pitch Shift on Quadvox
    int mappedValue = map(distance, lowest, highest, 0, 127);
    //usbMIDI.sendNoteOn(distance-50, 127, 1);
    usbMIDI.sendControlChange(1, mappedValue, 1);


  }



  delay(100);
}
