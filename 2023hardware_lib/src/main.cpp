#include <iostream>
#include <cstdint>
#include <vector>
using namespace std;

#include "LEDController.h"

int main()
{
    LEDController strip;
    vector<int> shape;
    
    int num_strip = 5;

    shape.clear();
    shape.resize(num_strip);

    for (int i = 0; i < num_strip; i++)
        shape[i] = (i + 1) * 10;
    shape[0] = 150;
    strip.init(shape);

    vector<vector<int>> status;

    status.resize(num_strip);

    for (int i = 0; i < num_strip; i++)
    {
        status[i].resize(shape[i]);
        for (int j = 0; j < shape[i]; j++)
            status[i][j] = 10;
    }
    strip.sendall(status);

    for (int it = 0; it < 50; it++)
    {
        for (int i = 0; i < num_strip; i++)
        {
            status[i].resize(shape[i]);
            for (int j = 0; j < shape[i]; j++)
                status[i][j] = (it + 1) * 10;
        }
        strip.sendall(status);
    }
    return 0;
}  

