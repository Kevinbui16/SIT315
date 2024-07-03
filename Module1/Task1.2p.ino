//pin connected to the motion sensor's output
const int motionSensorPin = 2;  
//pin connected to the built-in LED
const int ledPin = 13;          

//create variable to track motion detection
volatile bool motionDetected = false;  

void setup() {
  //initialize serial monitor at 9600 bits per second
  Serial.begin(9600);

  //make motion sensor pin as an input
  pinMode(motionSensorPin, INPUT);

  //make LED pin as an output
  pinMode(ledPin, OUTPUT);

  //attach interrupt to the motion sensor pin
  attachInterrupt(digitalPinToInterrupt(motionSensorPin), motionISR, CHANGE);

  //start with the LED turned off
  digitalWrite(ledPin, LOW);
}

//interrupt service routine(ISR) for motion detection
void motionISR() {
  //Read the motion sensor value
  //update the motionDetected variable
  motionDetected = digitalRead(motionSensorPin);
}


void loop() {
  //check if motion is detected
  if (motionDetected) {
    //if motion detected,turn on the LED
    digitalWrite(ledPin, HIGH);
    Serial.println("Motion detected: LED turn ON");
  } 
  else {
    // if motion not detected, turn off the LED
    digitalWrite(ledPin, LOW);
    Serial.println("No motion: LED is OFF");
  }

  //add a small delay to avoid flooding the serial output
  delay(500);
}

