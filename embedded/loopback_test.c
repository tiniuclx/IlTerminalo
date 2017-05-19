#define PICTOR_FASTMODE
#include <avr/io.h>

#include "../pictor.h"
#include "../fonts/OryxB.h"
#include "../fonts/Mash.h"

void init_spi_slave(void);
void init_spi_master(void);
uint8_t rx(void);
void tx(uint8_t b);

int main() {
	pictorInit(0);
	pictorSetRotation(0);
	unsigned char input_char = 'a';
	unsigned char send_buffer[64] = "Hello, world!";
	unsigned char receive_buffer[64] = "";
	int i=0;
	int clear_flag = 0;
	init_spi_master();
	for(i=0; i<strlen(send_buffer); i++){
		tx(send_buffer[i]);
		receive_buffer[i]=rx();
	}
	pictorDrawS(receive_buffer, (point){0,0}, WHITE, BLACK, Mash,1);
	return 0;
}

void init_spi_slave(void){
	DDRB = _BV(PB6);
	SPCR = _BV(SPE);
}

void init_spi_master(void){
	DDRB = _BV(PB4) | _BV(PB5) | _BV(PB7);
	SPCR = _BV(SPE) | _BV(MSTR) | _BV(SPI2X);
}

uint8_t rx(void){
	while(!(SPSR & _BV(SPIF)))
		;
	return SPDR;
}

void tx(uint8_t b) {
	SPDR = b;
	while(!(SPSR & _BV(SPIF)));
}

