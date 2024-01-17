#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

Servo myservo;  // create servo object to control a servo

LiquidCrystal_I2C lcd(0x27, 16, 2); 

 int leftf1=13;
 int leftf2=12;
 int rightf1=10;
 int rightf2=11;
 const int trigPin = 8;
 const int echoPin = 9;
 long duration;
 int distanceCm, distanceInch;
 const int buzzer_Pin = 7;
 const int green_led = 6;
 const int red_led = 5;
 const int temp_pin = A0;
 float temperature;
 char face_status = 0;
  int pos = 0;    // variable to store the servo position
 int max=15;
 int min = 10;
 boolean goesForward= false;



void setup() {
  Serial.begin(9600);  
  lcd.init();         // initialize the LCD
  lcd.backlight();
  myservo.attach(3);  // attaches the servo on pin 9 to the servo object
   pinMode(buzzer_Pin, OUTPUT);
   pinMode(red_led, OUTPUT);
   pinMode(green_led, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
    pinMode(leftf1, OUTPUT);
    pinMode(leftf2, OUTPUT);
    pinMode(rightf1, OUTPUT);
    pinMode(rightf2, OUTPUT);
  
  lcd.clear();                      // clear the LCD
   lcd.setCursor (3, 0);             // Set the cursor to 1st line
  lcd.print("Face Mask");
  lcd.setCursor(0,2);
  lcd.print(" Detection");
  delay(2000); 
  myservo.write(30);
  delay(2000);
 
}
 
 void moveForward(){

  if(!goesForward){

    goesForward=true;
    
  digitalWrite(leftf1, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(leftf2, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(rightf1, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(rightf2, LOW);   // turn the LED on (HIGH is the voltage level)
  }
}
void moveBackward(){

  goesForward=false;

  digitalWrite(leftf1, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(leftf2, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(rightf1, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(rightf2, HIGH);   // turn the LED on (HIGH is the voltage level)
  
}
void moveStop(){
  
  digitalWrite(leftf1, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(leftf2, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(rightf1, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(rightf2, LOW);   // turn the LED on (HIGH is the voltage level)
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * 0.034 / 2;
 
   if((distanceCm> 10)&&(distanceCm< 15)){
   moveStop();
    delay(500);
  digitalWrite(red_led, LOW); 
  digitalWrite(buzzer_Pin, LOW);
  digitalWrite(green_led, LOW); 
  lcd.clear();
  lcd.print("Scan Your face");
  delay(100);
  while (Serial.available() > 0)
  {
     face_status = Serial.read();
    
    if(face_status == 'a')
    { 
      lcd.clear();
      delay(100);
      lcd.print("Masked Detected");
      lcd.clear();
      delay(100);
      lcd.print("Read Temperature");
      delay(1000);
  
     temperature = analogRead(temp_pin);
     temperature= ( temperature/1024.0)*5000; 
     temperature = temperature/10;
     lcd.print("Temperature value = ");
     lcd.println(temperature);
     lcd.clear();
     delay(100);
     lcd.print("Temperature = ");
     lcd.setCursor(0,1);
     lcd.print(temperature);
     delay(1000);
     if(temperature > 40)
     {
       lcd.clear();
       delay(100);
       lcd.print("Body Temperature High");
       lcd.setCursor(0,2);
       lcd.print("Gate Closed");   
       delay(1000);
      digitalWrite(buzzer_Pin, HIGH);
      digitalWrite(red_led, HIGH); 
      digitalWrite(green_led, LOW);
       delay(1000);
       digitalWrite(buzzer_Pin, LOW);
    }
    else
    {
      lcd.clear();
      delay(100);
      lcd.print("Gate Open"); 
      delay(1000);
     digitalWrite(buzzer_Pin, LOW); 
     digitalWrite(green_led, HIGH);
     digitalWrite(red_led, LOW); 
      delay(1000);
      myservo.write(120); 
      delay(1000);
      myservo.write(30);
      delay(100);
   }
    }
  else if(face_status == 'b')
  {
     lcd.clear();
     delay(100);
     lcd.print("Mask is not");
     lcd.setCursor(0,1);
     lcd.print("detected");   
     delay(1000);
     digitalWrite(buzzer_Pin, HIGH);
    digitalWrite(red_led, HIGH); 
    digitalWrite(green_led, LOW);
     delay(1000);
    digitalWrite(buzzer_Pin, LOW);
  }else{  }
  
  }
  
  }else {
    
      
       
       if(distanceCm>max){
       
      moveForward();
       
      //  delay(2000);   
   
 }
 
    
    if(distanceCm<min){
      moveBackward();
  }
  }

    
}


void forward()
{
   
  digitalWrite(leftf1,LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(leftf2, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(rightf1, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(rightf2, LOW);   // turn the LED on (HIGH is the voltage level)    // wait for a second
     // lcd.print("Forward");
  }
  void reverse()
  {
   
  digitalWrite(leftf1, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(leftf2, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(rightf1, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(rightf2, HIGH);   // turn the LED on (HIGH is the voltage level)
     //lcd.print("Backword");
    }



