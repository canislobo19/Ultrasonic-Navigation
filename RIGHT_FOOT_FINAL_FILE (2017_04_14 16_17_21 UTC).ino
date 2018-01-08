//right foot does ground detection
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10,11); // RX, TX
//conenct 11 to DIN of xbee

#define trigPin1 A5 // for front sensor
#define echoPin1 A4
#define trigPin2 A3 //for RIGHT sensor
#define echoPin2 A2
#define trigPin3 A1 //for floor detection
#define echoPin3 A0
#define switch_mode 8
#define vibrator1 3 //front sensor
#define vibrator2 5 //right sensor
#define vibrator3 6 //floor detection
#define low_battery_buzzer A6
#define low_battery_reader A7

int toggle_switch;

//initialize vibration strength
const int smallvibration=175;  //weaker vibration means obstacle is further away
const int bigvibration=250;

//setting distances in centimeters
const int lower_limit=3;
const int middle_limit=50;
const int upper_limit=110;

long duration, distance, FrontSensor, RightSensor, FloorSensor;

void setup()
{
  //initialize pins
  Serial.begin(9600);
  mySerial.begin (9600);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(vibrator1, OUTPUT);
  pinMode(vibrator2, OUTPUT);
  pinMode(vibrator3, OUTPUT);
  pinMode(switch_mode,INPUT_PULLUP);
}

void loop() {
SonarSensor(trigPin1, echoPin1);  //record distances
FrontSensor = distance;

SonarSensor(trigPin2, echoPin2);
RightSensor = distance;

SonarSensor(trigPin3, echoPin3);
FloorSensor = distance;

toggle_switch = digitalRead(switch_mode); //checks if user wants to hear the speakers or vibration discs

if(toggle_switch == LOW)
  {
    if(FrontSensor>lower_limit && FrontSensor<middle_limit)
    {analogWrite(vibrator1,bigvibration);}
    
    else if (FrontSensor>middle_limit && FrontSensor<upper_limit)
    {analogWrite(vibrator1,smallvibration);}
    
    else
    {analogWrite(vibrator1,0);}


    if(RightSensor>lower_limit && RightSensor<middle_limit)
    {analogWrite(vibrator2,bigvibration);}
    
    else if (RightSensor>=middle_limit && RightSensor<upper_limit)
    {analogWrite(vibrator2,smallvibration);}
    
    else
    {analogWrite(vibrator2,0);}


    if(FloorSensor<180)
    {analogWrite(vibrator3,0);}
    
    else
    {analogWrite(vibrator3,bigvibration);}
  }


else if (toggle_switch == HIGH)
  {
    analogWrite(vibrator1,0);
    analogWrite(vibrator2,0);
    analogWrite(vibrator3,0);
    
    if (FrontSensor>lower_limit && FrontSensor<upper_limit)
      {
        mySerial.print(1); //SAYS 'FRONT'
        delay(10);
      }
         
    if (RightSensor>lower_limit && RightSensor<upper_limit)
      {
        mySerial.print(2);  //says "Right"
        delay(10);
      }

    if (FloorSensor>upper_limit)
    {
      mySerial.print(3); //says "staircase down"
      delay(10);
    }
  }

Serial.print(FrontSensor);
Serial.print("-");
Serial.print(RightSensor);
Serial.print("-");
Serial.println(FloorSensor);
}

void SonarSensor(int trigPin,int echoPin) 
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); 
  distance = (duration/2) / 29.1;
  delay(50);
}

 void printVolts()
{
  int sensorValue = analogRead(low_battery_reader); 
  float voltage = sensorValue * (5.00 / 1023.00) * 2; //convert to voltage.
  while(voltage < 7)
  {
    digitalWrite(low_battery_buzzer, HIGH);
  }
}

