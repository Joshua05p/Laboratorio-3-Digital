/*
 * Lab3.c
 *
 * Created: 29/01/2026 10:12:50
 * Author : masco
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include "Libreria.h"
#include <stdint.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>


/****************************************/
// Function prototypes
uint8_t valorSpi = 0;
int canal_actual = 0;
int voltaje1 = 0; //Maestro
int voltaje2 = 0; //Maestro
uint16_t valor1 = 0;
uint16_t valor2 = 0;
void setup();
uint16_t adc1 = 0;
uint16_t adc2 = 0;
char texto1[6];
char texto2[6];


///////////////////////ESCLAVO///////////////////////////////

/*

// Main Function
int main(void)
{
   
	setup();
	initADC();
	initCON();
	iniciar_USART(103);
	
	
	spiInit(spi_slave_ss, spi_msb, clock_low, spi_clock_first_edge); //Esclavo
	sei();
    while (1) 
    {
		itoa(valor1, texto1, 10);
		cadena(texto1);
		enviar('\n');
		_delay_ms(200);
    }
}


// NON-Interrupt subroutines
void setup(){
	PORTD |= (1<<PORTD2)|(1<<PORTD3)|(1<<PORTD4)|(1<<PORTD5)|(1<<PORTD6)|(1<<PORTD7);
	PORTB |= (1<<PORTB0)|(1<<PORTB1);
	
}


// Interrupt routines

//ESCLAVO
ISR(ADC_vect){
	

	initCON();
	
	if(canal_actual == 0){
		ADMUX |= (1 << MUX2) | (1 << MUX1);    // ADC6
		ADMUX &= ~(1<<MUX0);
		canal_actual = 1;
		valor1 = ADC;
		//voltaje1 = (valor1/1023.0)*5.0;
		

	}else if (canal_actual == 1)
	{
		ADMUX |= (1<<MUX2) | (1<<MUX0);           //cambia al canal 5
		ADMUX &= ~(1<<MUX1);
		valor2 = ADC;
		//voltaje2 = (valor2/1023.0)*5.0;
		canal_actual = 0;
	}
}

ISR(SPI_STC_vect)
{
	static uint8_t parte = 0;
	static uint16_t dato;

	uint8_t comando = SPDR;

	if(comando == '1'){         // Maestro pide ADC1
		dato = valor1;
		SPDR = dato >> 8;       // alto
		parte = 1;
	}
	else if(comando == '2'){    // Maestro pide ADC2
		dato = valor2;
		SPDR = dato >> 8;
		parte = 1;
	}
	else if(parte == 1){
		SPDR = dato & 0xFF;     // bajo
		parte = 0;
	}
	else{
		SPDR = 0;
	}
}

*/



////////////////////////////////////MAESTRO//////////////////////////////////////

// Main Function
int main(void){

	setup();
	iniciar_USART(103);
	
	//MSS para seleccionar el Slave
	DDRB |= (1<<PORTB2);
	PORTB |= (1<<PORTB2); //Maestro
	
	spiInit(spi_master_32, spi_msb, clock_low, spi_clock_first_edge); //Maestro
	sei();
    while (1) 
    {
		
		//MAESTRO
		adc1 = leerADC_esclavo('1');  // ADC6 del esclavo
		adc2 = leerADC_esclavo('2');  // ADC5 del esclavo
		itoa(adc1, texto1, 10);
		itoa(adc2, texto2, 10);
		cadena(adc1);
		cadena("    ");
		cadena(adc2);
		enviar('\n');


		_delay_ms(200);

		
		//Esclavo
		
		
    }
}



// NON-Interrupt subroutines
void setup(){
	PORTD |= (1<<PORTD2)|(1<<PORTD3)|(1<<PORTD4)|(1<<PORTD5)|(1<<PORTD6)|(1<<PORTD7);
	PORTB |= (1<<PORTB0)|(1<<PORTB1);
	
}


// Interrupt routines




