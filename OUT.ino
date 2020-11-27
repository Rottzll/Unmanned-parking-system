#include <Servo.h>

int sensing;
int out_sen = A0;
int out_flag = A1;

int servopin = 3;
Servo my_ser;
int angle = 0;

void setup() {
  Serial.begin(9600);
  pinMode(out_sen, INPUT);
  pinMode(out_flag, OUTPUT);
  my_ser.attach(servopin);
  my_ser.write(angle);
}

void loop() {
  do {
    sensing = digitalRead(out_sen);
  } while (sensing == HIGH);

    digitalWrite(out_flag, LOW);
    delay(5);
    digitalWrite(out_flag, HIGH);

    for (angle = 0; angle < 90; angle++)
    {
      my_ser.write(angle);
      delay(10);
    }
    
    for (int temp = 0; temp < 200; temp++)
    {
      delay(5);
    }

    for (angle = 90; angle > 0; angle--)
    {
      my_ser.write(angle);
      delay(15);
    }
}
