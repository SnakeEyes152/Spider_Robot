//  --------                 --------
// |  D9    |               |  D7    |
// | joint9 |               | joint7 |
//  ----- --------     --------- -----
//       |  D8    |   |  D6    |
//       | joint8 |   | joint6 |
//        --------     --------
//       |  D2    |  |   D4    |
//       | joint2 |  |  joint4 |
//  ----- --------    --------- -----
// |  D3    |               |  D5    |
// | joint3 |               | joint5 |
//  --------                 --------
//                Front


#include <Servo.h>
//#include <SoftwareSerial.h>
//#include <NeoSWSerial.h>
//#include <AltSoftSerial.h>

// deklaracja serwa
Servo joint2;      // right front hip
Servo joint3;      // right front leg
Servo joint4;      // left front hip
Servo joint5;      // left front leg
Servo joint6;      // left back hip
Servo joint7;      // left rear leg
Servo joint8;      // right back hip
Servo joint9;      // right rear leg
Servo neck_servo;  // neck

float Duration = 0;
float Distance = 0;
int angle = 90;
int sum = 0;

int a = 90;
// home position
int home_joint2 = 85;
int home_joint3 = 80;
int home_joint4 = 75;
int home_joint5 = 95;
int home_joint6 = a;
int home_joint7 = a;
int home_joint8 = a;
int home_joint9 = a;

//stand position
int stand_joint2 = 110;
int stand_joint3 = 30;
int stand_joint4 = 45;
int stand_joint5 = 150;
int stand_joint6 = 150;
int stand_joint7 = 40;
int stand_joint8 = 30;
int stand_joint9 = 140;

int slow = 500;
int normal = 300;  //pelny ruch serwa
int fast = 200;
int plaid = 100;

int mode = 0;
int runf = 1;
int forward = 2;
int backward = 3;

#define neck_servoPin 11
#define trigPin 4
#define echoPin 5
#define REDPIN
#define GREENPIN 6
#define BLUEPIN
#define lightPin A0

//#define JOYPIN 29
#define sensorX A4
#define sensorY A5

#define TxD 1
#define RxD 0
//SoftwareSerial BT(RxD, TxD);  // RX, TX for Bluetooth
char bt;
//String bt = "";

void setup() {

  bt = 'S';
  //BT.begin(9600);      // For Bluetooth
  Serial.begin(9600);  // For the IDE monitor Tools -> Serial Monitor

  Serial.println("JDd");
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  //pinMode(REDPIN, OUTPUT);
  //pinMode(BLUEPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);

  joint2.attach(2);
  joint3.attach(3);
  joint4.attach(7);
  joint5.attach(8);
  joint6.attach(9);
  joint7.attach(10);
  joint8.attach(12);
  joint9.attach(13);

  neck_servo.attach(neck_servoPin, 500, 2400);
  neck_servo.write(95);

  joint2.write(home_joint2);
  joint3.write(home_joint3);
  joint4.write(home_joint4);
  joint5.write(home_joint5);
  joint6.write(home_joint6);
  joint7.write(home_joint7);
  joint8.write(home_joint8);
  joint9.write(home_joint9);

  delay(2000);

  //show();
  //delay(1000);
}

void show() {
  Serial.println("JDDD");
  //light();

  standhome();
  delay(500);

  standhome2();
  delay(500);

  sithome();
  delay(1000);

  stand1();
  delay(1000);

  neckrotate();
  delay(1000);

  twist();
  delay(1000);

  stand2();
  delay(1000);

  stand3();
  delay(1000);

  downaction(4);
  delay(1000);

  wink(4);
  delay(1000);

  standhome2();
  delay(500);

  runforward(5);
  delay(500);

  forwardjumps(5);
  delay(500);

  forwardjumps2(5);
  delay(500);

  jumpforward();
  delay(500);

  backward2(5);
  delay(500);

  standhome2();
  delay(500);
}

void loop() {

  //sensor();
  joystick();

  delay(2000);
}

void rgb(int red, int green, int blue) {
  //analogWrite(REDPIN, red);
  analogWrite(GREENPIN, green);
  //analogWrite(BLUEPIN, blue);
  Serial.println("led");
}

void light() {

  int value = 0;
  //int value2=0;

  value = analogRead(lightPin);                        //Reads the Value of LDR(light).
  Serial.println((String) "LDR value is : " + value);  //Prints the value of LDR to Serial Monitor.
  //Serial.println("Digital output:");
  //Serial.println(value2);

  //2 lampki +monitor 600
  //swiatlo gorne 300
  //zakryty rekami 800
  //latarka <100

  if (value > 700) {
    //rgb(255, 255, 255);
  } else {
    // rgb(0, 0, 0);
  }
}

void joystick() {

  int value = 0;
  int valueX = 0;
  int valueY = 0;

  valueX = analogRead(sensorX);
  valueY = analogRead(sensorY);
  //value = digitalRead(JOYPIN);

  if (value == 0) {
    Serial.println(" ");
    Serial.print("X:");
    Serial.print(valueX, DEC);
    Serial.print(" | Y:");
    Serial.print(valueY, DEC);
    Serial.print(" | Przycisk: ");
    Serial.println(value, DEC);
    Serial.println(" ");
  }

  int xstate = valueX;
  int ystate = valueY;
  int xystate = 0;

  xstate = valueX >= 900 ? 2 : (valueX <= 200 ? 0 : 1);
  ystate = valueY >= 900 ? 2 : (valueY <= 200 ? 0 : 1);
  xystate = 3 * xstate + ystate;

  switch (xystate) {
    case 1:  //up (pins)
      forward2(2);
      break;
    case 0:  //right up
      runforward(2);
      break;
    case 3:  //right
      rightturn(3);
      break;
    case 6:  //right down
      standhome();
      break;
    case 7:  //down
      backward2(2);
      break;
    case 8:  //left down
      sithome();
      break;
    case 5:  //left
      leftturn(3);
      break;
    case 2:  //left up
      wink(2);
      break;
    case 4:  //center
      standhome2();
      break;
  }
}

void bluetooth() {

  Serial.println("Magnus");

  //bt = "";

  if (Serial.available() > 0) {
    bt = Serial.read();
  } else if (bt == 'O') {
    rgb(0, 255, 0);  //dioda swieci
    Serial.print(bt);
    delay(75);
  } else if (bt == 'D') {
    rgb(0, 0, 0);  //dioda sie wylacza
    Serial.print(bt);
    delay(75);
  } else if (bt == 'u') {
    standhome2();  //robot wstaje
    Serial.print(bt);
    delay(75);
  } else if (bt == 's') {
    sithome();
    Serial.print(bt);
    delay(75);
  } else if (bt == 'f') {
    forward2(2);
    Serial.print(bt);
    delay(75);
  } else if (bt == 'b') {
    backward2(2);
    Serial.print(bt);
    delay(75);
  } else if (bt == 'r') {
    runforward(2);
    Serial.print(bt);
    delay(75);
  } else {
    Serial.println("else");
  }

  delay(1000);
}

//lay default
void standhome() {
  joint2.write(home_joint2);
  joint3.write(home_joint3);
  joint4.write(home_joint4);
  joint5.write(home_joint5);
  joint6.write(home_joint6);
  joint7.write(home_joint7);
  joint8.write(home_joint8);
  joint9.write(home_joint9);
  Serial.println("Stand home");
}

//stand on arms extended
void standhome2() {
  joint2.write(stand_joint2);
  joint3.write(stand_joint3);
  joint4.write(stand_joint4);
  joint5.write(stand_joint5);
  joint6.write(stand_joint6);
  joint7.write(stand_joint7);
  joint8.write(stand_joint8);
  joint9.write(stand_joint9);
  Serial.println("Stand home2");
}

//stretch arms and touch ground
void sithome() {
  joint2.write(135);
  joint3.write(65);
  joint4.write(45);
  joint5.write(110);
  joint6.write(135);
  joint7.write(80);
  joint8.write(45);
  joint9.write(110);
  Serial.println("Sit home");
}

int scan() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  Duration = pulseIn(echoPin, HIGH);
  Serial.println(Duration);
  return Duration;
}

int scanleft() {
  int i = 170;
  int left = 0;
  int sumleft = 0;
  while (i >= 120) {
    neck_servo.write(i);
    i = i - 2;
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    Duration = pulseIn(echoPin, HIGH);
    int Distance = Duration * 340 * 100 / 2 / 1000000;
    Serial.println(Distance);

    if (Distance < 10) {
      left = 1;
      sumleft++;
    } else {
      left = 0;
    }
    delay(10);
  }
  return sumleft;
}

int scanright() {
  int i = 10;
  int right = 0;
  int sumright = 0;
  while (i <= 60) {
    neck_servo.write(i);
    i = i + 2;
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    Duration = pulseIn(echoPin, HIGH);
    int Distance = Duration * 340 * 100 / 2 / 1000000;
    Serial.println(Distance);

    if (Distance < 10) {
      right = 1;
      sumright++;
    } else {
      right = 0;
    }
    delay(10);
  }
  return sumright;
}

void sensor() {

  Serial.println("Sensor");
  // ultrasonic sensor
  scan();
  if (Duration > 0) {
    int Distance = Duration * 340 * 100 / 2 / 1000000;
    Serial.println(Distance);

    if (Distance < 15) {
      //rgb(255, 0, 0);
      int right = 0;
      int left = 0;
      int sumright = 0;
      int sumleft = 0;
      delay(10);
      scanleft();
      delay(10);
      scanright();
      delay(10);
      neck_servo.write(95);
      delay(10);

      if (sumright > sumleft) {
        leftturn(3);
        Serial.println("Turning left");
      } else {
        rightturn(3);
        Serial.println("Turning right");
      }

      if (sumright >= 20) {
        backward2(2);
        leftturn(3);
        Serial.println("Retreating left");
      } else if (sumleft >= 20) {
        backward2(2);
        rightturn(3);
        Serial.println("Retreating right");
      }
    } else if (Distance > 35) {
      //rgb(0, 255, 0);
      Serial.println("Advancing fast");
      runforward(3);
    } else {
      //rgb(223, 255, 0);
      Serial.println("Advancing carefully");
      forward2(1);
    }
  }
  delay(10);
}
void forward2(unsigned int step) {
  int velocity = normal;
  if (mode != forward) {
    joint2.write(stand_joint2);
    joint3.write(stand_joint3);
    joint4.write(stand_joint4);
    joint5.write(stand_joint5);
    joint6.write(stand_joint6);
    joint7.write(stand_joint7);
    joint8.write(stand_joint8);
    joint9.write(stand_joint9);
    delay(500);
  }
  while (step-- > 0) {

    joint3.write(stand_joint3 + 70);  //prawa noga przód do góry
    joint7.write(stand_joint7 + 70);  //lewa noga tył do góry
    delay(velocity);
    joint2.write(stand_joint2 + 30);  //prawa noga przód do przodu
    joint6.write(stand_joint6 - 70);  //lewa noga tył do przodu
    delay(velocity);
    joint3.write(stand_joint3);  //opuszczenie nogi
    joint7.write(stand_joint7);
    delay(normal);
    joint5.write(stand_joint5 - 70);  //lewa noga przód do góry
    joint9.write(stand_joint9 - 55);  //prawa noga tył do góry
    delay(velocity);
    joint8.write(stand_joint8 + 70);  //prawa noga tył do przodu
    joint4.write(stand_joint4 - 45);  //lewa noga przód do przodu
    delay(velocity);
    joint5.write(stand_joint5);  //opuszczenie nogi
    joint9.write(stand_joint9);
    delay(400);
    joint2.write(stand_joint2 - 50);  //przesunięcie prawej przedniej nogi do tyłu
    joint6.write(stand_joint6);       //powrót
    joint8.write(stand_joint8);
    joint4.write(stand_joint4 + 30);  //przesunięcie lewej przedniej nogi do tyłu
    delay(600);
  }
  Serial.println("Forward");
  mode = forward;
}

// retreat (several steps)
void backward2(unsigned int step) {
  if (mode != backward) {
    joint2.write(stand_joint2);
    joint3.write(stand_joint3);
    joint4.write(stand_joint4);
    joint5.write(stand_joint5);
    joint6.write(stand_joint6);
    joint7.write(stand_joint7);
    joint8.write(stand_joint8);
    joint9.write(stand_joint9);
    delay(500);
  }
  while (step-- > 0) {
    joint3.write(stand_joint3 + 70);
    joint7.write(stand_joint7 + 70);
    delay(100);
    joint2.write(stand_joint2 - 50);
    joint6.write(stand_joint6 + 70);
    delay(100);
    joint3.write(stand_joint3);
    joint7.write(stand_joint7);
    delay(300);

    joint5.write(stand_joint5 - 70);
    joint9.write(stand_joint9 - 55);
    delay(100);
    joint8.write(stand_joint8 - 70);
    joint4.write(stand_joint4 + 45);
    delay(100);
    joint5.write(stand_joint5);
    joint9.write(stand_joint9);
    delay(300);

    joint2.write(stand_joint2 + 50);
    joint6.write(stand_joint6 - 30);
    joint8.write(stand_joint8 + 30);
    joint4.write(stand_joint4 - 30);
    delay(600);
  }
  mode = backward;
  Serial.println("Backwards");
}

void runforward(unsigned int step) {
  int velocity = fast;
  if (mode != runf) {
    joint2.write(home_joint2);
    joint4.write(home_joint4);
    joint6.write(home_joint6);
    joint8.write(home_joint8);
    joint3.write(stand_joint3);  //prawa noga przód do dołu
    joint5.write(stand_joint5);  //lewa noga przód do dołu
    joint7.write(stand_joint7);  //lewa noga tył do dołu
    joint9.write(stand_joint9);  //prawa noga tył do dołu
    delay(300);
  }
  while (step-- > 0) {
    joint3.write(stand_joint3 + 70);  //prawa noga przód do góry
    joint7.write(stand_joint7 + 70);  //lewa noga tył do góry

    joint2.write(home_joint2 + 50);  //prawa noga przód do przodu
    joint6.write(home_joint6);       //lewa noga tył do przodu

    joint4.write(home_joint4 + 10);  //lewa noga przód do tyłu
    joint8.write(home_joint8 - 60);  //prawa noga tył do tyłu
    delay(velocity + 50);

    joint3.write(stand_joint3);  //prawa noga przód do dołu
    joint7.write(stand_joint7);  //lewa noga tył do dołu
    delay(velocity);

    joint5.write(stand_joint5 - 70);  //lewa noga przód do góry
    joint9.write(stand_joint9 - 55);  //prawa noga tył do góry

    joint4.write(home_joint4 - 55);  //lewa noga przód do przodu
    joint8.write(home_joint8);       //prawa noga tył do przodu

    joint2.write(home_joint2 - 10);  //prawa noga przód do tyłu
    joint6.write(home_joint6 + 60);  //lewa noga tył do tyłu
    delay(velocity + 50);

    joint5.write(stand_joint5);  //lewa noga przód do dołu
    joint9.write(stand_joint9);  //prawa noga tył do dołu
    delay(velocity);
  }
  mode = runf;
  /*
    joint2.write(home_joint2);
    joint4.write(home_joint4);
    joint6.write(home_joint6);
    joint8.write(home_joint8);
    joint3.write(stand_joint3); //prawa noga przód do dołu
    joint5.write(stand_joint5); //lewa noga przód do dołu
    joint7.write(stand_joint7); //lewa noga tył do dołu
    joint9.write(stand_joint9); //prawa noga tył do dołu
    delay(300); */
}

// clockwise
void rightturn(unsigned int step) {
  int velocity = fast;
  joint2.write(stand_joint2);
  joint3.write(stand_joint3);
  joint4.write(stand_joint4);
  joint5.write(stand_joint5);
  joint6.write(stand_joint6);
  joint7.write(stand_joint7);
  joint8.write(stand_joint8);
  joint9.write(stand_joint9);
  while (step-- > 0) {
    joint5.write(stand_joint5 - 70);  //lewa noga przód do góry
    joint9.write(stand_joint9 - 55);  //prawa noga tył do góry
    delay(velocity);
    joint4.write(home_joint4 - 65);  //lewa noga przód do przodu
    joint8.write(home_joint8 - 70);  //prawa noga tył do tyłu
    delay(velocity);
    joint5.write(stand_joint5);  //opuszczenie nogi
    joint9.write(stand_joint9);
    delay(normal);
    joint3.write(stand_joint3 + 70);  //prawa noga przód do góry
    joint7.write(stand_joint7 + 70);  //lewa noga tył do góry
    delay(velocity);
    joint2.write(home_joint2 - 20);  //prawa noga przód do tyłu
    joint6.write(home_joint6);       //lewa noga tył do przodu
    delay(velocity);
    joint3.write(stand_joint3);  //opuszczenie nogi
    joint7.write(stand_joint7);
    delay(normal);
    joint2.write(stand_joint2);
    joint3.write(stand_joint3);
    joint4.write(stand_joint4);
    joint5.write(stand_joint5);
    joint6.write(stand_joint6);
    joint7.write(stand_joint7);
    joint8.write(stand_joint8);
    joint9.write(stand_joint9);
  }
  joint2.write(stand_joint2);
  joint3.write(stand_joint3);
  joint4.write(stand_joint4);
  joint5.write(stand_joint5);
  joint6.write(stand_joint6);
  joint7.write(stand_joint7);
  joint8.write(stand_joint8);
  joint9.write(stand_joint9);
}

// counter clockwise
void leftturn(unsigned int step) {
  int velocity = fast;
  joint2.write(stand_joint2);
  joint3.write(stand_joint3);
  joint4.write(stand_joint4);
  joint5.write(stand_joint5);
  joint6.write(stand_joint6);
  joint7.write(stand_joint7);
  joint8.write(stand_joint8);
  joint9.write(stand_joint9);
  while (step-- > 0) {
    joint3.write(stand_joint3 + 70);  //prawa noga przód do góry
    joint7.write(stand_joint7 + 70);  //lewa noga tył do góry
    delay(velocity);
    joint2.write(home_joint2 + 50);  //prawa noga przód do przodu
    joint6.write(home_joint6 + 60);  //lewa noga tył do tyłu
    delay(velocity);
    joint3.write(stand_joint3);  //opuszczenie nogi
    joint7.write(stand_joint7);
    delay(normal);
    joint5.write(stand_joint5 - 70);  //lewa noga przód do góry
    joint9.write(stand_joint9 - 55);  //prawa noga tył do góry
    delay(velocity);
    joint4.write(home_joint4 + 10);  //lewa noga przód do tyłu
    joint8.write(home_joint8);       //prawa noga tył do przodu
    delay(velocity);
    joint5.write(stand_joint5);  //opuszczenie nogi
    joint9.write(stand_joint9);
    delay(normal);
    joint2.write(stand_joint2);
    joint3.write(stand_joint3);
    joint4.write(stand_joint4);
    joint5.write(stand_joint5);
    joint6.write(stand_joint6);
    joint7.write(stand_joint7);
    joint8.write(stand_joint8);
    joint9.write(stand_joint9);
  }
  joint2.write(stand_joint2);
  joint3.write(stand_joint3);
  joint4.write(stand_joint4);
  joint5.write(stand_joint5);
  joint6.write(stand_joint6);
  joint7.write(stand_joint7);
  joint8.write(stand_joint8);
  joint9.write(stand_joint9);
}

void forwardjumps(unsigned int step) {
  int velocity = normal;
  joint2.write(home_joint2);
  joint4.write(home_joint4);
  joint6.write(home_joint6);
  joint8.write(home_joint8);
  delay(300);

  while (step-- > 0) {

    joint2.write(home_joint2 - 40);  //prawa noga przód do tyłu
    joint4.write(home_joint4 + 45);  //lewa noga przód do tyłu
    joint6.write(home_joint6 + 40);  //lewa noga tył do tyłu
    joint8.write(home_joint8 - 40);  //prawa noga tył do tyłu
    delay(velocity);

    joint3.write(stand_joint3 + 70);  //prawa noga przód do góry
    joint5.write(stand_joint5 - 70);  //lewa noga przód do góry
    joint7.write(stand_joint7 + 70);  //lewa noga tył do góry
    joint9.write(stand_joint9 - 55);  //prawa noga tył do góry

    joint2.write(home_joint2 + 50);  //prawa noga przód do przodu
    joint4.write(home_joint4 - 55);  //lewa noga przód do przodu
    joint6.write(home_joint6 - 40);  //lewa noga tył do przodu
    joint8.write(home_joint8 + 40);  //prawa noga tył do przodu
    delay(velocity);

    joint3.write(stand_joint3);  //prawa noga przód do dołu
    joint5.write(stand_joint5);  //lewa noga przód do dołu
    joint7.write(stand_joint7);  //lewa noga tył do dołu
    joint9.write(stand_joint9);  //prawa noga tył do dołu

    joint2.write(home_joint2 - 30);  //prawa noga przód do tyłu
    joint4.write(home_joint4 + 35);  //lewa noga przód do tyłu
    joint6.write(home_joint6 + 30);  //lewa noga tył do tyłu
    joint8.write(home_joint8 - 30);  //prawa noga tył do tyłu
  }
  joint2.write(home_joint2);
  joint4.write(home_joint4);
  joint6.write(home_joint6);
  joint8.write(home_joint8);
  delay(300);
}

void forwardjumps2(unsigned int step) {
  int velocity = normal;
  joint2.write(home_joint2);
  joint4.write(home_joint4);
  joint6.write(home_joint6);
  joint8.write(home_joint8);
  delay(300);

  while (step-- > 0) {

    joint3.write(stand_joint3 + 70);  //prawa noga przód do góry
    joint5.write(stand_joint5 - 70);  //lewa noga przód do góry
    joint2.write(home_joint2 + 60);   //prawa noga przód do przodu
    joint4.write(home_joint4 - 65);   //lewa noga przód do przodu
    delay(velocity);
    joint3.write(stand_joint3);      //prawa noga przód do dołu
    joint5.write(stand_joint5);      //lewa noga przód do dołu
    joint7.write(stand_joint7);      //lewa noga tył do dołu
    joint9.write(stand_joint9);      //prawa noga tył do dołu
    joint6.write(home_joint6 + 70);  //lewa noga tył do tyłu
    joint8.write(home_joint8 - 70);  //prawa noga tył do tyłu
    delay(velocity);
    joint7.write(stand_joint7 + 70);  //lewa noga tył do góry
    joint9.write(stand_joint9 - 55);  //prawa noga tył do góry
    joint6.write(home_joint6 - 10);   //lewa noga tył do przodu
    joint8.write(home_joint8 + 10);   //prawa noga tył do przodu
    delay(velocity);
    joint7.write(stand_joint7);      //lewa noga przód do dołu
    joint9.write(stand_joint9);      //prawa noga tył do dołu
    joint3.write(stand_joint3);      //prawa noga przód do dołu
    joint5.write(stand_joint5);      //lewa noga przód do dołu
    joint2.write(home_joint2 - 10);  //prawa noga przód do tyłu
    joint4.write(home_joint4 + 15);  //lewa noga przód do tyłu
    delay(velocity);
  }
  joint3.write(stand_joint3);  //prawa noga przód do dołu
  joint5.write(stand_joint5);  //lewa noga przód do dołu
  joint7.write(stand_joint7);  //lewa noga przód do dołu
  joint9.write(stand_joint9);  //prawa noga tył do dołu
  joint2.write(home_joint2);
  joint4.write(home_joint4);
  joint6.write(home_joint6);
  joint8.write(home_joint8);
  delay(300);
}


void jumpforward() {

  joint2.write(stand_joint2 + 30);  //prawa noga przód do przodu
  joint6.write(stand_joint6 - 70);  //lewa noga tył do przodu
  joint8.write(stand_joint8 + 60);  //prawa noga tył do przodu
  joint4.write(stand_joint4 - 35);  //lewa noga przód do przodu
  delay(300);

  joint2.write(50);
  joint4.write(90);
  delay(300);

  joint6.write(stand_joint6 + 30);
  joint8.write(stand_joint8 - 30);
  joint4.write(stand_joint4 - 45);
  joint2.write(stand_joint2 + 40);

  joint3.write(stand_joint3 + 70);  //prawa noga przód do góry
  joint5.write(stand_joint5 - 70);  //lewa noga przód do góry

  delay(300);  //minimalna wartość??

  joint3.write(stand_joint3);
  joint5.write(stand_joint5);
  joint6.write(stand_joint6);
  joint7.write(stand_joint7);
  joint8.write(stand_joint8);
  joint9.write(stand_joint9);
  delay(500);
}
void stand1() {
  sithome();
  joint2.write(170);
  delay(300);
  joint2.write(home_joint2);
  delay(300);
  joint4.write(10);
  delay(300);
  joint4.write(home_joint4);
  delay(300);
  joint6.write(170);
  delay(300);
  joint6.write(home_joint6);
  delay(300);
  joint8.write(10);
  delay(300);
  joint8.write(home_joint8);
  delay(300);

  joint3.write(home_joint3);
  joint5.write(home_joint5);
  joint7.write(home_joint7);
  joint9.write(home_joint9);

  Serial.println("Stand1 home");
}

void stand2() {
  sithome();
  joint2.write(175);
  joint4.write(5);
  joint6.write(175);
  joint8.write(5);
  delay(600);

  joint2.write(home_joint2);
  joint4.write(home_joint4);
  joint6.write(home_joint6);
  joint8.write(home_joint8);
  delay(600);

  joint3.write(home_joint3);
  joint5.write(home_joint5);
  joint7.write(home_joint7);
  joint9.write(home_joint9);

  Serial.println("Stand2 home");
}


void stand3() {
  sithome();
  int i;
  int j = 90;
  int k = 90;
  joint2.write(home_joint2);
  joint4.write(home_joint4);
  joint6.write(home_joint6);
  joint8.write(home_joint8);
  for (i = 90; i < 165; i++) {
    joint5.write(i);
    j = j - 1;
    joint3.write(j);
    delay(20);
  }

  for (i = 115; i < 165; i++) {
    joint9.write(i);
    k = k - 1;
    joint7.write(k);
    delay(20);
  }

  Serial.println("Stand3 home");
}

// quick ups and downs
void downaction(unsigned int step) {
  while (step-- > 0) {
    sithome();
    delay(100);
    standhome();
    delay(100);
  }
}

// wave hands
void wink(unsigned int step) {
  standhome();
  joint9.write(home_joint9 - 30);

  while (step-- > 0) {
    joint5.write(30);
    joint4.write(home_joint4 + 60);
    delay(300);
    joint4.write(home_joint4 - 60);
    delay(300);
  }
}

// move body
void twist() {
  joint3.write(home_joint3);
  joint5.write(home_joint5);
  joint7.write(home_joint7);
  joint9.write(home_joint9);

  for (int right = 90; right < 170; right++) {
    joint2.write(right);
    joint6.write(right);
    joint4.write(right - 90);
    joint8.write(right - 90);
    delay(10);
  }

  for (int right = 170; right > 90; right--) {
    joint2.write(right);
    joint6.write(right);
    joint4.write(right - 90);
    joint8.write(right - 90);
    delay(10);
  }
}



// neck move (sensor off)
void neckrotate() {
  int i = 90;
  while (i < 150) {
    neck_servo.write(i);
    i++;
    delay(5);
  }
  while (i > 30) {
    neck_servo.write(i);
    i--;
    delay(5);
  }
  while (i <= 90) {
    neck_servo.write(i);
    i++;
    delay(5);
  }

  Serial.println("Neck rotate");
}


void neck_leftrotate() {
  int i = 90;
  while (i < 150) {
    neck_servo.write(i);
    i++;
    delay(5);
  }
}


void neck_rightrotate() {
  int i = 90;
  while (i > 30) {
    neck_servo.write(i);
    i--;
    delay(5);
  }
}

void neck_home() {
  neck_servo.write(90);
  Serial.println("Neck home");
}



/*
  //advance(several steps)
  void forward(unsigned int step) {
  while (step-- > 0) {
    joint3.write(home_joint3 + 30);
    joint7.write(home_joint7 + 30);
    delay(100);
    joint2.write(home_joint2 + 30);
    joint8.write(home_joint8 - 30);
    joint4.write(home_joint4);
    joint6.write(home_joint6);
    delay(100);
    joint3.write(home_joint3);
    joint7.write(home_joint7);
    idle();

    joint5.write(home_joint5 - 30);
    joint9.write(home_joint9 - 30);
    delay(100);
    joint2.write(home_joint2);
    joint8.write(home_joint8);
    joint4.write(home_joint4 - 30);
    joint6.write(home_joint6 + 30);
    delay(100);
    joint5.write(home_joint5);
    joint9.write(home_joint9);
    idle();
  }
  }

  // retreat (several steps)
  void backward(unsigned int step) {
  while (step-- > 0) {
    joint3.write(home_joint3 + 30);
    joint7.write(home_joint7 + 30);
    delay(100);
    joint2.write(home_joint2);
    joint8.write(home_joint8);
    joint4.write(home_joint4 - 30);
    joint6.write(home_joint6 + 30);
    delay(100);
    joint3.write(home_joint3);
    joint7.write(home_joint7);
    idle();

    joint5.write(home_joint5 - 30);
    joint9.write(home_joint9 - 30);
    delay(100);
    joint2.write(home_joint2 + 30);
    joint8.write(home_joint8 - 30);
    joint4.write(home_joint4);
    joint6.write(home_joint6);
    delay(100);
    joint5.write(home_joint5);
    joint9.write(home_joint9);
    idle();
  }
  }

*/