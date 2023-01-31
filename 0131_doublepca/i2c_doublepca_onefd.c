#include <stdio.h>
#include <unistd.h>

// Needed for I2C port
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

int main()
{
	// open two file descriptor
	int fd;
	
	// length of data to send
	int length;
	
	// buffer to send
	unsigned char buffer[60] = {0};

	//----- OPEN THE I2C BUS -----
	char *filename = (char*)"/dev/i2c-1";
	if ((fd = open(filename, O_RDWR)) < 0)
	{
		printf("Failed to open the i2c bus 1.\n");
		return 1;
	}

	int addr1 = 0x10, addr2 = 0x20;

	length = 2;
	buffer[0] = 0x08;
	buffer[1] = 0x00;

	if (ioctl(fd, I2C_SLAVE, addr1) < 0)
	{
		printf("Failed to talk to slave 1.\n");
		return 1;
	}

	if (write(fd, buffer, length) != length)
	{
		printf("Failed to write to the i2c bus 1.\n");
	}
	else
	{
		printf("i2c bus 1 send successfully.\n");
	}

	// =====================================================

	if (ioctl(fd, I2C_SLAVE, addr2) < 0)
	{
		printf("Failed to talk to slave 2.\n");
		return 1;
	}
	if (write(fd, buffer, length) != length)
	{
		printf("Failed to write to the i2c bus 2.\n");
	}
	else
	{
		printf("i2c bus 2 send successfully\n");
	}
	return 0;
}



