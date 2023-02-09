#include "LEDController.h"

LEDStatus::LEDStatus() : r(0), g(0), b(0), rgb(0) {}

LEDStatus::LEDStatus(const int &colorCode)
{
    const int R = (colorCode >> 24) & 0xff;
    const int G = (colorCode >> 16) & 0xff;
    const int B = (colorCode >> 8) & 0xff;
    const int A = (colorCode >> 0) & 0xff;

    const float gamma = 2.2;
    // convert rgba to rgb

    // GAMMA CORRECTION
    r = (int)(pow(R * A, (1/gamma)));
    g = (int)(pow(G * A, (1/gamma)));
    b = (int)(pow(B * A, (1/gamma)));
    
    rgb = ( ( r << 16 ) + ( g << 8 ) + b );
}

uint32_t LEDStatus::getrgb()
{
    return rgb;
}

LEDController::LEDController()
{
    strip_num = 0;

    if (length != NULL)
        length = NULL;
    
}

int LEDController::init(const std::vector<int> &shape)
{
    // member variables initialization
    strip_num = shape.size();
    length = new int[strip_num];

    // for WS2812 to allocate enough space for led data
    for (int i = 0; i < strip_num; i++)
    {
        length[i] = shape[i];
    }

    // initialize WS2812B
    ws2811_return_t ret;

    for (int i = 0; i < strip_num; i++)
    {
        ledstring[i].channel[0].count = shape[i];
        if ((ret = ws2811_init(&ledstring[i])) != WS2811_SUCCESS)
        {
            fprintf(stderr, "ws2811_init %d failed: %s\n", i, ws2811_get_return_t_str(ret));
            return ret;
        }
    }

    // initialize GPIO_PIN
    gpio_init();

    for (int i = 0; i < strip_num; i++)
    {
//      printf("Strip %d: ", i);
        select_channel(i);
//      printf("Count: %d.\n", ledstring[i].channel[0].count);
        for (int j = 0; j < length[i]; j++)
        {
            ledstring[i].channel[0].leds[j] = 0;
        }

        if ((ret = ws2811_render(&ledstring[i])) != WS2811_SUCCESS)
        {
            fprintf(stderr, "ws2811_render %d failed: %s\n", i, ws2811_get_return_t_str(ret));
            return ret;
        }
        usleep(length[i] * 30);
//      printf("\n========================\n");
    }
 
    return WS2811_SUCCESS;
}

int LEDController::sendall(const std::vector<std::vector<int>> &statusLists)
{
    // Check if data size is consistent with stored during initialization
    for (int i = 0; i < strip_num; i++)
    {
        if (statusLists[i].size() > length[i])
        {
            printf("Error: Strip %d is longer then init settings: %d", statusLists[i].size(), length[i]);
            return -1;
        }
    }

    // Push data to LED strips
    play(statusLists);
    return 0;
}

int LEDController::play(const std::vector<std::vector<int>> &statusLists)
{
    ws2811_return_t ret;
 
    for (int i = 0; i < strip_num; i++)
    {
//      printf("Strip %d: ", i);
        select_channel(i);
//      printf("Count: %d.\n", ledstring.channel[0].count);
        for (int j = 0; j < length[i]; j++)
        {
            LEDStatus led(statusLists[i][j]);
        
//          printf("%X, ", led.getrgb());

            ledstring[i].channel[0].leds[j] = led.getrgb();
        }

        if ((ret = ws2811_render(&ledstring[i])) != WS2811_SUCCESS)
        {
            fprintf(stderr, "ws2811_render %d failed: %s\n", i, ws2811_get_return_t_str(ret));
            return ret;
        }
        usleep(length[i] * 30);
//      printf("\n========================\n");
    }
    return 0;
}

void LEDController::gpio_init()
{
    int fd_export = open("/sys/class/gpio/export", O_WRONLY);
    
    if (fd_export == -1) {
        perror("Unable to open /sys/class/gpio/export");
        exit(1);
    }

    if (write(fd_export, "23", 2) != 2) {
        perror("Error writing to /sys/class/gpio/export");
        exit(1);
    }

    if (write(fd_export, "24", 2) != 2) {
        perror("Error writing to /sys/class/gpio/export");
        exit(1);
    }

    if (write(fd_export, "25", 2) != 2) {
        perror("Error writing to /sys/class/gpio/export");
        exit(1);
    }

    close(fd_export);

    // Set the pin to be an output by writing "out" to /sys/class/gpio/gpio24/direction

    int fd = open("/sys/class/gpio/gpio23/direction", O_WRONLY);
    if (fd == -1) {
        perror("Unable to open /sys/class/gpio/gpio23/direction");
        exit(1);
    }

    if (write(fd, "out", 3) != 3) {
        perror("Error writing to /sys/class/gpio/gpio23/direction");
        exit(1);
    }

    close(fd);

    // Set the pin to be an output by writing "out" to /sys/class/gpio/gpio24/direction

    fd = open("/sys/class/gpio/gpio24/direction", O_WRONLY);
    if (fd == -1) {
        perror("Unable to open /sys/class/gpio/gpio24/direction");
        exit(1);
    }

    if (write(fd, "out", 3) != 3) {
        perror("Error writing to /sys/class/gpio/gpio24/direction");
        exit(1);
    }

    close(fd);

    // Set the pin to be an output by writing "out" to /sys/class/gpio/gpio24/direction

    fd = open("/sys/class/gpio/gpio25/direction", O_WRONLY);
    if (fd == -1) {
        perror("Unable to open /sys/class/gpio/gpio25/direction");
        exit(1);
    }

    if (write(fd, "out", 3) != 3) {
        perror("Error writing to /sys/class/gpio/gpio25/direction");
        exit(1);
    }

    close(fd);


    A0 = open("/sys/class/gpio/gpio23/value", O_WRONLY);
    if (fd == -1) {
        perror("Unable to open /sys/class/gpio/gpio23/value");
        exit(1);
    }

    A1 = open("/sys/class/gpio/gpio24/value", O_WRONLY);
    if (fd == -1) {
        perror("Unable to open /sys/class/gpio/gpio24/value");
        exit(1);
    }

    A2 = open("/sys/class/gpio/gpio25/value", O_WRONLY);
    if (fd == -1) {
        perror("Unable to open /sys/class/gpio/gpio25/value");
        exit(1);
    }
}

void LEDController::select_channel(int channel){
    switch(channel){
        case 0:
            if (write(A0, "0", 1) != 1) {
            perror("Error writing to /sys/class/gpio/gpio23/value");
            exit(1);
            }
            if (write(A1, "0", 1) != 1) {
            perror("Error writing to /sys/class/gpio/gpio24/value");
            exit(1);
            }
            if (write(A2, "0", 1) != 1) {
            perror("Error writing to /sys/class/gpio/gpio25/value");
            exit(1);
            }
	    break;
        case 1:
            if (write(A0, "1", 1) != 1) {
            perror("Error writing to /sys/class/gpio/gpio23/value");
            exit(1);
            }
            if (write(A1, "0", 1) != 1) {
            perror("Error writing to /sys/class/gpio/gpio24/value");
            exit(1);
            }
            if (write(A2, "0", 1) != 1) {
            perror("Error writing to /sys/class/gpio/gpio25/value");
            exit(1);
            };
	    break;
        case 2:
            if (write(A0, "0", 1) != 1) {
            perror("Error writing to /sys/class/gpio/gpio23/value");
            exit(1);
            }
            if (write(A1, "1", 1) != 1) {
            perror("Error writing to /sys/class/gpio/gpio24/value");
            exit(1);
            }
            if (write(A2, "0", 1) != 1) {
            perror("Error writing to /sys/class/gpio/gpio25/value");
            exit(1);
            }
	    break;
        case 3:
            if (write(A0, "1", 1) != 1) {
            perror("Error writing to /sys/class/gpio/gpio23/value");
            exit(1);
            }
            if (write(A1, "1", 1) != 1) {
            perror("Error writing to /sys/class/gpio/gpio24/value");
            exit(1);
            }
            if (write(A2, "0", 1) != 1) {
            perror("Error writing to /sys/class/gpio/gpio25/value");
            exit(1);
            }
	    break;
        case 4:
            if (write(A0, "0", 1) != 1) {
            perror("Error writing to /sys/class/gpio/gpio23/value");
            exit(1);
            }
            if (write(A1, "0", 1) != 1) {
            perror("Error writing to /sys/class/gpio/gpio24/value");
            exit(1);
            }
            if (write(A2, "1", 1) != 1) {
            perror("Error writing to /sys/class/gpio/gpio25/value");
            exit(1);
            };
	    break;
        case 5:
            if (write(A0, "1", 1) != 1) {
            perror("Error writing to /sys/class/gpio/gpio23/value");
            exit(1);
            }
            if (write(A1, "0", 1) != 1) {
            perror("Error writing to /sys/class/gpio/gpio24/value");
            exit(1);
            }
            if (write(A2, "1", 1) != 1) {
            perror("Error writing to /sys/class/gpio/gpio25/value");
            exit(1);
            };
	    break;
        case 6:
            if (write(A0, "0", 1) != 1) {
            perror("Error writing to /sys/class/gpio/gpio23/value");
            exit(1);
            }
            if (write(A1, "1", 1) != 1) {
            perror("Error writing to /sys/class/gpio/gpio24/value");
            exit(1);
            }
            if (write(A2, "1", 1) != 1) {
            perror("Error writing to /sys/class/gpio/gpio25/value");
            exit(1);
            }
	    break;
        case 7:
            if (write(A0, "1", 1) != 1) {
            perror("Error writing to /sys/class/gpio/gpio23/value");
            exit(1);
            }
            if (write(A1, "1", 1) != 1) {
            perror("Error writing to /sys/class/gpio/gpio24/value");
            exit(1);
            }
            if (write(A2, "1", 1) != 1) {
            perror("Error writing to /sys/class/gpio/gpio25/value");
            exit(1);
            }
	    break;
    }
}

LEDController::~LEDController()
{
    delete[] length;
    for (int i = 0; i < strip_num; i++)
        ws2811_fini(&ledstring[i]);

//  printf("LED Controller finished.\n");
    close(A0);
    close(A1);
    close(A2);

    int fd = open("/sys/class/gpio/unexport", O_WRONLY);
    if (fd == -1)
    {
	perror("Unable to open /sys/class/gpio/unexpect");
	exit(1);
    }
    
    if (write(fd, "23", 2) != 2){
        perror("Error writing to /sys/class/gpio/unexpect");
    	exit(1);
    }

    if (write(fd, "24", 2) != 2){
        perror("Error writing to /sys/class/gpio/unexpect");
    	exit(1);
    }

    if (write(fd, "25", 2) != 2){
        perror("Error writing to /sys/class/gpio/unexpect");
    	exit(1);
    }
}

void LEDController::delayMicroseconds (int delay_us)
{
	long int start_time;
	long int time_difference;
	struct timespec gettime_now;

	clock_gettime(CLOCK_REALTIME, &gettime_now);
	start_time = gettime_now.tv_nsec;		//Get nS value
	while (1)
	{
		clock_gettime(CLOCK_REALTIME, &gettime_now);
		time_difference = gettime_now.tv_nsec - start_time;
		if (time_difference < 0)
			time_difference += 1000000000;				//(Rolls over every 1 second)
		if (time_difference > (delay_us * 1000))		//Delay for # nS
			break;
	}
}
