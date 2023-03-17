#include <iostream>
#include <cstdint>
#include <vector>
using namespace std;

#include "LEDController.h"
#include "OFController.h"

int main()
{
    OFController OF;
    LEDController strip;
    vector<int> shape;

    OF.init();

    int OFnum = 7;
    int num_strip = 2;

    vector<int> status;
    status.resize(5 * OFnum);

    shape.clear();
    shape.resize(num_strip);

    for (int i = 0; i < num_strip; i++)	shape[i] = 100;
    strip.init(shape);

    vector<vector<int>> LEDstatus;
    LEDstatus.resize(num_strip);

    for (int i = 0; i < num_strip; i++)
	    LEDstatus[i].resize(shape[i]);
   
 /*    
    for (int a = 0; a < 15; a++)
    {

    	for (int i = 0; i < 5*OFnum; i++)
    	{
        	status[i] = 0xFFFFFF00 + a;
    	}

    	for (int i = 0; i < num_strip; i++)
	    	for (int j = 0; j < shape[i]; j++)	LEDstatus[i][j] = 0xFFFFFF00 + a;
	strip.sendAll(LEDstatus);
    	OF.sendAll(status);
    	usleep(1000000);
    }
*/
while(1){
   for(int a = 1; a <= 100 ; a++) {
    for (int i = 0; i < 5*OFnum; i++)
    {
        status[i] = 0xFF000000 + a;
    }
    for (int i = 0; i < num_strip; i++)
	    for (int j = 0; j < shape[i]; j++)	LEDstatus[i][j] = 0xFF000000 + a;
    strip.sendAll(LEDstatus);
    OF.sendAll(status);
    usleep(100);
    }

   for(int a = 100; a >= 1 ; a--) {
    for (int i = 0; i < 5*OFnum; i++)
    {
        status[i] = 0xFF000000 + a;
    }
    for (int i = 0; i < num_strip; i++)
	    for (int j = 0; j < shape[i]; j++)	LEDstatus[i][j] = 0xFF000000 + a;
    strip.sendAll(LEDstatus);
    OF.sendAll(status);
    usleep(100);
    }
    for(int a = 1; a <= 100 ; a++) {
    for (int i = 0; i < 5*OFnum; i++)
    {
        status[i] = 0x00FF0000 + a;
    }
    for (int i = 0; i < num_strip; i++)
	    for (int j = 0; j < shape[i]; j++)	LEDstatus[i][j] = 0x00FF0000 + a;
    strip.sendAll(LEDstatus);
    OF.sendAll(status);
    usleep(100);
    }

   for(int a = 100; a >= 1 ; a--) {
    for (int i = 0; i < 5*OFnum; i++)
    {
        status[i] = 0x00FF0000 + a;
    }
    for (int i = 0; i < num_strip; i++)
	    for (int j = 0; j < shape[i]; j++)	LEDstatus[i][j] = 0x00FF0000 + a;
    strip.sendAll(LEDstatus);
    OF.sendAll(status);
    usleep(100);
    }
    for(int a = 1; a <= 100 ; a++) {
    for (int i = 0; i < 5*OFnum; i++)
    {
        status[i] = 0x0000FF00 + a;
    }
    for (int i = 0; i < num_strip; i++)
	    for (int j = 0; j < shape[i]; j++)	LEDstatus[i][j] = 0x0000FF00 + a;
    strip.sendAll(LEDstatus);
    OF.sendAll(status);
    usleep(100);
    }

   for(int a = 100; a >= 1 ; a--) {
    for (int i = 0; i < 5*OFnum; i++)
    {
        status[i] = 0x0000FF00 + a;
    }
    for (int i = 0; i < num_strip; i++)
	    for (int j = 0; j < shape[i]; j++)	LEDstatus[i][j] = 0x0000FF00 + a;
    strip.sendAll(LEDstatus);
    OF.sendAll(status);
    usleep(100);
    }
}
    // usleep(1000000);
/*
    for (int i = 0; i < 5*OFnum; i++)
    {
        status[i] = 0x00aa0010;
    }

    for (int i = 0; i < num_strip; i++)
	    for (int j = 0; j < shape[i]; j++)	LEDstatus[i][j] = 0x00aa0010;
    strip.sendAll(LEDstatus);
    OF.sendAll(status);
    usleep(1000000);

    for (int i = 0; i < 5*OFnum; i++)
    {
        status[i] = 0x0000aa10;
    }

    for (int i = 0; i < num_strip; i++)
	    for (int j = 0; j < shape[i]; j++)	LEDstatus[i][j] = 0x0000aa10;
    strip.sendAll(LEDstatus);
    OF.sendAll(status);
    usleep(1000000);

    for (int i = 0; i < 5*OFnum; i++)
    {
        status[i] = 0x00000010;
    }

    for (int i = 0; i < num_strip; i++)
	    for (int j = 0; j < shape[i]; j++)	LEDstatus[i][j] = 0x00000010;
    strip.sendAll(LEDstatus);
    OF.sendAll(status);
    */

    strip.finish();

    
    return 0;
}  


