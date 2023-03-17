#include <cstdint>
#include <iostream>
#include <vector>
using namespace std;

#include "LEDController.h"

int main() {
    LEDController strip;
    vector<int> shape;

    int num_strip = 8;

    shape.clear();
    shape.resize(num_strip);

    for (int i = 0; i < num_strip; i++) shape[i] = 3;
    strip.init(shape);

    vector<vector<int>> status;

    status.resize(num_strip);

    for (int i = 0; i < num_strip; i++) {
        status[i].resize(shape[i]);
        for (int j = 0; j < shape[i]; j++) status[i][j] = 0xFF000000;
    }
    strip.sendAll(status);

    for (int it = 0; it <= 100; it++) {
        for (int i = 0; i < num_strip; i++) {
            status[i].resize(shape[i]);
            for (int j = 0; j < shape[i]; j++) status[i][j] += 1;
        }
        strip.sendAll(status);
        printf("Now light: %X\n", status[0][0]);
        usleep(100000);
    }
    for (int i = 0; i < num_strip; i++) {
        status[i].resize(shape[i]);
        for (int j = 0; j < shape[i]; j++) status[i][j] = 0x00FF0000;
    }
    strip.sendAll(status);

    for (int it = 0; it <= 100; it++) {
        for (int i = 0; i < num_strip; i++) {
            status[i].resize(shape[i]);
            for (int j = 0; j < shape[i]; j++) status[i][j] += 1;
        }
        strip.sendAll(status);
        printf("Now light: %X\n", status[0][0]);
        usleep(100000);
    }
    for (int i = 0; i < num_strip; i++) {
        status[i].resize(shape[i]);
        for (int j = 0; j < shape[i]; j++) status[i][j] = 0x0000FF00;
    }
    strip.sendAll(status);

    for (int it = 0; it <= 100; it++) {
        for (int i = 0; i < num_strip; i++) {
            status[i].resize(shape[i]);
            for (int j = 0; j < shape[i]; j++) status[i][j] += 1;
        }
        strip.sendAll(status);
        printf("Now light: %X\n", status[0][0]);
        usleep(1000);
    }

    strip.finish();
    return 0;
}
