/*
 * Libreria.h
 *
 * Created: 29/01/2026 10:16:52
 *  Author: masco
 */ 


#ifndef LIBRERIA_H_
#define LIBRERIA_H_
#include <avr/io.h>
#include "stdint.h"


typedef enum{
	spi_msb = 0b00000000,
	spi_lsb = 0b00100000
	}orden;
	
typedef enum{
	clock_high	= 0b00001000,
	clock_low	= 0b00000000
	}polaridad;

typedef enum{
	spi_master_2	= 0b01010000,
	spi_master_4	= 0b01010001,
	spi_master_8	= 0b01010010,
	spi_master_16	= 0b01010011,
	spi_master_32	= 0b01010100,
	spi_master_64	= 0b01010101,
	spi_master_128	= 0b01010110,
	spi_slave_ss	= 0b01000000
	}tipo;


typedef enum{
	spi_clock_first_edge	= 0b00000000,
	spi_clock_last_edge		= 0b00000100
	}phase;

void spiInit(tipo, orden, polaridad, phase);
void spiwrite(uint8_t dat);
unsigned spidata();
uint8_t spiread(void);

///////////////////
void enviar(char data);
void cadena();
void iniciar_USART();
void initADC();
void initCON();


#endif /* LIBRERIA_H_ */
