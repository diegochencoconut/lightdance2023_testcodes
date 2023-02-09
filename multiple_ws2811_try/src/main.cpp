#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <signal.h>
#include <stdarg.h>
#include <getopt.h>


#include "clk.h"
#include "gpio.h"
#include "dma.h"
#include "pwm.h"

#include "ws2811.h"


// defaults for cmdline options
#define TARGET_FREQ             WS2811_TARGET_FREQ
#define GPIO_PIN                18
#define DMA                     10
#define STRIP_TYPE              WS2811_STRIP_GRB		// WS2812/SK6812RGB integrated chip+leds
//#define STRIP_TYPE            SK6812_STRIP_RGBW		// SK6812RGBW (NOT SK6812RGB)

#define WIDTH                   8
#define HEIGHT                  8
#define LED_COUNT               (WIDTH * HEIGHT)
#define LED_SECOND_COUNT        50

int width = WIDTH;
int height = HEIGHT;
int led_count = LED_COUNT;
int led_second_count = LED_SECOND_COUNT;

int clear_on_exit = 0;

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
            .count = LED_COUNT,
            .strip_type = STRIP_TYPE,
            .brightness = 255,
        },
   },
};

ws2811_t secondledstring =
{
    .freq = TARGET_FREQ,
    .dmanum = DMA,
    .channel =
    {
        [0] =
        {
            .gpionum = GPIO_PIN,
            .invert = 0,
            .count = LED_COUNT,
            .strip_type = STRIP_TYPE,
            .brightness = 255,
        },
   },
};

ws2811_led_t *matrix;

static uint8_t running = 1;

int main(int argc, char *argv[])
{
    ws2811_return_t ret;

    // parseargs(argc, argv, &ledstring);

    // matrix = malloc(sizeof(ws2811_led_t) * width * height);
    matrix = new ws2811_led_t[ width * height] ;

    // setup_handlers();

    if ((ret = ws2811_init(&ledstring)) != WS2811_SUCCESS)
    {
        fprintf(stderr, "ws2811_init failed: %s\n", ws2811_get_return_t_str(ret));
        return ret;
    }
    if ((ret = ws2811_init(&secondledstring)) != WS2811_SUCCESS)
    {
        fprintf(stderr, "ws2811_init failed (second): %s\n", ws2811_get_return_t_str(ret));
        return ret;
    }

    for (int i = 0; i < LED_COUNT; i++)
        ledstring.channel[0].leds[i] = 100;

    for (int i = 0; i < LED_SECOND_COUNT; i++)
        secondledstring.channel[0].leds[i] = 100;

    int cycles = 0;
    while (cycles++ < 100)
    {
        if ((ret = ws2811_render(&ledstring)) != WS2811_SUCCESS)
        {
            fprintf(stderr, "ws2811_render failed: %s\n", ws2811_get_return_t_str(ret));
            break;
        }
        if ((ret = ws2811_render(&secondledstring)) != WS2811_SUCCESS)
        {
            fprintf(stderr, "ws2811_render failed (second): %s\n", ws2811_get_return_t_str(ret));
            break;
        }

        // 15 frames /sec
        usleep(1000000 / 15);
    }

    if (1) {
	    ws2811_render(&ledstring);
        ws2811_render(&secondledstring);
    }

    ws2811_fini(&ledstring);
    ws2811_fini(&secondledstring);
    delete[] matrix;

    printf ("\n");
    return ret;
}
