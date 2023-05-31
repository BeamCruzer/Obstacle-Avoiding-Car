#include <Servo.h>
#include <NewPing.h>

#define frontRight1 2
#define frontRight2 3
#define frontLeft1 4
#define frontLeft2 5
#define backRight1 6
#define backRight2 7
#define backLeft1 8
#define backLeft2 9
#define TRIG_PIN A0
#define ECHO_PIN A1

#define MAX_DISTANCE 200
int distance = 100;
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);
Servo myservo;

void setup()
{
    pinMode(frontRight1, OUTPUT);
    pinMode(frontRight2, OUTPUT);
    pinMode(frontLeft1, OUTPUT);
    pinMode(frontLeft2, OUTPUT);
    pinMode(backRight1, OUTPUT);
    pinMode(backRight2, OUTPUT);
    pinMode(backLeft1, OUTPUT);
    pinMode(backLeft2, OUTPUT);
    stop();

    myservo.attach(10);
    myservo.write(125);
    delay(2000);
    distance = readPing();
    delay(100);
    distance = readPing();
    delay(100);
    distance = readPing();
    delay(100);
    distance = readPing();
    delay(100);
}

void loop()
{
    int distanceR = 0;
    int distanceL = 0;
    delay(100);

    if (distance <= 15)
    {
        stop();
        delay(100);
        backward();
        delay(300);
        stop();
        delay(200);
        distanceR = lookRight();
        delay(200);
        distanceL = lookLeft();
        delay(200);

        if (distanceR >= distanceL)
        {
            turnLeft();
            stop();
        }

        else
        {
            turnRight();
            stop();
        }
    }
    else forward();

    distance = readPing();
}

int lookRight()
{
    myservo.write(50);
    delay(500);
    int distance = readPing();
    delay(200);
    return distance;
}

int lookLeft()
{
    myservo.write(180);
    delay(1000);
    int distance = readPing();
    delay(200);
    myservo.write(125);
    delay(500);
    return distance;
}

int readPing()
{
    delay(70);
    int cm = sonar.ping_cm();
    if (cm == 0)
      cm = 250;

    return cm;
}

void stop()
{
    digitalWrite(frontRight1, LOW);     digitalWrite(frontRight2, LOW); 
    digitalWrite(frontLeft1, LOW);      digitalWrite(frontLeft2, LOW);
    digitalWrite(backRight1, LOW);      digitalWrite(backRight2, LOW); 
    digitalWrite(backLeft1, LOW);       digitalWrite(backLeft2, LOW);
}

void forward()
{
    digitalWrite(frontRight1, HIGH);    digitalWrite(frontRight2, LOW); 
    digitalWrite(frontLeft1, LOW);      digitalWrite(frontLeft2, HIGH);
    digitalWrite(backRight1, HIGH);     digitalWrite(backRight2, LOW); 
    digitalWrite(backLeft1, LOW);       digitalWrite(backLeft2, HIGH);
}

void backward()
{
    digitalWrite(frontRight1, LOW);     digitalWrite(frontRight2, HIGH); 
    digitalWrite(frontLeft1, HIGH);     digitalWrite(frontLeft2, LOW);
    digitalWrite(backRight1, LOW);      digitalWrite(backRight2, HIGH); 
    digitalWrite(backLeft1, HIGH);      digitalWrite(backLeft2, LOW);
}

void turnRight()
{
    digitalWrite(frontRight1, LOW);     digitalWrite(frontRight2, HIGH); 
    digitalWrite(frontLeft1, LOW);      digitalWrite(frontLeft2, HIGH);
    digitalWrite(backRight1, LOW);      digitalWrite(backRight2, HIGH); 
    digitalWrite(backLeft1, LOW);       digitalWrite(backLeft2, HIGH);

    delay(700);
    forward();
}

void turnLeft()
{
    digitalWrite(frontRight1, HIGH);    digitalWrite(frontRight2, LOW); 
    digitalWrite(frontLeft1, HIGH);     digitalWrite(frontLeft2, LOW);
    digitalWrite(backRight1, HIGH);     digitalWrite(backRight2, LOW); 
    digitalWrite(backLeft1, HIGH);      digitalWrite(backLeft2, LOW);

    delay(700);
    forward();
}
