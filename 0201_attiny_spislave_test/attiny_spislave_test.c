#include <stdio.h>
#include <unistd.h>                             //Needed for I2C port
#include <fcntl.h>                              //Needed for I2C port
#include <sys/ioctl.h>                  //Needed for I2C port
#include <linux/i2c-dev.h>              //Needed for I2C port

int main()
{
        int file_i2c;
        int length;
        unsigned char buffer[1000] = {0};


        //----- OPEN THE I2C BUS -----
        char *filename = (char*)"/dev/i2c-1";
        if ((file_i2c = open(filename, O_RDWR)) < 0)
        {
                //ERROR HANDLING: you can check errno to see what went wrong
                printf("Failed to open the i2c bus");
                return 1;
        }

        int addr = 0x10;          //<<<<<The I2C address of the slave
        if (ioctl(file_i2c, I2C_SLAVE, addr) < 0)
        {
                printf("Failed to acquire bus access and/or talk to slave.\n");
                //ERROR HANDLING; you can check errno to see what went wrong
                return 1;
        }


        //----- READ BYTES -----
        length = 2;                     //<<< Number of bytes to read
//      if (read(file_i2c, buffer, length) != length)           //read() returns the number of bytes actually read, if it doesn't match then an error occurred (e.g. no response from the device)
//      {
                //ERROR HANDLING: i2c transaction failed
//              printf("Failed to read from the i2c bus.\n");
//      }
//      else
//      {
//              for(int i=0; buffer[i]!='\0'; i++){
//                      printf("%d", buffer[i]);
//              }
//              // printf("Data read: %s\n", buffer);
//      }


        //----- WRITE BYTES -----
        length = 120;
	for (int i = 0; i < length; i++)
	{
		buffer[i] = i % 0xFF;
	}							//<<< Number of bytes to write

	int send_ptr = 0;
	while (length > 30)
	{
		if (write(file_i2c, buffer + send_ptr, 30) != 30)
		{
			printf("Failed to write to the i2c bus.\n");
		}
		else
		{
			printf("buffer %d send\n", send_ptr);
			printf("%d :: %d\n", buffer[send_ptr], buffer[send_ptr + 1]);
		}
		length -= 30;
		send_ptr += 30;
	}

	if (length > 0)
	{
        	if (write(file_i2c, buffer + send_ptr, length) != length)          //write() returns the number of bytes actually written, if it doesn't match then an error occurred (e.g. no response from the device)
        	{
               		/* ERROR HANDLING: i2c transaction failed */
                	printf("Failed to write to the i2c bus.\n");
        	}
        	else{
                	printf("final buffer send\n");
                	printf("%d :: %d\n", buffer[send_ptr], buffer[send_ptr + 1]);
        	}
	}


	return 0;
}
