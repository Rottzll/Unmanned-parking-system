#include <Servo.h>
#include <SoftwareSerial.h>

SoftwareSerial BTSerial(2, 3);
byte buffer[1024];
int bufferPosition;

int count = 4;
int sensing;
int in_sen = A0;
int out_sen = A1;

int fin[] = {8, 7, 6, 9};
int num[10][4] = {
  {0, 0, 0, 0}, /*0*/
  {0, 0, 0, 1}, /*1*/
  {0, 0, 1, 0}, /*2*/
  {0, 0, 1, 1}, /*3*/
  {0, 1, 0, 0}, /*4*/
  {0, 1, 0, 1}, /*5*/
  {0, 1, 1, 0}, /*6*/
  {0, 1, 1, 1}, /*7*/
  {1, 0, 0, 0}, /*8*/
  {1, 0, 0, 1}, /*9*/
};

int digit_1 = 4;
int digit_10 = 5;

int servopin = A4;
Servo my_servo;
int angle = 0;

void setup() {
  pinMode(in_sen, INPUT);
  pinMode(out_sen, INPUT);
  pinMode(digit_1, OUTPUT);
  pinMode(digit_10, OUTPUT);
  my_servo.attach(servopin);
  my_servo.write(angle);
  BTSerial.begin(9600);
  Serial.begin(9600);
  for (int i = 0; i < 4; i++) {
    pinMode(fin[i], OUTPUT);
  }
}

void display_count(int number) {
  int temp = number % 10;
  for (int i = 0; i < 4; i++)
  {
    digitalWrite(fin[i], num[temp][i]);
    digitalWrite(digit_1, LOW);
    digitalWrite(digit_1, HIGH);
  }
  temp = number / 10;
  for (int i = 0; i < 4; i++)
  {
    digitalWrite(fin[i], num[temp][i]);
    digitalWrite(digit_10, LOW);
    digitalWrite(digit_10, HIGH);
  }
}

void check() {
  if (digitalRead(out_sen) == LOW) {
    count += 1;
    if (count >= 4)
    {
      count = 4;
    }
    display_count(count);
    BTSerial.print("state sit : ");
    BTSerial.println(count);
    while (digitalRead(out_sen) == LOW);
  }
}

void loop() {
  BTSerial.print("state sit : ");
  BTSerial.println(count);
  Serial.println(count);
  display_count(count);
  do {
    sensing = digitalRead(in_sen);
    check();

  } while (sensing == HIGH);

  if (count == 0) {
    angle = 0;
  }
  else
  {
    count -= 1;
    display_count(count);
    for (angle = 0; angle < 93; angle++)
    {
      my_servo.write(angle);
      delay(10);
      check();
    }
    for (int temp = 0; temp < 200; temp++)
    {
      delay(5);
      check();
    }
    for (angle = 93; angle > 0; angle--)
    {
      my_servo.write(angle);
      delay(15);
      check();
    }
    if (count <= 0) {
      count = 0;
    }
  }
}
