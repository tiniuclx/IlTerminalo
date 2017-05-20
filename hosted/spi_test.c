#include <stdio.h>
#include <pigpio.h>
#include <string.h>

void clean_up(unsigned h);

int main() {
	/*
	 * To enable SPI on the Raspberry Pi, type into terminal:
	 * sudo raspi-config
	 * Then go to: Interfacing Options and enable SPI
	 * Restart to complete the process.
	 * */
	if(gpioInitialise() < 0) return 1;
	unsigned h = spiOpen(0, 750000, 0);
	if(h < 0) return 2;
	char buffer[64];
	while(1){
		printf("Send over SPI:     ");
		if(!scanf("%s", buffer))
			printf("\nError reading from stdin!");
		if(!strcmp(buffer, "exit")) {
			clean_up(h);
			return 0;
		}
		spiWrite(h, buffer, 64);
	}
	clean_up(h);
	return 0;
}

void clean_up(unsigned h){
	spiClose(h);
	gpioTerminate();
}
