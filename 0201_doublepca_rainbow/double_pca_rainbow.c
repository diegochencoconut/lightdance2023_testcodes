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

	int lightness = 0;
	int status = 0;
	while (1)
	{
		if (status % 2 == 0)	lightness++;
		else lightness--;

		if (lightness < -50)	//weird situation
			continue;

		if (lightness >= LIGHTNESS_MAX || lightness <= 0)
		{
			status++;
			status %= 6;
		}	
		for (int i = 0; i < 5; i++)
		{
			buffer[3 * i + 1] = (status == 0 || status == 1) ? lightness : 0 ;
			buffer[3 * i + 2] = (status == 2 || status == 3) ? lightness : 0;
			buffer[3 * i + 3] = (status == 4 || status == 5) ? lightness : 0;
		}
		
		for (int i = 0; i < NUMPCA; i++)
			if (write(fd[i], buffer, 16) != 16)
			{
				printf("Failed to write to the I2C bus %d. \n");
				delay(500);
			}
		delay(25);
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
