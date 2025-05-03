// IR sensor pins
const int irFrontLeft = 36;   // Front-left IR sensor
const int irFrontCenter = 35; // Front-center IR sensor
const int irFrontRight = 34;  // Front-right IR sensor

// Motor A (right)
const int motorPin1 = 12; // Right motor IN1
const int motorPin2 = 27; // Right motor IN2
const int ena = 25;       // Right motor PWM (enable pin for speed control)
const int gasledpin = 32;
const int gassensorpin = 23;
// Motor B (left)
const int motorPin3 = 14; // Left motor IN3
const int motorPin4 = 33; // Left motor IN4
const int enb = 26;       // Left motor PWM (enable pin for speed control)

// Motor speed settings (0-255 for PWM)
const int baseSpeed = 160;    // Base speed for forward movement
const int turnSpeed = 160;    // Speed during pivot turns
const int maxSpeed = 160;     // Maximum forward speed
const int reverseSpeed = 160; // Reverse speed
const int gasThreshold = 600;

void setup()
{
    Serial.begin(9600);        // Initialize serial communication
    randomSeed(analogRead(0)); // Seed random generator

    // Set motor pins
    pinMode(motorPin1, OUTPUT);
    pinMode(motorPin2, OUTPUT);
    pinMode(motorPin3, OUTPUT);
    pinMode(motorPin4, OUTPUT);
    pinMode(ena, OUTPUT);
    pinMode(enb, OUTPUT);

    // Set sensor pins
    pinMode(irFrontLeft, INPUT);
    pinMode(irFrontCenter, INPUT);
    pinMode(irFrontRight, INPUT);
}

void loop()
{
    int frontLeft = digitalRead(irFrontLeft);
    int frontCenter = digitalRead(irFrontCenter);
    int frontRight = digitalRead(irFrontRight);

    Serial.print("FL: ");
    Serial.print(frontLeft);
    Serial.print(" FC: ");
    Serial.print(frontCenter);
    Serial.print(" FR: ");
    Serial.println(frontRight);

    // Check gas levels
    int gasValue = digitalRead(gassensorpin);
    Serial.print("Gas Value: ");
    Serial.println(gasValue);

    if (gasValue ==1)
    {
        digitalWrite(gasledpin, HIGH); // Gas detected - turn on LED
        Serial.println("Gas threshold exceeded!");
        Serial.print("Gas Value: ");
        Serial.println(gasValue);
        stopMotors();
    }
    else
    {
        digitalWrite(gasledpin, LOW); // Safe - turn off LED
    }

    navigate(frontLeft, frontCenter, frontRight);

    delay(10); // Small delay for stability
}

void navigate(int fl, int fc, int fr)
{
    if ((fl == HIGH && fr == HIGH) || (fl == HIGH && fc == HIGH && fr == HIGH))
    {
        Serial.println("Dead end or junction detected - Moving backward");
        turnsharpRight();
        return;
    }

    if (fc == HIGH && fl == LOW && fr == LOW)
    {
        Serial.println("Moving Forward (centered)");
        moveForward(maxSpeed);
    }
    else if (fl == HIGH && fc == LOW && fr == LOW)
    {
        Serial.println("Sharp Turn Left");
        stopMotors();
        turnsharpLeft();
    }
    else if (fr == HIGH && fc == LOW && fl == LOW)
    {
        Serial.println("Sharp Turn Right");
        stopMotors();
        turnsharpRight();
    }
    else if (fc == HIGH && fl == HIGH && fr == LOW)
    {
        Serial.println("Slight Left");
        stopMotors();
        turnLeft();
    }
    else if (fc == HIGH && fl == LOW && fr == HIGH)
    {
        Serial.println("Slight Right");
        stopMotors();
        turnRight();
    }
    else if (fl == LOW && fc == LOW && fr == LOW)
    {
        Serial.println("Lost - Move Backward");
        moveForward(reverseSpeed);
    }
    else
    {
        Serial.println("Unclear State - Move Backward");
        moveForward(reverseSpeed);
    }
}

// Motor control functions
void moveForward(int speed)
{
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, HIGH);
    digitalWrite(motorPin4, LOW);
    analogWrite(ena, speed);
    analogWrite(enb, speed);
}

void moveBackward(int speed)
{
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, HIGH);
    digitalWrite(motorPin3, LOW);
    digitalWrite(motorPin4, HIGH);
    analogWrite(ena, speed);
    analogWrite(enb, speed);
}

void turnLeft()
{
    digitalWrite(motorPin1, LOW); // Right motor backward
    digitalWrite(motorPin2, HIGH);
    digitalWrite(motorPin3, HIGH); // Left motor forward
    digitalWrite(motorPin4, LOW);
    analogWrite(ena, 200);
    analogWrite(enb, 200);
}

void turnRight()
{
    digitalWrite(motorPin1, HIGH); // Right motor forward
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, LOW); // Left motor backward
    digitalWrite(motorPin4, HIGH);
    analogWrite(ena,200);
    analogWrite(enb,200);
}

void stopMotors()
{
    digitalWrite(motorPin1, LOW); // Right motor backward
    digitalWrite(motorPin2, HIGH);
    digitalWrite(motorPin3, HIGH); // Left motor forward
    digitalWrite(motorPin4, LOW);
    analogWrite(ena, 0);
    analogWrite(enb, 0);
    delay(20);
}
void turnsharpRight()
{
    digitalWrite(motorPin1, HIGH); // Right motor forward
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, LOW); // Left motor backward
    digitalWrite(motorPin4, HIGH);
    analogWrite(ena, 255);
    analogWrite(enb, 255);
}

void turnsharpLeft()
{
    digitalWrite(motorPin1, LOW); // Right motor backward
    digitalWrite(motorPin2, HIGH);
    digitalWrite(motorPin3, HIGH); // Left motor forward
    digitalWrite(motorPin4, LOW);
    analogWrite(ena, 255);
    analogWrite(enb, 255);
}