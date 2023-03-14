#include <iostream>
#include <cstdint>
#include <vector>
using namespace std;

#include "OFController.h"

int main()
{
    OFController OF;
    OF.init();

    int OFnum = 7;

    vector<int> status;
    status.resize(5 * OFnum);

    for (int i = 0; i < 5*OFnum; i++)
    {
        status[i] = 0xaa000010;
    }

    OF.sendAll(status);
    usleep(1000000);

    for (int i = 0; i < 5*OFnum; i++)
    {
        status[i] = 0x00aa0010;
    }

    OF.sendAll(status);
    usleep(1000000);

    for (int i = 0; i < 5*OFnum; i++)
    {
        status[i] = 0x0000aa10;
    }

    OF.sendAll(status);
    usleep(1000000);

    for (int i = 0; i < 5*OFnum; i++)
    {
        status[i] = 0x00000010;
    }

    OF.sendAll(status);

    
    return 0;
}  


