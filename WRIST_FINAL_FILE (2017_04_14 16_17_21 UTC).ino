#include <SoftwareSerial.h>

SoftwareSerial mySerial(10,11); // RX, TX
// CONNECT 10 TO DOUT OF XBEE

#define front_tune 2
#define right_tune 3
#define stair_down_tune 4
#define left_tune 5
#define stair_up_tune 6
byte value[3];

//Initialize pins
void setup() { 
  mySerial.begin(9600);
  pinMode(front_tune, OUTPUT); 
  pinMode(right_tune, OUTPUT);
  pinMode(stair_down_tune, OUTPUT); 
  pinMode(left_tune, OUTPUT);
  pinMode(stair_up_tune, OUTPUT);
}

//Depending on the input received by the bluetooth receiver, play a different message

void loop() {
  
  if (mySerial.available()>2) {
    for (int i=0; i<3; i++) 
      value[i]=mySerial.read();
  
  if (value[2]==49){
  digitalWrite(front_tune, HIGH); //Plays message to inform user
  delay(50);
  digitalWrite(front_tune, LOW);
  }

  else if (value[2]==50){
  digitalWrite(right_tune, HIGH); //Plays message to inform user
  delay(50);
  digitalWrite(right_tune, LOW);
  }

  else if (value[2]==51){
  digitalWrite(stair_down_tune, HIGH); //Plays message to inform user
  delay(50);
  digitalWrite(stair_down_tune, LOW);
  }

    else if (value[2]==52){
  digitalWrite(left_tune, HIGH); //Plays message to inform user
  delay(50);
  digitalWrite(left_tune, LOW);
  }

    else if (value[2]==53){
  digitalWrite(stair_up_tune, HIGH); //Plays message to inform user
  delay(50);
  digitalWrite(stair_up_tune, LOW);
  }
  
  }
}
