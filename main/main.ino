/*
 Sonar sensor
 VCC to 5v 
 GND to GND
 SIG to PIN 12
 LEFT LED to PIN 10
 RIGHT LED to PIN 11
 */

#define led1 10
#define led2 11
#define sig 12

void setup() {
  Serial.begin (9600);
  pinMode(sig, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

unsigned long ping() {
  long duration, distance;

  pinMode(sig, OUTPUT);     // Switch signalpin to output
  digitalWrite(sig, LOW);   // Send low pulse 
  delayMicroseconds(2);     // Wait for 2 microseconds
  digitalWrite(sig, HIGH);  // Send high pulse
  delayMicroseconds(5);     // Wait for 5 microseconds
  digitalWrite(sig, LOW);   // Holdoff
  pinMode(sig, INPUT);      // Switch signalpin to input
  digitalWrite(sig, HIGH);  // Turn on pullup resistor
  
  duration = pulseIn(sig, HIGH);  // Listen for echo
  distance = (duration/58.138);   // convert to CM
  
  return distance;
}

void loop(){
  int distance = 0;
  distance = ping();

  if (distance < 4) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
  } else {
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
  }
  if (distance >= 200 || distance <= 0){
    Serial.println("Out of range");
  } else {
    Serial.print(distance);
    Serial.println(" cm");
  }
  delay(500);
}

