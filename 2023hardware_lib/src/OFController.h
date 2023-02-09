#ifndef OF_CONTROLLER
#define OF_CONTROLLER

#include <stdio.h>
#include <vector>
#include <iostream>
#include <cstdint>
#include <cmath>

// library for PCA
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

using namespace std;

// define
#define NUMPCA 7
const int PCAaddr[] = {0x1f, 0x20, 0x22, 0x23, 0x5b, 0x5c, 0x5e};


class OFColor {
    public:
        OFColor();
        OFColor(const int &colorCode);
        int get_r();
        int get_g();
        int get_b();
    private:
        int r, g, b;

};

class OFController {
  public:
    OFController();
    int init();
    int sendAll(const vector<int> &statusLists);

  private:
    int I2C_init();
	int buffer[1+15*NUMPCA] = {0};
    int fd[NUMPCA];


};

#endif

