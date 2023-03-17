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

    for (int ab = 0; ab < 5; ab++)
    {
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
    }
/*    for (int i = 0; i < 5 * OFnum; i++)
	    status[i] = 0;

    status[11] = 0xFF000000;
    status[12] = 0x00FF0000;
    status[14] = 0x0000FF00;
   while (true)
   {
    for (int i = 1; i <= 100; i++)
    {
	    status[11] = 0xFF000000 + i;
	    status[12] = 0x00FF0000 + i;
	    status[14] = 0x0000FF00 + i;


   	 OF.sendAll(status);	
	 usleep(10000);
    }
   for (int i = 100; i >= 1; i--)
    {
	    status[11] = 0xFF000000 + i;
	    status[12] = 0x00FF0000 + i;
	    status[14] = 0x0000FF00 + i;


   	 OF.sendAll(status);	
	 usleep(10000);
    }}*/
    return 0;
}  


