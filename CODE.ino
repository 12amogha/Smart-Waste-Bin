#include<Servo.h>
Servo Myservo_wet;
Servo Myservo_dry;
int pos;
int WET= 3; 
int DRY= 2;  
int Sensor= 0; // Soil Sensor input at Analog PIN A0
int value= 0;
const int trigPin1 = 5;
const int echoPin1 = 6;
//const int trigPin2 = 6;
//const int echoPin2 = 7;
// defines variables
long duration1;
//long duration2;
int distance1;
//int distance2;
const int buzzer1 = 9; //buzzer to arduino pin 9
//const int buzzer2 = 10; //buzzer to arduino pin 10


void setup() {
   Serial.begin(9600);
   Myservo_wet.attach(3);
   Myservo_dry.attach(4);
   pinMode(WET, OUTPUT);
   pinMode(DRY, OUTPUT);
   delay(2000);
   //pinMode (3, OUTPUT) ;
pinMode (trigPin1, OUTPUT) ; // Sets the trigPin as an Output
pinMode (echoPin1, INPUT) ; // Sets the echoPin as an Input
//pinMode (trigPin2, OUTPUT) ; // Sets the trigPin as an Output
//pinMode (echoPin2, INPUT) ; // Sets the echoPin as an Input
Serial. begin (9600); // Starts the serial communication
pinMode(buzzer1, OUTPUT); // Set buzzer - pin 9 as an output
//pinMode(buzzer2, OUTPUT); // Set buzzer - pin 9 as an output
}

void loop() {
  // Clears the trigPin
digitalWrite (trigPin1, LOW) ;
//digitalWrite (trigPin2, LOW) ;
delayMicroseconds (2000);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite (trigPin1, HIGH) ;
//digitalWrite (trigPin2, HIGH) ;
delayMicroseconds (2000) ;
digitalWrite (trigPin1, LOW) ;
//digitalWrite (trigPin2, LOW) ;
// Reads the echoPin, returns the sound wave travel time in microseconds

duration1 = pulseIn (echoPin1, HIGH) ;
//duration2 = pulseIn (echoPin1, HIGH) ;
//duration1 = pulseIn (echoPin2, HIGH) ;
//duration2 = pulseIn (echoPin2, HIGH) ;
// Calculating the distance
distance1= duration1*0.034/2;
//distance2= duration2*0.034/2;
// Prints the distance on the Serial Monitor
Serial . print ("Distance: ") ;
Serial. println(distance1) ;
//Serial. println(distance2) ;
if (distance1<5 && duration1>5)
{
  tone(buzzer1, 900); // Send 1KHz sound signal...
//  noTone(buzzer2);
  delay(1000);        // ...for 1 sec
digitalWrite (3, HIGH);
}
//else if(distance2<5 && duration2>10)
//{
  // noTone(buzzer1);     // Stop sound...
  //  tone(buzzer2, 900);
  //delay(1000);        // ...for 1sec
  //digitalWrite (3, LOW) ;
//}
else
{
  noTone(buzzer1);     // Stop sound...
//  noTone(buzzer2);     // Stop sound...
   Serial.print("MOISTURE LEVEL : ");
   value= analogRead(Sensor);
   value= value/10;
   Serial.println(value);
   if(value>0)
   {
      digitalWrite(WET, HIGH);
   }
   else
   {
      digitalWrite(DRY,HIGH);
   }
   delay(15);
   digitalWrite(WET,LOW);
   digitalWrite(DRY, LOW);
   if(value<50) //threshold for wet
   {
   for(pos=0;pos<=720;pos++){
   Myservo_wet.write(pos);
   delay(15);
   }
   delay(15);
   for(pos=780;pos>=0;pos--){
   Myservo_wet.write(pos);
   delay(15);
   }
   delay(15); 
   }
   if(value>100) //threshold for dry
   {
   for(pos=0;pos<=720;pos++){
   Myservo_dry.write(pos);
   delay(15);
   }
   delay(15);
   for(pos=720;pos>=0;pos--){
   Myservo_dry.write(pos);
   delay(15);
   }
   delay(15); 
   }
}
}
