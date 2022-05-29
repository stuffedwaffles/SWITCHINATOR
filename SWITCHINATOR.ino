#include <Wire.h>
#include <DS3231.h>
//rtc gives time, servo moves to turn light switch on and off at 8 am

DS3231 clock;
RTCDateTime dt;
#include <Servo.h>
Servo myservo;
//light on- servo angle closer to 0
//light off - servo angle closer to 180

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);//serial setup for reference

  Serial.println("Initialize RTC module");
  // Initialize DS3231
  clock.begin();
  //clock.setDateTime(2022, 4, 17, 12, 12, 00);
  // Send sketch compiling time to Arduino
  clock.setDateTime(__DATE__, __TIME__);    
  myservo.attach(4);//pin
  myservo.write(90);// move servo to center position -> 90°
}

void loop() {
  // put your main code here, to run repeatedly:
  dt = clock.getDateTime();//time
  Serial.println(String(dt.hour) + " " + String(dt.minute) + " " + String(dt.second)); //print it in serial for reference
  if (dt.hour==7){
    if (dt.minute==59){
      if (dt.second==00){//if time is 7:59:00 (early just in case time is off)  
        myservo.write(0);
        delay(500);
        myservo.write(180);
        delay(500);
        myservo.write(0);
        delay(500);
        myservo.write(180);
        delay(500);
        myservo.write(90);// move servo to turn light on, off, on, off, and back to center
        }
      }
    }
  delay(1000);
}
