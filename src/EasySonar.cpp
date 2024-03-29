// Ultrasonic - Library for HR-SC04 Ultrasonic Ranging Module.
// GitHub: https://github.com/JRodrigoTech/Ultrasonic-HC-SR04
// #### LICENSE ####
// This code is licensed under Creative Commons Share alike 
// and Attribution by J.Rodrigo ( http://www.jrodrigo.net ).

#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "EasySonar.h"

EasySonar::EasySonar()
{}
   
EasySonar::EasySonar(int TP, int EP)
{
   pinMode(TP,OUTPUT);
   pinMode(EP,INPUT);
   Trig_pin=TP;
   Echo_pin=EP;
   Time_out=18000;  // 3000 µs = 50cm // 30000 µs = 5 m 
}

EasySonar::EasySonar(int TP, int EP, long TO)
{
   pinMode(TP,OUTPUT);
   pinMode(EP,INPUT);
   Trig_pin=TP;
   Echo_pin=EP;
   Time_out=TO;
}
void EasySonar::begin(int TP,int EP,long TO)
{
  
   Trig_pin=TP;
   Echo_pin=EP;
   Time_out=TO;
}
long EasySonar::Timing()
{
   pinMode(Trig_pin,OUTPUT);
   pinMode(Echo_pin,INPUT);
  digitalWrite(Trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig_pin, LOW);
  duration = pulseIn(Echo_pin,HIGH,Time_out);
  if ( duration == 0 ) duration = Time_out;

  return duration;
}

float EasySonar::Ranging(int sys)
{
  Timing();
  if (sys) {
	distance_cm = duration /29.41 / 2 ;
	return distance_cm;
  } else {
	distance_inc = duration / 74.70 / 2;
	return distance_inc; }
}
