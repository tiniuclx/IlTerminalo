#define PICTOR_FASTMODE
#include <avr/io.h>

#include "../pictor.h"
#include "../fonts/OryxB.h"
#include "../fonts/Mash.h"

void init_spi_slave(void);
uint8_t rx(void);
void tx(uint8_t b);

int main() {
	pictorInit(0);
	pictorSetRotation(3);
	unsigned char input_char = 'a';
	unsigned char buffer[256] = "";
	int i=0;
	init_spi_slave();
	while(1){
		do{
			input_char = rx();
			buffer[i] = input_char;
			i++;
		} while((input_char != '\0') && (i<255));
		i=0;		
		pictorDrawS(buffer, (point){0,0}, WHITE, BLACK, Mash,1);
		if(!strcmp(buffer,"clear"))
			pictorDrawAll(BLACK);		
		memset(buffer,0,sizeof(buffer));
	}
	return 0;
}

void init_spi_slave(void){
	DDRB = _BV(PB6);
	SPCR = _BV(SPE);
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

