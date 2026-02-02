/*
 * Lab3.c
 *
 * Created: 29/01/2026 10:12:50
 * Author : masco
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include "Libreria1.h"
#include <stdint.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>


/****************************************/
// Function prototypes

uint8_t valorSpi = 0;
void refreshPort(uint8_t valor);


///////////////////////MAESTRO///////////////////////////////
// Main Function
int main(void)
{
	
	DDRC |= (1<<DDC4);
	DDRD |= (1<<DDD2)|(1<<DDD3)|(1<<DDD4)|(1<<DDD5)|(1<<DDD6)|(1<<DDD7);
	DDRB |= (1<<DDB0)|(1<<DDB1);
	
	PORTC |= (1<<PORTC4);
	
	PORTD &=	~((1<<DDD2)|(1<<DDD3)|(1<<DDD4)|(1<<DDD5)|(1<<DDD6)|(1<<DDD7));
	PORTB &= ~((1<<DDB0)|(1<<DDB1));
	
	
	spiInit(spi_master_128, spi_msb, clock_low, spi_clock_first_edge); 
	iniciar_USART(103);
	char texto[6];
	sei();
    while (1) 
    {
		
		////////////MAESTRO
		PORTC &= ~(1<<PORTC4);
		
		spiwrite('c');
		
		spiwrite(0x00);
		
		valorSpi = spiread();
		cadena("POTENCIOMETRO 1: ");
		itoa(valorSpi, texto, 10);
		cadena(texto);
		cadena("               ");

		
		
		spiwrite('A');
		
		spiwrite(0x00);
		
		valorSpi = spiread();
		cadena("POTENCIOMETRO 2: ");
		itoa(valorSpi, texto, 10);  
		cadena(texto);
		enviar('\n');
		refreshPort(valorSpi);

		PORTC |= (1<<PORTC4);
	
		
		_delay_ms(250);

		
    }
}


// NON-Interrupt subroutines
void refreshPort(uint8_t valor){
	if(valor & 0b10000000){
		PORTB |= (1<<PORTB1);
	}else{
		PORTB &= ~(1<<PORTB1);
	}
	if(valor & 0b01000000){
		PORTB |= (1<<PORTB0);
	}else{
		PORTB &= ~(1<<PORTB0);
	}
	if(valor & 0b00100000){
		PORTD |= (1<<PORTD7);
		}else{
		PORTD &= ~(1<<PORTD7);
	}
	if(valor & 0b00010000){
		PORTD |= (1<<PORTD6);
		}else{
		PORTD &= ~(1<<PORTD6);
	}
	if(valor & 0b00001000){
		PORTD |= (1<<PORTD5);
		}else{
		PORTD &= ~(1<<PORTD5);
	}
	if(valor & 0b00000100){
		PORTD |= (1<<PORTD4);
		}else{
		PORTD &= ~(1<<PORTD4);
	}
	if(valor & 0b00000010){
		PORTD |= (1<<PORTD3);
		}else{
		PORTD &= ~(1<<PORTD3);
	}
	if(valor & 0b00000001){
		PORTD |= (1<<PORTD2);
		}else{
		PORTD &= ~(1<<PORTD2);
	}

}
