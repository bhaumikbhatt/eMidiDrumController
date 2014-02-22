#include<avr/io.h>
#include<avr/interrupt.h>
#include"LCD_mega128.h"
#include"serial.h"
#include"midi.h"
#include"adc.h"

#define PIEZOTHRESHOLD 50
#define BOUNCE_PERIOD 20

#define CHANNEL0 Bass_Drum1
#define CHANNEL1 Acoustic_Snare
#define CHANNEL2 High_Tom
#define CHANNEL3 Low_Tom
#define CHANNEL4 Low_Floor_Tom
#define CHANNEL5 Open_HiHat
#define CHANNEL6 Ride_Cymbal1
#define CHANNEL7 Crash_Cymbal1

volatile unsigned static int adcValue0, adcValue1, adcValue2, adcValue3, adcValue4, adcValue5,adcValue6, adcValue7, HHpedal = 0;

volatile unsigned static int adcState0, adcState1, adcState2, adcState3, adcState4, adcState5,adcState6, adcState7 = 0;
 
unsigned long lastreadtime0, lastreadtime1, lastreadtime2, lastreadtime3, lastreadtime4,lastreadtime5,lastreadtime6, lastreadtime7 = 0;

volatile unsigned long ms=0;

int flag_peak = 1, last_val = 0;

int main(void)
{
	Port_Init();
	sei();
	UART_Init(MYUBRR);
	lcd_init();
	ADC_Init();
	Timer0_Init();

	while(1)
	{
	
	ADC0On();
	ADC0Off();
	
	ADC1On();
	ADC1Off();

	ADC2On();
	ADC2Off();
	
	ADC3On();
	ADC3Off();
	
	ADC4On();
	ADC4Off();
	
	ADC5On();
	ADC5Off();
	
	ADC6On();
	ADC6Off();
	
	ADC7On();
	ADC7Off();
	
	}

}

ISR(TIMER0_COMP_vect)
{
ms++;
}

unsigned long int millis(void) 
{ 
    return ms; 
} 

void Timer0_Init(void)
{
TCCR0 = 0x0F; //Init Timer0, CTC, pre-scaler = 1024
OCR0 = 0x0F; //16 clock cycles
TIMSK = 0x02; //Set OCIE0 bit
}

void Port_Init(void) 
{ 
   DDRC = 0xFF;   //    Make port C as output port 
   PORTC = 0xFF;   // Initial condition of LED OFF
   
   DDRG = 0xFE;   //    Make pinG0 as input pin 
   PORTG = 0x01;   // Pull up resistors
} 

void ADC0On(void)
{

	adcValue0 = ADC_read(0);
	
	lcd_gotoxy1(0); 
	lcd_char('B'); 
	
	if(adcValue0 >= PIEZOTHRESHOLD && adcState0 == 0)
	{
	
	while(flag_peak)
	{
    adcValue0 = ADC_read(0);

    if(last_val > adcValue0)
    flag_peak=0;
    
	last_val=adcValue0;
    }
	
	last_val = 0;
    flag_peak = 1;
	
	noteOn(CHANNEL0, 0, 127);
	PORTC = 0xFE; 
	
	lcd_gotoxy2(0); 
	lcd_char(0x5E);
	lcd_gotoxy2(12); 
	lcd_showvalue(adcValue0); 
	
	adcState0 = 1;
	
	lastreadtime0 = millis();
	
	}
	
}

void ADC0Off(void)
{
	
	adcValue0 = ADC_read(0);
	
	if(adcState0 == 1 && adcValue0 < (PIEZOTHRESHOLD/2) && (millis() - lastreadtime0) > BOUNCE_PERIOD)
	{
	PORTC = 0xFF; 
	noteOff(CHANNEL0, 0, 127);
	
	adcState0 = 0;
    }
	
}

void ADC1On(void)
{

	adcValue1 = ADC_read(1);
	
	lcd_gotoxy1(1); 
	lcd_char('S'); 
	
	if(adcValue1 >= PIEZOTHRESHOLD  && adcState1 == 0)
	{
	
	while(flag_peak)
	{
    adcValue1 = ADC_read(1);

    if(last_val > adcValue1)
    flag_peak=0;
    
	last_val=adcValue1;
    }
	
	last_val = 0;
    flag_peak = 1;
	
	noteOn(CHANNEL1, 1, 127);
	PORTC = 0xFD; 
	
	lcd_gotoxy2(1); 
	lcd_char(0x5E);
	lcd_gotoxy2(12); 
	lcd_showvalue(adcValue1); 
	
	adcState1 = 1;
	
	lastreadtime1 = millis();
	}
	
}

void ADC1Off(void)
{
	
	adcValue1 = ADC_read(1);
	
	if(adcState1 == 1 && adcValue1 < (PIEZOTHRESHOLD/2) && (millis() - lastreadtime1) > BOUNCE_PERIOD)
	{
	PORTC = 0xFF; 
	noteOff(CHANNEL1, 1, 127);
	
	adcState1 = 0;
    }
	
}

void ADC2On(void)
{

	adcValue2 = ADC_read(2);
	
	lcd_gotoxy1(2); 
	lcd_char('T'); 
	
	if(adcValue2 >= PIEZOTHRESHOLD && adcState2 == 0)
	{
	
	while(flag_peak)
	{
    adcValue2 = ADC_read(2);

    if(last_val > adcValue2)
    flag_peak=0;
    
	last_val=adcValue2;
    }
	
	last_val = 0;
    flag_peak = 1;
	
	noteOn(CHANNEL2, 2, 127);
	PORTC = 0xFB; 
	
	lcd_gotoxy2(2); 
	lcd_char(0x5E);
	lcd_gotoxy2(12); 
	lcd_showvalue(adcValue2); 
	
	adcState2 = 1;
	
	lastreadtime2 = millis();
	}
	
}

void ADC2Off(void)
{
	
	adcValue2 = ADC_read(2);
	
	if(adcState2 == 1 && adcValue2 < (PIEZOTHRESHOLD/2) && (millis() - lastreadtime2) > BOUNCE_PERIOD)
	{
	PORTC = 0xFF; 
	noteOff(CHANNEL2, 2, 127);
	
	adcState2 = 0;
    }
	
}

void ADC3On(void)
{

	adcValue3 = ADC_read(3);
	
	lcd_gotoxy1(3); 
	lcd_char('T'); 
	
	if(adcValue3 >= PIEZOTHRESHOLD && adcState3 == 0)
	{

	while(flag_peak)
	{
    adcValue3 = ADC_read(3);

    if(last_val > adcValue3)
    flag_peak=0;
    
	last_val=adcValue3;
    }
	
	last_val = 0;
    flag_peak = 1;
	
	noteOn(CHANNEL3, 3, 127);
	PORTC = 0xF7; 
	
	lcd_gotoxy2(3); 
	lcd_char(0x5E);
	lcd_gotoxy2(12); 
	lcd_showvalue(adcValue3); 
	
	adcState3 = 1;
	
	lastreadtime3 = millis();
	}
	
}

void ADC3Off(void)
{
	
	adcValue3 = ADC_read(3);
	
	if(adcState3 == 1 && adcValue3 < (PIEZOTHRESHOLD/2) && (millis() - lastreadtime3) > BOUNCE_PERIOD)
	{
	PORTC = 0xFF; 
	noteOff(CHANNEL3, 3, 127);
	
	adcState3 = 0;
    }
	
}

void ADC4On(void)
{

	adcValue4 = ADC_read(4);
	
	lcd_gotoxy1(4); 
	lcd_char('T'); 
	
	if(adcValue4 >= PIEZOTHRESHOLD  && adcState4 == 0)
	{
	
	while(flag_peak)
	{
    adcValue4 = ADC_read(4);

    if(last_val > adcValue4)
    flag_peak=0;
    
	last_val=adcValue4;
    }
	
	last_val = 0;
    flag_peak = 1;
	
	noteOn(CHANNEL4, 4, 127);
	PORTC = 0xEF; 
	
	lcd_gotoxy2(4); 
	lcd_char(0x5E);
	lcd_gotoxy2(12); 
	lcd_showvalue(adcValue4); 
	
	adcState4 = 1;
	
	lastreadtime4 = millis();
	}
	
}

void ADC4Off(void)
{
	
	adcValue4 = ADC_read(4);
	
	if(adcState4 == 1 && adcValue4 < (PIEZOTHRESHOLD/2) && (millis() - lastreadtime4) > BOUNCE_PERIOD)
	{
	PORTC = 0xFF; 
	noteOff(CHANNEL4, 4, 127);
	
	adcState4 = 0;
    }
	
}

void ADC5On(void)
{

	adcValue5 = ADC_read(5);
	
	lcd_gotoxy1(5); 
	lcd_char('H'); 
	
	if(!(PING & 0x01)) //press
	{
	HHpedal = 1;
	}

	if(adcValue5 >= PIEZOTHRESHOLD && adcState5 == 0)
	{
	
	while(flag_peak)
	{
    adcValue5 = ADC_read(5);

    if(last_val > adcValue5)
    flag_peak=0;
    
	last_val=adcValue5;
    }
	
	last_val = 0;
    flag_peak = 1;

	noteOn(CHANNEL5, 5, 127);
	PORTC = 0xDF; 
	
	lcd_gotoxy2(5); 
	lcd_char(0x5E);
	lcd_gotoxy2(12); 
	lcd_showvalue(adcValue5); 
	
	adcState5 = 1;
	
	lastreadtime5 = millis();
	
	}
	
}

void ADC5Off(void)
{
	
	adcValue5 = ADC_read(5);
	
	if(adcState5 == 1 && adcValue5 < (PIEZOTHRESHOLD/2) && (millis() - lastreadtime5) > BOUNCE_PERIOD)
	{
	PORTC = 0xFF; 
	noteOff(CHANNEL5, 5, 127);
	
	adcState5 = 0;
    }
	
}

void ADC6On(void)
{

	adcValue6 = ADC_read(6);
	
	lcd_gotoxy1(6); 
	lcd_char('R'); 
	
	if(adcValue6 >= PIEZOTHRESHOLD && adcState6 == 0)
	{

	while(flag_peak)
	{
    adcValue6 = ADC_read(6);

    if(last_val > adcValue6)
    flag_peak=0;
    
	last_val=adcValue6;
    }
	
	last_val = 0;
    flag_peak = 1;
	
	noteOn(CHANNEL6, 6, 127);
	PORTC = 0xBF; 
	
	lcd_gotoxy2(6); 
	lcd_char(0x5E);
	lcd_gotoxy2(12); 
	lcd_showvalue(adcValue6); 
	
	adcState6 = 1;
	
	lastreadtime6 = millis();
	}
	
}

void ADC6Off(void)
{
	
	adcValue1 = ADC_read(1);
	
	if(adcState6 == 1 && adcValue6 < (PIEZOTHRESHOLD/2) && (millis() - lastreadtime6) > BOUNCE_PERIOD)
	{
	PORTC = 0xFF; 
	noteOff(CHANNEL6, 6, 127);
	
	adcState6 = 0;
    }
	
}

void ADC7On(void)
{

	adcValue7 = ADC_read(7);
	
	lcd_gotoxy1(7); 
	lcd_char('C'); 
	
	if(adcValue7 >= PIEZOTHRESHOLD && adcState7 == 0)
	{
	
	while(flag_peak)
	{
    adcValue7 = ADC_read(7);

    if(last_val > adcValue7)
    flag_peak=0;
    
	last_val=adcValue7;
    }
	
	last_val = 0;
    flag_peak = 1;
	
	noteOn(CHANNEL7, 7, 127);
	PORTC = 0x7F; 
	
	lcd_gotoxy2(7); 
	lcd_char(0x5E);
	lcd_gotoxy2(12); 
	lcd_showvalue(adcValue7); 
	
	adcState7 = 1;
	
	lastreadtime7 = millis();
	}
	
}

void ADC7Off(void)
{
	
	adcValue7 = ADC_read(7);
	
	if(adcState7 == 1 && adcValue7 < (PIEZOTHRESHOLD/2) && (millis() - lastreadtime7) > BOUNCE_PERIOD)
	{
	PORTC = 0xFF; 
	noteOff(CHANNEL7, 7, 127);
	
	adcState7 = 0;
    }
	
}