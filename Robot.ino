#include <NewPing.h>
#include <Servo.h>

#define enA 10    // Enable1 L298 Pin enA
#define in1 9     // Motor1 L298 Pin in1
#define in2 8     // Motor1 L298 Pin in1
#define in3 7     // Motor2 L298 Pin in1
#define in4 6     // Motor2 L298 Pin in1
#define enB 5     // Enable2 L298 Pin enB
#define echo A2   // Echo pin
#define trigger A3  // Trigger pin
#define myservoPin A5

Servo myservo;  // Create a servo object

int Set = 20;
int distanceL, distance_F, distanceR;
bool goesForward = false;

void setup() {
  Serial.begin(9600);
  pinMode(echo, INPUT);
  pinMode(trigger, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enB, OUTPUT);
  analogWrite(enA, 100); // Write The Duty Cycle 0 to 255 Enable Pin A for Motor1 Speed
  analogWrite(enB, 100); // Write The Duty Cycle 0 to 255 Enable Pin B for Motor2 Speed
  myservo.attach(myservoPin);  // Attach servo to the specified pin
  myservo.write(115);
  delay(2000);
  distance_F = Ultrasonic_read();
  delay(100);
  distance_F = Ultrasonic_read();
  delay(100);
  distance_F = Ultrasonic_read();
  delay(100);
  distance_F = Ultrasonic_read();
  delay(100);
}

void loop() {
  delay(40);
  if(distance_F > Set) {
    moveForward();
  } else {
    Check_side();
  }
  distance_F = Ultrasonic_read(); // Assign value to distance_F variable
}

long Ultrasonic_read() {
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  long time = pulseIn(echo, HIGH);
  return time / 29 / 2;
}

void compareDistance() {
  if (distanceR >= distanceL) {
    turnRight();
    delay(500);
    moveForward();
    delay(600);
  } else {
    turnLeft();
    delay(500);
    moveForward();
    delay(600);
  }
}

void Check_side() {
  moveStop();
  delay(100);
  moveBackward();
  delay(200);
  moveStop();
  delay(200);
  distanceR = lookRight();
  delay(200);
  distanceL = lookLeft();
  delay(200);
  compareDistance();
}

int lookRight() {
  myservo.write(50);
  delay(500);
  int distance = Ultrasonic_read();
  delay(100);
  myservo.write(115);
  return distance;
}

int lookLeft() {
  myservo.write(170);
  delay(500);
  int distance = Ultrasonic_read();
  delay(100);
  myservo.write(115);
  return distance;
}
void turnLeft() {
  // Make both motors rotate in the forward direction
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  // Enable both motors
  digitalWrite(enA, HIGH);
  digitalWrite(enB, HIGH);
}


void turnRight() {
  // Make both motors rotate in reverse
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  // Enable both motors
  digitalWrite(enA, HIGH);
  digitalWrite(enB, HIGH);
}
  void moveBackward() {
  // Assuming you want to turn both motors right simultaneously
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  // Assuming you need to enable the motors
  digitalWrite(enA, HIGH);
  digitalWrite(enB, HIGH);
}
  void moveForward() {
  // Assuming you want to turn both motors right simultaneously
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  // Assuming you need to enable the motors
  digitalWrite(enA, HIGH);
  digitalWrite(enB, HIGH);
}

void moveStop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
