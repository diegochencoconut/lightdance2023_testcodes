#include "LEDController_umb.h"

LEDColor_umb::LEDColor_umb() : r(0), g(0), b(0), rgb(0) {}
#define MAX_BRIGHTNESS 200
#define r_gamma 2.25
#define g_gamma 2.3
#define b_gamma 2.5

LEDColor_umb::LEDColor_umb(const int &colorCode) {
    const int R = (colorCode >> 24) & 0xff;
    const int G = (colorCode >> 16) & 0xff;
    const int B = (colorCode >> 8) & 0xff;
    const int A = (colorCode >> 0) & 0xff;

    // convert rgba to rgb
    //
    float r_cal, g_cal, b_cal;
    float r_max, g_max, b_max;

    if ((R + G + B) > 0)
    {
	    r_cal = (1.0) * R / (R + G + B);
	    g_cal = (1.0) * G / (R + G + B);
	    b_cal = (1.0) * B / (R + G + B);
	    printf("Ratio: r = %f, g = %f, b = %f\n", r_cal, g_cal, b_cal);

	    r_max = r_cal *= MAX_BRIGHTNESS;
	    g_max = g_cal *= MAX_BRIGHTNESS;
	    b_max = b_cal *= MAX_BRIGHTNESS;
	    r_cal *= A;
	    g_cal *= A;
	    b_cal *= A;
	    printf("Before gamma: r = %f, g = %f, b = %f\n", r_cal, g_cal, b_cal);
	    printf("Max value: r = %f, g = %f, b = %f\n", r_max, g_max, b_max);

	    r_cal = pow((r_cal / r_max), r_gamma) * r_max;
	    g_cal = pow((g_cal / g_max), g_gamma) * g_max;
	    b_cal = pow((b_cal / b_max), b_gamma) * b_max;
	    printf("After gamma: r = %f, g = %f, b = %f\n", r_cal, g_cal, b_cal);

	    r = (int)(r_cal);
	    g = (int)(g_cal);
	    b = (int)(b_cal);
	    printf("FINAL: R = %d, G = %d, B = %d\n", r, g, b);

	        
    }
    else
    {
	    r = 0;
	    g = 0;
	    b = 0;
	    return;
    }

    // GAMMA CORRECTION
    // r = (int)(pow(R * A, (1 / gamma)));
    // g = (int)(pow(G * A, (1 / gamma)));
    // b = (int)(pow(B * A, (1 / gamma)));
    // printf("%X, %X, %X", r, g, b);
    // rgb = ((r << 16) + (g << 8) + b);
}
uint32_t LEDColor_umb::getRGB() { return rgb; }

LEDController_umb::LEDController_umb() {
    // if (stripShape != NULL) stripShape = NULL;
}

int LEDController_umb::init(const std::vector<int> &shape) {
    // member variables initialization
    stripShape.assign(shape.begin(), shape.end());

    // initialize WS2812B
    ws2811_return_t ret;

    // ledstrips count initialize
    //ledstrip_1

    // initialize GPIO_PIN
    // gpioInit();

    ledString[0].channel[0].count = shape[0];
    if ((ret = ws2811_init(&ledString[0])) != WS2811_SUCCESS) {
        fprintf(stderr, "ws2811_init %d failed: %s\n", 0, ws2811_get_return_t_str(ret));
        return ret;
    }
    ledString[1].channel[0].count = shape[1];
    if ((ret = ws2811_init(&ledString[1])) != WS2811_SUCCESS) {
        fprintf(stderr, "ws2811_init %d failed: %s\n", 1, ws2811_get_return_t_str(ret));
        return ret;
    }

    for (int i = 0; i < ledString[0].channel[0].count ; i++){
        ledString[0].channel[0].leds[i] = 0;
    }
    if ((ret = ws2811_render(&ledString[0])) != WS2811_SUCCESS) {
        fprintf(stderr, "ws2811_render %d failed: %s\n", 0, ws2811_get_return_t_str(ret));
        return ret;
    }
    usleep(stripShape[0] * 30);

    for (int i = 0; i < ledString[1].channel[0].count ; i++){
        ledString[1].channel[0].leds[i] = 0;
    }
    if ((ret = ws2811_render(&ledString[1])) != WS2811_SUCCESS) {
        fprintf(stderr, "ws2811_render %d failed: %s\n", 1, ws2811_get_return_t_str(ret));
        return ret;
    }
    usleep(stripShape[1] * 30);
    return WS2811_SUCCESS;
}

int LEDController_umb::sendAll(const std::vector<std::vector<int>> &statusLists) {
    // Check if data size is consistent with stored during initialization

    if (statusLists[0].size() > stripShape[0]) {
        printf("Error: Strip %d is longer then init settings: %d", (int)statusLists[0].size(),
               stripShape[0]);
        return -1;
    }
    if (statusLists[1].size() > stripShape[1]) {
        printf("Error: Strip %d is longer then init settings: %d", (int)statusLists[1].size(),
               stripShape[1]);
        return -1;
    }
    // Push data to LED strips
    play(statusLists);
    return 0;
}

int LEDController_umb::play(const std::vector<std::vector<int>> &statusLists) {
    ws2811_return_t ret;

    for (int i=0 ; i<stripShape[0]; i++){
        LEDColor_umb led(statusLists[0][i]);
        ledString[0].channel[0].leds[i] = led.getRGB();
        if (i == 0) printf("rgb now: %X\n\n", led.getRGB());

    }
    if ((ret = ws2811_render(&ledString[0])) != WS2811_SUCCESS) {
        fprintf(stderr, "ws2811_render %d failed: %s\n", 0, ws2811_get_return_t_str(ret));
        return ret;
    }
    usleep(stripShape[0] * 30);

    for (int i=0 ; i<stripShape[1]; i++){
        LEDColor_umb led(statusLists[1][i]);
        ledString[1].channel[0].leds[i] = led.getRGB();
        if (i == 0) printf("rgb now: %X\n\n", led.getRGB());

    }
    if ((ret = ws2811_render(&ledString[1])) != WS2811_SUCCESS) {
        fprintf(stderr, "ws2811_render %d failed: %s\n", 1, ws2811_get_return_t_str(ret));
        return ret;
    }
    usleep(stripShape[1] * 30);
    return 0;
}

void LEDController_umb::finish() {
    stripShape.clear();
    ws2811_fini(&ledString[0]);
    ws2811_fini(&ledString[1]);
}
