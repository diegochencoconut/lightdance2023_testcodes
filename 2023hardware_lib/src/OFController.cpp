#include "OFController.h"

// ==================== OFColor ============================

OFColor::OFColor() : r(0), g(0), b(0) {}

OFColor::OFColor(const int &colorCode) {
    const int R = (colorCode >> 24) & 0xff;
    const int G = (colorCode >> 16) & 0xff;
    const int B = (colorCode >> 8) & 0xff;
    const int A = (colorCode >> 0) & 0xff;

    // TODO: convert rgba to rgb
    const float gamma = 2.2;
    // convert rgba to rgb

    // GAMMA CORRECTION
    r = (int)(pow(R * A, (1/gamma)));
    g = (int)(pow(G * A, (1/gamma)));
    b = (int)(pow(B * A, (1/gamma)));
}

int OFColor::get_r(){
    return r;
}int OFColor::get_g(){
    return g;
}int OFColor::get_b(){
    return b;
}


// ==================== OFController ========================

OFController::OFController() {}

int OFController::init() {
    printf("Hardware Initialzed\n");

    // open I2C bus
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
	buffer[0] = 69; //0x45
	buffer[1] = 255; //0xFF

	for (int i = 0; i < NUMPCA; i++)
	{
		if(write(fd[i], buffer, 2) != 2)
		{
			printf("Failed to write to I2C bus.\n");
			return 3;
		}
	}

    return 1;
}

int OFController::sendAll(const vector<int> &statusLists) {
    printf("%d strips sent\n", (int)statusLists.size());
    // OFController RGBData[(int)statusLists.size()];
    buffer[0] = 136 //0x88
    int counter;
    for (int i = 0; i < NUMPCA; i++)
	{   
        counter = 0;
        for(int j=i*5; j<j+5; j++){
            OFColor Status(statusLists[j]);
            buffer[counter*3+1] = Status.get_r();
            buffer[counter*3+2] = Status.get_g();
            buffer[counter*3+3] = Status.get_b();
            counter++;
        }
		if(write(fd[i], buffer, 16) != 16)
		{
			printf("Failed to write to the I2C bus.\n");
			return 4;
		}
	}

    return 1;
}

int OFController::I2C_init(){
    int file_i2c;
	char *filename = (char*)"/dev/i2c-1";
	if ((file_i2c = open(filename, O_RDWR)) < 0)
	{
		printf("Failed to open i2c bus. Exit.\n");
		return -1;
	}
	return file_i2c;
}

