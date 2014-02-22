#ifndef _MIDI_H
#define _MIDI_H

#define SYSEX_BEGIN 240
#define SYSEX_END 247
//if you and this with a byte and you get anything non-zero, it is a status message

#define STATUSMASK 128
//if you and this with a status message that contains channel info, you'll get the channel

#define CC 176
#define NOTE_ON 144
#define NOTE_OFF 128
#define AFTERTOUCH 160
#define PITCHBEND 224
#define PROGCHANGE 192
#define CHANPRESSURE 208

//midi realtime
#define CLOCK 248
#define TICK 249
#define START 250
#define CONTINUE 251
#define STOP 252
#define ACTIVESENSE 254
#define RESET 255

#define TC_QUATERFRAME 241
#define SONGPOSITION 242
#define SONGSELECT 243
#define TUNEREQUEST 246

//This ID is for educational or development use only
#define SYSEX_EDUMANUFID 125 

//drum sounds
#define Acoustic_Bass_Drum 35
#define Bass_Drum1 36
#define Side_Stick 37
#define Acoustic_Snare 38
#define Hand_Clap 39
#define Electric_Snare 40	
#define Low_Floor_Tom 41
#define Closed_HiHat 42
#define High_Floor_Tom 43
#define Pedal_HiHat 44
#define Low_Tom 45
#define Open_HiHat 46	
#define Low_Mid_Tom 47
#define Hi_Mid_Tom 48
#define Crash_Cymbal1 49
#define High_Tom 50
#define Ride_Cymbal1 51 
#define Chinese_Cymbal 52
#define Ride_Bell 53
#define Tambourine 54
#define Splash_Cymbal 55
#define Cowbell 56
#define Crash_Cymbal2 57
#define Vibraslap 58
#define Ride_Cymbal2 59
#define Hi_Bongo 60
#define Low_Bongo 61
#define Mute_Hi_Conga 62
#define Open_Hi_Conga 63
#define Low_Conga 64
#define High_Timbale 65
#define Low_Timbale 66
#define High_Agogo 67
#define Low_Agogo 68
#define Cabasa 69
#define Maracas 70
#define Short_Whistle 71
#define Long_Whistle 72
#define Short_Guiro 73
#define Long_Guiro 74
#define Claves 75
#define Hi_Wood_Block 76
#define Low_Wood_Block 77
#define Mute_Cuica 78
#define Open_Cuica 79
#define Mute_Triangle 80
#define Open_Triangle 81

unsigned static int Status, Note, Velocity;

volatile unsigned static int Channel = 0; //init channel1 by default

void noteOn(int MYNOTE, int MYCHAN, int MYVEL)
{	
	Channel = MYCHAN; 
	
	Status = ((NOTE_ON) | (Channel));
	Note = MYNOTE;
	Velocity = MYVEL; 
	
	UART_Transmit(Status); 
	UART_Transmit(Note); 
	UART_Transmit(Velocity);	
}

void noteOff(int MYNOTE, int MYCHAN, int MYVEL)
{	
	Channel = MYCHAN; 
	
	Status = ((NOTE_OFF) | (Channel));
	Note = MYNOTE;
	Velocity = MYVEL; 
	
	UART_Transmit(Status); 
	UART_Transmit(Note); 
	UART_Transmit(Velocity);
}

#endif