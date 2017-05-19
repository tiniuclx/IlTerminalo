#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <string.h>

#define CHANNEL 0

int main() {
	/*
	 * To enable SPI on the Raspberry Pi, type into terminal:
	 * sudo raspi-config
	 * Then go to: Interfacing Options and enable SPI
	 * Restart to complete the process.
	 * */
	wiringPiSetup();
	wiringPiSPISetup(CHANNEL, 750000);
	unsigned char buffer[256];
	while(1){
		printf("Send over SPI:     ");
		if(!scanf("%s", buffer))
			printf("\nError reading from stdin!");
		wiringPiSPIDataRW(CHANNEL, buffer, 256);
		printf("Received over SPI: %s\n", buffer);		
		memset(buffer,0,sizeof(buffer));
	}
	return 0;
}
