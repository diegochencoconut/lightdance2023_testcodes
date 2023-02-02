#include <stdio.h>
#include <string.h>

// for I2C port
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

// for delay
#include <time.h>

void delay(int number_of_ms)
{
	clock_t start_time = clock();

	while (clock() < start_time + number_of_ms / 1000.0 * CLOCKS_PER_SEC)
		;
}

int I2C_init();

int main()
{
	int file_i2c;
	int length;
	unsigned char buffer[60] = {0};

	// ----- OPEN THE I2C BUS -----
	if ((file_i2c = I2C_init()) < 0)
	{
		printf("I2C init fail.\n");
		return 1;
	}
	printf("File descriptor opened at %d.\n", file_i2c);
	
	int addr = 0x1f;

	if (ioctl(file_i2c, I2C_SLAVE, addr) < 0)
	{
		printf("Failed to acquire bus access and/or talk to slave.\n");
		return 2;
	}

	// write to PCA
	
	buffer[0] = 0x88;	//10001000, auto increment from "brightness control LED0"

	int lightness = 0;
	bool status = 0;
	while (true)
	{	
		// printf("lightness: %d\n", lightness);
		if (status == 0)	lightness++;
		else lightness--;

		if (lightness >= 50)	status = 1;
		else if (lightness <= 0)	status = 0;

		// LED brightness control
		// circuit: R | VCC | G | B			
		// LED1: RGB = 0xff0000
		buffer[1] = 0x01;
		buffer[2] = 0x00;
		buffer[3] = 0x00;

		// LED2: RGB = 0x00ff00
		buffer[4] = 0x01;
		buffer[5] = 0x00;
		buffer[6] = 0x00;

		// LED3: RGB = 0x0000ff
		buffer[7] = 0x01;
		buffer[8] = 0x00;
		buffer[9] = 0x00;

		// LED4: RGB = 0xffff00
		buffer[10] = 0x01;
		buffer[11] = 0x00;
		buffer[12] = 0x00;

		// LED5: RGB = 0xff00ff
		buffer[13] = 0x01;
		buffer[14] = 0x00;
		buffer[15] = 0x00;
		
		for (int i = 1; i <= 15; i++)
		{
			buffer[i] *= lightness;
		}

		if (write(file_i2c, buffer, 16) != 16)
		{
			printf("Failed to write to the I2C bus.\n");
		}
		/*
		else
		{
			printf("LED status (R, G, B):\n");
			printf("LED1: %3d\t%3d\t%3d\n", buffer[1], buffer[2], buffer[3]);
			printf("LED2: %3d\t%3d\t%3d\n", buffer[4], buffer[5], buffer[6]);
			printf("LED3: %3d\t%3d\t%3d\n", buffer[7], buffer[8], buffer[9]);	
			printf("LED4: %3d\t%3d\t%3d\n", buffer[10], buffer[11], buffer[12]);
			printf("LED5: %3d\t%3d\t%3d\n", buffer[13], buffer[14], buffer[15]);
		}
		*/
		// delay(20);
	}

	return 0;
}

int I2C_init()
{
	int file_i2c;
	printf("======== Opening I2C INIT ========\n");
	printf("Trying channel 0: \n");
	// select the proper i2c file (0 or 1)
	char *filename = (char*)"/dev/i2c-0";
	if ((file_i2c = open(filename, O_RDWR)) < 0)
	{
		printf("Failed to open the i2c bus at 0, try 1\n\nTrying channel 1: \n");
		
		filename = (char*)"/dev/i2c-1";	//change to channel 1
		if ((file_i2c = open(filename, O_RDWR)) < 0)
		{
			printf("Failed to open both i2c bus. Exit.\n");
			return -1;
		}
		else
			printf("Open i2c bus at channel 1 successfully.\n\n");
	}
	else
		printf("Open i2c bus at channel 0 successfully.\n\n");

	printf("======== Closing I2C INIT ========\n\n");
	return file_i2c;	
}
