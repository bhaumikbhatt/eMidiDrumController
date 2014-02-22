#ifndef _adc_h
#define _adc_h

#define ADC_ENABLE ADCSRA |= (1<<ADEN)
#define ADC_DISABLE ADCSRA &= 0x7F
#define ADC_START_CONVERSION ADCSRA |= (1<<ADSC)
#define ADC_STOP_CONVERSION ADCSRA &= (1<<ADSC)

void ADC_Init(void)
{
	ADMUX = 0xE0; //8 bit left-shift, channel0 default
	ADCSRA = 0x87; //Only ADEN and Pre-scaler 128, ADIF will be set after conversion completes
}

int ADC_read(char ADC_CHAN)
{
	ADMUX &= 0xE0 |(ADC_CHAN); // clear existing selection
	ADMUX |= ADC_CHAN;	// select channels 0-7
	
	ADC_START_CONVERSION; // do single conversion

	// wait for conversion done, ADSC to go inactive 
    while(ADCSRA & (1<<ADSC));
	
	return ADCH;
}

#endif