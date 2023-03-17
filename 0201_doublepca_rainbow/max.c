#include <stdio.h>
#include <string.h>

// for I2C port
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

#define LIGHTNESS_MAX 25

#define NUMPCA 2
const int PCAaddr[] = {0x22, 0x23};

#include <time.h>
void delay(int number_of_ms)
{
	clock_t start_time = clock();

	while (clock() < start_time + number_of_ms / 1000.0 * CLOCKS_PER_SEC)	;

}

int I2C_init();

int main()
{
	int fd[NUMPCA];
	int length;
	unsigned char buffer[60] = {0};

	// ----- OPEN THE I2C BUS -----
	for (int i = 0; i < NUMPCA; i++)
	{
		if ((fd[i] = I2C_init()) < 0)
		{
			printf("I2C of %d init fail.\n", i);
			return 1;
		}
		printf("File descriptor of %d opened at %d.\n", i, fd[i]);
		
		if (ioctl(fd[i], I2C_SLAVE, PCAaddr[i]) < 0)
		{
			printf("Failed to acquire bus access and/or talk to slave %d", i);
			return 2;
		}
	}
	printf("======================\n\n");

	// write to PCA
	buffer[0] = 0x45;
	buffer[1] = 0xFF;

	for (int i = 0; i < NUMPCA; i++)
	{
		if(write(fd[i], buffer, 2) != 2)
		{
			printf("Failed to write to I2C bus.\n");
			return 3;
		}
	}


	buffer[0] = 0x88;
	buffer[1] = 150;
	buffer[2] = 0x00;
	buffer[3] = 0x00;

	buffer[4] = 0x00;
	buffer[6] = 0x00;
	buffer[5] = 255;

	buffer[9] = 255;
	buffer[7] = 0x00;
	buffer[8] = 0x00;

	buffer[12] = 0x00;
	buffer[10] = 0x00;
	buffer[11] = 0x00;

	buffer[15] = 0xFF;
	buffer[13] = 0x00;
	buffer[14] = 0x00;

	
		for (int i = 0; i < NUMPCA; i++)
			if (write(fd[i], buffer, 16) != 16)
			{
				printf("Failed to write to the I2C bus %d. \n");
				delay(500);
			}
	return 0;
}

int I2C_init()
{
	int file_i2c;
	char *filename = (char*)"/dev/i2c-1";
	if ((file_i2c = open(filename, O_RDWR)) < 0)
	{
		printf("Failed to open i2c bus. Exit.\n");
		return -1;
	}
	return file_i2c;
}
