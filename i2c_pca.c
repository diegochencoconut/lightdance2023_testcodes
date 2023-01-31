#include <stdio.h>
#include <unistd.h>                             //Needed for I2C port
#include <fcntl.h>                              //Needed for I2C port
#include <sys/ioctl.h>                  //Needed for I2C port
#include <linux/i2c-dev.h>              //Needed for I2C port

int main()
{
        int file_i2c;
        int length;
        unsigned char buffer[60] = {0};


        //----- OPEN THE I2C BUS -----
        char *filename = (char*)"/dev/i2c-1";
        if ((file_i2c = open(filename, O_RDWR)) < 0)
        {
                //ERROR HANDLING: you can check errno to see what went wrong
                printf("Failed to open the i2c bus");
                return 1;
        }

        int addr = 0x1f;          //<<<<<The I2C address of the slave
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
        buffer[0] = 0x45;
        buffer[1] = 0xff;
        buffer[2] = 0x02;
        buffer[3] = 0xaa;
        buffer[4] = 0x08;
        buffer[5] = 0x00;
        buffer[6] = 0x06;
        buffer[7] = 0x07;
        length = 2;                     //<<< Number of bytes to write
        if (write(file_i2c, buffer, length) != length)          //write() returns the number of bytes actually written, if it doesn't match then an error occurred (e.g. no response from the device)
        {
                /* ERROR HANDLING: i2c transaction failed */
                printf("Failed to write to the i2c bus.\n");
        }
        else{
                printf("buffer send\n");
                printf("%d :: %d\n", buffer[0], buffer[1]);
        }

	// register
	//
        buffer[0] = 0x88;

	// LED buffer
	// | LED || Blue  | Green | Red |
	// |-----||-------|-------|-----|
	// |  1  ||   1   |   2   |  3  |
	// |  2  ||   4   |   5   |  6  |
	// |  3  ||   7   |   8   |  9  |
	// |  4  ||  10   |  11   | 12  |
	// |  5  ||  13   |  14   | 15  |
	// 15 --> float

        buffer[1] = 0x00;
        buffer[2] = 0x00;
        buffer[3] = 0x20;
        buffer[4] = 0x00;
        buffer[5] = 0x00;
        buffer[6] = 0x00;
        buffer[7] = 0x00;
	buffer[8] = 0x00;
	buffer[9] = 0x00;
	buffer[10] = 0x00;
	buffer[11] = 0x00;
	buffer[12] = 0x00;
	buffer[13] = 0x00;
	buffer[14] = 0x20;
	buffer[15] = 0x00;
        length =16;                     //<<< Number of bytes to write
        if (write(file_i2c, buffer, length) != length)          //write() returns the number of bytes actually written, if it doesn't match then an error occurred (e.g. no response from the device)
        {
                /* ERROR HANDLING: i2c transaction failed */
                printf("Failed to write to the i2c bus.\n");
        }
        else{
                printf("buffer send\n");
                printf("%d :: %d\n", buffer[0], buffer[1]);
        }
	return 0;
}
