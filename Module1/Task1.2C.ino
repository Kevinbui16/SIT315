//pin connected to the output of the motion sensor
const int pirSensorPin = 2;  
//trig pin of the ultrasonic sensor
const int trigPin = 11; 
//echo pin of the ultrasonic sensor
const int echoPin = 10;
//pin connected to the LED for the motion sensor
const int pirLedPin = 13;       
//pin connected to the LED for the ultrasonic sensor
const int ultrasonicLedPin = 12; 

//volatile variable to track motion and object detection
volatile bool motionDetected = false;  
volatile bool objectDetected = false;  

void setup() {
  //initialize serial communication at 9600 bits per second
  Serial.begin(9600);

  //set sensor pins as input
  pinMode(pirSensorPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  //set LED pins as output
  pinMode(pirLedPin, OUTPUT);
  pinMode(ultrasonicLedPin, OUTPUT);

  //attach interrupts to the sensor pins
  attachInterrupt(digitalPinToInterrupt(pirSensorPin), motionISR, CHANGE);

  //start with the LEDs turned off
  digitalWrite(pirLedPin, LOW);
  digitalWrite(ultrasonicLedPin, LOW);
}

//interrupt service routine (ISR) for motion detection
void motionISR() {
  //read the motion sensor value 
  //update the motionDetected variable
  motionDetected = digitalRead(pirSensorPin);
}

void loop() {
  //measure distance with the ultrasonic sensor
  long duration, distance;
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration / 58.2; 

  //print the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  //check if an object is detected within a certain distance
  if (distance < 50 && distance > 0) {
    objectDetected = true;
  } else {
    objectDetected = false;
  }

  // Check if an object is detected
  if (objectDetected) {
    //if object detected, turn on the LED for the object
    digitalWrite(ultrasonicLedPin, HIGH);
    Serial.println("Object Detected: LED ON");
  } else {
    //if no object detected, turn off the LED for the object
    digitalWrite(ultrasonicLedPin, LOW);
    Serial.println("No Object: LED OFF");
  }

  //check if motion is detected
  if (motionDetected) {
    //if motion detected, turn on the LED for motion
    digitalWrite(pirLedPin, HIGH);
    Serial.println("Motion Detected: LED ON");
  } else {
    //if no motion detected, turn off the LED for motion
    digitalWrite(pirLedPin, LOW);
    Serial.println("No Motion: LED OFF");
  }

  //add a small delay to avoid flooding the serial output
  delay(500);
}


