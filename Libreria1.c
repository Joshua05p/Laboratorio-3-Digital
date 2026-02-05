/*
 * Libreria.c
 *
 * Created: 29/01/2026 10:15:44
 *  Author: masco
 */ 
#include "Libreria.h"
#include <avr/interrupt.h>

void spiInit(tipo sType, orden sOrden, polaridad sPolaridad, phase sPhase){
	//PB2 = SS
	//PB3 = MOSI
	//PB4 = MISO
	//PB5 = SCK
	if (sType & (1<<MSTR)){ //If master mode
		DDRB |= (1<<DDB3)|(1<<DDB5)|(1<<DDB2); //MOSI, NEGADO_SS, SS
		DDRB &= ~(1<<DDB4); //MISO
		SPCR |= (1<<MSTR);
		
		uint8_t temp = sType & 0b00000111;
		switch(temp){
			case 0:
				SPCR &= ~((1<<SPR1)|(1<<SPR0));
				SPSR |=(1<<SPI2X);
			break;
			case 1:
				SPCR &= ~((1<<SPR1)|(1<<SPR0));
				SPSR &= ~(1<<SPI2X);
			break;
			case 2:
				SPCR |= (1<<SPR0);
				SPCR &= ~(1<<SPR1);
				SPSR |= (1<<SPI2X);
			break;
			case 3:
				SPCR |= (1<<SPR0);
				SPCR &= ~(1<<SPR1);
				SPSR &= ~(1<<SPI2X);
			break;
			case 4:
				SPCR &= ~(1<<SPR0);
				SPCR |= (1<<SPR1);
				SPSR |= (1<<SPI2X);
			break;
			case 5:
				SPCR |= (1<<SPR1);
				SPCR &= ~(1<<SPR0);
				SPSR &= ~(1<<SPI2X);
			break;
			case 6:
				SPCR |= (1<<SPR0);
				SPCR |= (1<<SPR1);
				SPSR &= ~(1<<SPI2X);
			break;
		}
		
	}else { //If slave mode
		DDRB |= (1<<DDB4); //MISO
		DDRB &= ~((1<<DDB3)|(1<<DDB5)|(1<<DDB2)); //MOSI, SCK, SS
		SPCR &= ~(1<<MSTR); //SLAVE
	}
	//Enable SPI, orden, polaridad, phase
	SPCR |= (1<<SPE)|(1<<SPIE)|sOrden|sPolaridad|sPhase;

}	
void spiReceiveWait(){
	while (!(SPSR & (1<<SPIF))); //Wait for data receive complete
	
}	
void spiwrite(uint8_t dat){
	SPDR = dat;
}
unsigned spidata(){
	if(SPSR & (1<<SPIF))
	return 1;
	else
	return 0;
}
uint8_t spiread(uint8_t data){
	while (!(SPSR & (SPIF)));
	return(SPDR);
}

void initADC(void)
{
	cli();

	ADMUX = 0;
	ADMUX |= (1 << REFS0);                 // AVcc
	ADMUX |= (1 << MUX2) | (1 << MUX1);    // ADC6

	ADCSRA = (1 << ADEN)  |                // ADC enable
	(1 << ADIE)  |                // Interrupt enable
	(1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Prescaler 128

	sei();
}
void initCON(){
	ADCSRA |= (1 << ADSC);
}
void iniciar_USART(unsigned int ubrr) {
	UBRR0H = (ubrr >> 8);
	UBRR0L = ubrr;

	UCSR0B |= (1 << TXEN0) | (1 << RXEN0) | (1 << RXCIE0) ; // Habilitar transmisión

	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
}

void enviar(char data) {
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;

}

void cadena(char *caracteres) {
	while (*caracteres != '\0'){
		enviar(*caracteres);
		caracteres++;
	}

}

uint16_t leerADC_esclavo(uint8_t canal)
{
	uint8_t alto, bajo;
	uint16_t valor;

	PORTB &= ~(1<<PORTB2);  // SS = 0 ? activar esclavo

	spiread(canal);   // Manda 'A' o 'B'
	alto = spiread(0x00);  // Reloj para recibir byte alto
	bajo = spiread(0x00);  // Reloj para recibir byte bajo

	PORTB |= (1<<PORTB2);   // SS = 1 ? desactivar esclavo

	valor = ((uint16_t)alto << 8) | bajo;
	return valor;
}
