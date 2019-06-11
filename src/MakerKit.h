/*
https://negendo.com

Project: Umake Kit for education
Hardware: Arduino Uno R3 + Maker shield Uno made by NEGENDO
    Sensor:
        1 - Temperature Humidity sensor - DHT11
        2 - Gas sensor - MQ-2
        3 - Touch sensor
        4 - Soil moisture sensor
        5 - Vibration sensor
        6 - Light sensor
        7 - Sound sensor
        8 - Triple axis acceleromenter sensor
        9 - Rotation potentiomenter sensor
    Module:
        1 - Microswitch
        2 - Push button
        3 - LED Light
        4 - Relay module
        5 - Module 2 motor
        6 - LCD I2C
Author: Tuan Hung
NEGENDO Education
*/

#ifndef Makerkit_H_
#define Makerkit_H_

#include "Arduino.h"
#include "stdint.h"

#include "Scratch.h"
#include "DHT.h"
#include "Servo.h"
#include "Adafruit_NeoPixel.h"
#include "IRremote.h"
#include "EasySonar.h"
#include "NegendoSounds.h"
//#define DEBUG 1
//#define DEBUG_SERIAL 1

#define M1A 3
#define M1B 5
#define M2A 6
#define M2B 11

#define leftline_pin        A0
#define rightline_pin       A2
#define centerline_pin      A1	
#define lineSensor_enable   A3

//////// define State
#define READ_SERIAL 0 
#define PARSING 1
#define WRITE_SERIAL 2

class MakerKit
{
public:
    MakerKit(){}
    void runM1(int speed);
    void runM2(int speed);
    void stopM1();
    void stopM2();
    void setMotor(int M, int speed);
    void stopMotor(int M);
    void moveForward(int speed);
    void moveBack(int speed);
    void turnRight(int speed);
    void turnLeft(int speed);
    void stop();
    void relay(int pin, int status);
    void setLED(int pin, int status);
    void setServo(int pin, int angle);
    void disableServo(int pin);
    void generateTone(int pin,int fr);
    void generateNote(int pin,int fr,int duration);
    void setPWM(int pin, int value);

    bool getDigital(int pin) {
    pinMode(pin,INPUT);
    return digitalRead(pin);
    }

    bool buttonPressed(int pin);
    bool readMicroswitch(int pin);
    int getGasSensor(int pin);
    float getTemperature(int pin);
    float getHumidity(int pin);
    bool readTouch(int pin);
    bool readVibration(int pin);
    int getSoilMoisture(int pin);
    int getSound(int pin);
    int getLight(int pin);
    int getAcceleromenterValue(int axis);
    int getPotentiomenterLocation(int pin);
    float getUSdistance(int trig,int ech);
    
    
    int leftSensor();
    int rightSensor();
    int centerSensor();
    int readIRdistance(int pin);
    void setColor(int pin, byte R, byte G, byte B);
    void setStrip(int pin,int num,int location, byte R, byte G, byte B);
    void enableIR(int receiverPin);
    unsigned long readIR();
    unsigned long readIRremote(int pin) {
        enableIR(pin);
        return readIR();
    }
    int getLineSensor(int pin);
    bool readPIR(int pin) { return digitalRead(pin);}
    //////////////////////////////////////////

    void run();
    void readSerial();
    void parseData();
    void writeSerial();

private:

    DHT DHTsensor = DHT(DHT11);
    Adafruit_NeoPixel RGB = Adafruit_NeoPixel(NEO_GRB + NEO_KHZ800);
    IRrecv irrecv;
    decode_results results;
    NegendoSounds Sound;
    EasySonar US;
    Servo servo2;
    Servo servo3;
    Servo servo4;
    Servo servo5;
    Servo servo6;
    Servo servo7;
    Servo servo8;
    Servo servo9;
    Servo servo10;
    Servo servo11;
    Servo servo12;
    bool IRenabled = false;
    unsigned long lastIRcode;
    int State = 0;
    bool first_run = true;
    bool actionDone = false;
    double timeStart;
    bool isAvailable = false;
    bool isStart=false;
    unsigned char prevc=0;
    int index = 0;
    int dataLen;
    int ind = 0;
    unsigned char buffer[32]; // reading
    unsigned char serial_buf[12]; // writing
    unsigned char serialRead;
    uint8_t command_index = 0;
    int numLed;
    int IR_pin; 

    union
    {
        byte byteVal[4];
        float floatVal;
        long longVal;
    }val;

    union
    {
        byte byteVal[8];
        double doubleVal;
    }valDouble;

    union
    {
        byte byteVal[2];
        short shortVal;
    }valShort;
    /////////////////////////////////////////
    void writeHead();
    void writeEnd();
    /////////////////////////////////////////
    unsigned char readBuffer(int index);  //read Serial Comming buffer
    void writeBuffer(int index,unsigned char c); //write to Serial Sending Buffer
    void clearBuffer(unsigned char *buf, int leng);
    /////////////////////////////////
    void callOK();
    void sendByte(char c);
    void sendString(String s);
    void sendFloat(float value);
    void sendShort(double value);
    void sendDouble(double value);
    short readShort(int idx);
    float readFloat(int idx);
    long readLong(int idx);

    void runFunction(int device);
    int searchServoPin(int pin);
    void readSensors(int device);
};
#endif