#include <cstdint>
#include <iostream>
#include <vector>
using namespace std;

#include "LEDController_umb.h"

int main() {
    LEDController strip;
    vector<int> shape;

    int num_strip = 2;

    shape.clear();
    shape.resize(num_strip);

    for (int i = 0; i < num_strip; i++) shape[i] = 50;
    strip.init(shape);

    vector<vector<int>> status;

    status.resize(num_strip);

    for (int i = 0; i < num_strip; i++) {
        status[i].resize(shape[i]);
        for (int j = 0; j < shape[i]; j++) status[i][j] = 0x00000010;
    }
    strip.sendAll(status);

    for (int it = 0; it < 50; it++) {
        for (int i = 0; i < num_strip; i++) {
            status[i].resize(shape[i]);
            for (int j = 0; j < shape[i]; j++) status[i][j] += 0x00000100;
        }
        strip.sendAll(status);
        printf("Now light: %X\n", status[0][0]);
        usleep(100000);
    }

    for (int i =0 ; i <num_strip; i++){
	    status[i].resize(shape[i]);
	    for(int j=0; j<shape[i]; j++){
		    status[i][j] = 0x0000110011;
	
	    
	   }
    strip.sendAll(status);
    }
    
    usleep(1000000);
    for (int i=0; i<num_strip; i++){
	    status[i].resize(shape[i]);
	    for(int j=0; j<shape[i]; j++){
		    status[i][j] = 0x00aa0000aa;
	    }
    strip.sendAll(status);
    }
    


    strip.fini();
    return 0;
}