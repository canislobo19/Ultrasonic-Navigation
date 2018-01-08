//left sensor does staircase detection
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10,11); // RX, TX

//CONNECT 11 TO DIN PIN OF XBEE

#define trigPin1 A1 // for front sensor
#define echoPin1 A0
#define trigPin2 A3 //for RIGHT sensor
#define echoPin2 A2
#define trigPin3 A5 //for floor detection
#define echoPin3 A4
#define switch_mode 8
#define vibrator1 3 //front sensor
#define vibrator2 5 //left sensor
#define vibrator3 6 //relative staircase deteciton
#define low_battery_buzzer A6
#define low_battery_reader A7

int toggle_switch;

//initialize vibration strength
const int smallvibration=175; //weaker vibration means obstacle is further away
const int bigvibration=250;

//setting distances in centimeters
const int lower_limit=3;
const int middle_limit=40;
const int upper_limit=60;

long duration, distance, FrontSensor, LeftSensor, StairSensor,temp;
void setup()
{ Serial.begin(9600);
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
toggle_switch = digitalRead(switch_mode); //checks if user wants to hear the speakers or vibration discs
  
SonarSensor(trigPin1, echoPin1); //record distances
FrontSensor = distance;

SonarSensor(trigPin2, echoPin2);
LeftSensor = distance;

SonarSensor(trigPin3, echoPin3);
StairSensor = distance;

temp=StairSensor-FrontSensor;

if(toggle_switch == LOW)
  {
    if(FrontSensor>lower_limit && FrontSensor<middle_limit)
    {analogWrite(vibrator1,bigvibration);}
    
    else if (FrontSensor>=middle_limit && FrontSensor<=upper_limit)
    {analogWrite(vibrator1,smallvibration);}
    
    else
    {analogWrite(vibrator1,0);}
    

    if(LeftSensor>lower_limit && LeftSensor<middle_limit)
    {analogWrite(vibrator2,bigvibration);}
    
    else if (LeftSensor>=middle_limit && LeftSensor<upper_limit)
    {analogWrite(vibrator2,smallvibration);}
    
    else
    {analogWrite(vibrator2,0);}


    if (temp>10 && temp<40)
    {analogWrite(vibrator3,smallvibration);}
    
    else
    {analogWrite(vibrator3,0);}
  }

else if (toggle_switch == HIGH)
  {
    if (temp>4 && temp<50 && FrontSensor<1500 && StairSensor<1500)
    {
        mySerial.print(5);
        delay(10);
    }
    
    else if (FrontSensor>lower_limit && FrontSensor<upper_limit)
      {
        mySerial.print(1); 
        delay(10);
      }


    if (LeftSensor>lower_limit && LeftSensor<upper_limit)
      {
        mySerial.print(4);
        delay(10);
      }
  }

Serial.print(FrontSensor); //print distance
Serial.print("-");
Serial.print(LeftSensor);
Serial.print("-");
Serial.print(StairSensor);
Serial.print("-");
Serial.println(temp);
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
  delay(30);
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

