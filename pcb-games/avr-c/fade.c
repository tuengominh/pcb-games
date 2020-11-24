#include <avr/io.h>
#include <util/delay.h>

int main (void) {

    initialize_ADC();
    initialize_PWM();

    uint8_t brightness = 0;
    volatile uint8_t adc;

    while (1) {
        set_PWM(read_ADC()/8);
        _delay_ms(5);
    }
    return 0;
}

void initialize_ADC() {
    // set pin PC0 (ADC #0) as INPUT
    DDRC |= (1 << PC0); 
    ADMUX = 0;
    // use AVcc as the reference, and adjust for 8 bit resolution
	ADMUX |= (1 << REFS0) | (1 << ADLAR);
    // set prescaler to clock/128 and enable ADC
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0) | (1 << ADEN);    
}

void initialize_PWM() {
    // set pin PD6 (pin 6~) as OUTPUT
    DDRD |= (1 << PD6);
    // use timer0, activate fast PWM mode and non-inverting mode 
    TCCR0A |= (1 << WGM00) | (1 << WGM01) | (1 << COM0A1);
    // set prescaler to clock/8 and start PWM
    TCCR0B |= (1 << CS01); 
}

int read_ADC() {
    int ADCval;
    // start the ADC conversion
    ADCSRA |= (1 << ADSC);    
    // wait for the ADC to finish 
    while (ADCSRA & (1 << ADSC));  
    ADCval = ADCL;
    // update reading
    ADCval = (ADCH << 8) + ADCval;
    // return reading      
    return ADCval;
}

void set_PWM(uint8_t duty) {
    // set PWM based on input duty cycle
    OCR0A = duty;
}