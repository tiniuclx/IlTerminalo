#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <string.h>

#define CHANNEL 0
#define CE0 11 // Chip Enable pin

int main() {
	/*
	 * To enable SPI on the Raspberry Pi, type into terminal:
	 * sudo raspi-config
	 * Then go to: Interfacing Options and enable SPI
	 * Restart to complete the process.
	 * */
	wiringPiSetup();
	wiringPiSPISetup(CHANNEL, 500000);
	pinMode(CE0, OUTPUT);
	digitalWrite(CE0, 1);
	unsigned char buffer[256];
	while(1){
		printf("Send over SPI:     ");
		if(!scanf("%s", buffer))
			printf("\nError reading from stdin!");
		digitalWrite(CE0, 0);
		delay(10);
		wiringPiSPIDataRW(CHANNEL, buffer, strlen(buffer)+1);
		delay(10);
		digitalWrite(CE0, 1);
		printf("Received over SPI: %s\n", buffer);		
		memset(buffer,0,sizeof(buffer));
	}
	return 0;
}
