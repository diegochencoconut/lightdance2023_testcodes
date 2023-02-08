#ifndef LEDCONTROLLER_H
#define LEDCONTROLLER_H

#include <vector>
#include <stdio.h>
#include <iostream>
#include <cstdint>
#include <cmath>

// include for GPIO
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string>

// library for WS2812
#include "clk.h"
#include "gpio.h"
#include "dma.h"
#include "pwm.h"
#include "ws2811.h"

// parameters for WS2812
#define TARGET_FREQ     WS2811_TARGET_FREQ
#define GPIO_PIN        18
#define DMA             10
#define STRIP_TYPE      WS2811_STRIP_GRB

class LEDStatus
{
public:
    LEDStatus();
    LEDStatus(const int &colorCode);
    uint32_t getrgb();
private:
    uint32_t rgb;
    int r;
    int g;
    int b;
};

class LEDController
{
public:
    LEDController();
 
    int init(const std::vector<int> &shape);

    int sendall(const std::vector<std::vector<int>> &statusLists);
    // send all data to RPI and push them to LED strips.
    // return value: 
    // 0: OK
    // -1: The data size of statausLists is not consist with number of strips initialized

    ~LEDController();

private:
    ws2811_t ledstring = 
    {
        .freq = TARGET_FREQ,
        .dmanum = DMA,
        .channel = 
        {
            [0] = 
            {
                .gpionum = GPIO_PIN,
                .invert = 0,
                .count = 100,    //just for init
                .strip_type = STRIP_TYPE,
                .brightness = 255,
            },
        },
    };

    int *length;
    int strip_num;

    int play(const std::vector<std::vector<int>> &statusLists);
    void gpio_init();
    void select_channel(int channel);
    void delayMicroseconds(int delay_us);
    const int HIGH = 1;
    const int LOW  = 0;

    int A0, A1, A2;
};

#endif
