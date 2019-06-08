#include "NegendoSounds.h"

NegendoSounds::NegendoSounds(int _pinBuzzer): Buzzer_pin(_pinBuzzer)
{}


void NegendoSounds::setPin(int pin) {
Buzzer_pin = pin;
}

void NegendoSounds::_tone(float noteFrequency, long noteDuration, int silentDuration)
{
	if(silentDuration==0)
		silentDuration = 1;
	TimerFreeTone(Buzzer_pin, noteFrequency, noteDuration,10);
	delay(noteDuration);
	delay(silentDuration);
}
/*
void NegendoSounds::generateNote(float noteFrequency)
{
	
	tone(Buzzer_pin, noteFrequency);
	
}*/
void NegendoSounds::_playNote(float noteFrequency, long noteDuration)
{
	TimerFreeTone(Buzzer_pin, noteFrequency, noteDuration,10);
	int pauseBetweenNotes = noteDuration * 1.30;
	delay(pauseBetweenNotes);
//	noTone(Buzzer_pin);
}
void NegendoSounds::bendTones(float initFrequency, float finalFrequency, float prop, long noteDuration, int silentDuration)
{
	if(silentDuration==0)
		silentDuration = 1;
	if(initFrequency < finalFrequency)
	{
		for(int i=initFrequency; i<finalFrequency; i=i*prop)
		{
			_tone(i, noteDuration,silentDuration);
		}
	}
	else
	{
		for(int i=initFrequency; i>finalFrequency; i=i/prop)
		{
			_tone(i, noteDuration, silentDuration);
		}
	}
}
void NegendoSounds::sing(int songName)
{
	switch(songName)
	{
		case Connection:
			_tone(note_E5,50,30);
			_tone(note_E6,55,25);
			_tone(note_A6,60,10);
			break;
		case Disconnection:
			_tone(note_E5,50,30);
			_tone(note_A6,55,25);
			_tone(note_E6,50,10);
			break;
		case ButtonPushed:
			bendTones (note_E6, note_G6, 1.03, 20, 2);
			delay(30);
			bendTones (note_E6, note_D7, 1.04, 10, 2);
			break;
		case Mode1:
			bendTones (note_E6, note_A6, 1.02, 30, 10);  //1318.51 to 1760
			break;
		case Mode2:
			bendTones (note_G6, note_D7, 1.03, 30, 10);  //1567.98 to 2349.32
			break;
		case Mode3:
			_tone(note_E6,50,100); //D6
			_tone(note_G6,50,80);  //E6
			_tone(note_D7,300,0);  //G6
			break;
		case Surprise:
			bendTones(800, 2150, 1.02, 10, 1);
			bendTones(2149, 800, 1.03, 7, 1);
			break;
		case OhOoh:
			bendTones(880, 2000, 1.04, 8, 3); //A5 = 880
			delay(200);
			for (int i=880; i<2000; i=i*1.04)
			{
				_tone(note_B5,5,10);
			}
			break;
		case OhOoh2:
			bendTones(1880, 3000, 1.03, 8, 3);
			delay(200);
			for (int i=1880; i<3000; i=i*1.03)
			{
				_tone(note_C6,10,10);
			}
			break;
		case Cuddly:
			bendTones(700, 900, 1.03, 16, 4);
			bendTones(899, 650, 1.01, 18, 7);
			break;
		case Sleeping:
			bendTones(100, 500, 1.04, 10, 10);
			bendTones(2499, 1500, 1.05, 25, 8);
			break;
		case Happy:
			bendTones(1500, 2500, 1.05, 20, 8);
			bendTones(2499, 1500, 1.05, 25, 8);
			break;
		case SuperHappy:
			bendTones(2000, 6000, 1.05, 8, 3);
			delay(50);
			bendTones(5999, 2000, 1.05, 13, 2);
			break;
		case Happy_short:
			bendTones(1500, 2000, 1.05, 15, 8);
			delay(100);
			bendTones(1900, 2500, 1.05, 10, 8);
			break;
		case Sad:
			bendTones(880, 669, 1.02, 20, 200);
			break;
		case Confused:
			bendTones(1000, 1700, 1.03, 8, 2); 
			bendTones(1699, 500, 1.04, 8, 3);
			bendTones(1000, 1700, 1.05, 9, 10);
			break;
		case Fart1:
			bendTones(1600, 3000, 1.02, 2, 15);
			break;
		case Fart2:
			bendTones(2000, 6000, 1.02, 2, 20);
			break;
		case Fart3:
			bendTones(1600, 4000, 1.02, 2, 20);
			bendTones(4000, 3000, 1.02, 2, 20);
			break;
	}
}