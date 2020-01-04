#include <wiringPi.h>
#include <stdio.h>
#include <Image.h>
#include <sys/time.h>
#include <math.h>
#include <fonts.h>
#include <pthread.h>

#include <Display.h>
#include <DisplayST7789.h>
#include <DisplayST7735R.h>


using namespace udd;

DisplayConfigruation d1Config;
DisplayST7789R d1;

DisplayConfigruation d2Config;
DisplayST7735R d2;


unsigned long long currentTimeMillis();


long long lastTime = currentTimeMillis();
long long lastSecond;
int fps, lastFPS = 0;


unsigned long long currentTimeMillis() {
    struct timeval currentTime;
    gettimeofday(&currentTime, NULL);

    return
        (unsigned long long)(currentTime.tv_sec) * 1000 +
        (unsigned long long)(currentTime.tv_usec) / 1000;
}


void drawSine(Image image, float offset, float speed, int maxX, int maxY, float waveHeight, Color color, int width) {
    bool first = true;;
    int lx = -1, ly = -1;
    double vx = 0;
    float vmax = 2;
    for (int x = 0; x < maxX; ++x) {
        vx = (speed * offset) + (6 * PI) * x / maxX;
        int y = (maxY / 2) - sin(vx) * (maxY * waveHeight / 2);
        if (first) {
            first = false;
            continue;
        }
        else {
            image.drawLine(lx, ly, x, y, color, SOLID, width);
        }
        lx = x;
        ly = y;
    }
}


bool frame(int frameCount, long long start) {
    long long now = currentTimeMillis();
    float refVoltage = 5;

    long long second = now / 1000;
    if (lastSecond < 0) lastSecond = second;

    if (lastSecond != second) {
        lastFPS = fps;
        fps = 0;
        lastSecond = second;
    }
    ++fps;

    int imageWidth  = d1Config.height;
    int imageHeight = d1Config.width;

    Image image = Image(imageWidth, imageHeight, BLACK);

    int minX=0, minY = 0;
    int maxX = imageWidth-1;
    int maxY = imageHeight-1;
    int midY = minY + (maxY - minY) / 2;


    image.drawRectangle(minX, minY, maxX, maxY, WHITE, NONE, DOTTED, 1);

    // line markers
    for (int v = 1; v < refVoltage; ++v) {
        int y = maxY - ((v / refVoltage) * maxY);
        image.drawLine(1, y, maxX, y, BROWN, SOLID, 1);
    }


    image.drawCircle(maxX / 2, maxY / 2, maxY / 4, GRAY,        NONE,  DOTTED, 3);
    image.drawCircle(maxX / 2, maxY / 2, maxY / 4, LIGHT_GRAY,  NONE,  SOLID,  2);
    image.drawCircle(maxX / 2, maxY / 2, maxY / 4, WHITE,       NONE,  SOLID,  1);


    Color lineColor[9] = {
        //1      2     3        4      5         6        7       8    
        YELLOW, GREEN, MAGENTA, CYAN,  ORANGE,   RED, LIGHT_BLUE, LIGHT_GRAY
    };

    for (int line = 0; line < 4; ++line) {
        drawSine(image, frameCount + (4 - line) * (PI), .25, maxX, maxY, .65, lineColor[line], (line == 0) ? 3 : 2);
    }


    char message[32];
    sprintf(message, "%4.2f", refVoltage);
    image.drawText(minX + 1, minY + 1, message, &Font24, DARK_GRAY_BLUE, WHITE);

    sprintf(message, "%d-fps", lastFPS);
    image.drawText(maxX - (17 * strlen(message)) - 1, minY + 1, message, &Font24, BLACK, WHITE);

    d1.showImage(image,DEGREE_270);


    image.close();

    return ((now - start) < 6000);
}

void *d2ImageDemo(void *) {

    while (true) {
        d2.clear(WHITE);
        delay(100);
        d2.clear(RED);
        delay(100);
        d2.clear(GREEN);
        delay(100);
        d2.clear(BLUE);
        delay(100);
        d2.clear(BLACK);

        Image d2Image = Image(d2Config.width, d2Config.height, BLACK);

        Color pallet[10] = {
            RED, YELLOW, GREEN, BLUE, MAGENTA, CYAN
        };

        for (int i = 0; i < 6; ++i) {
            d2Image.drawRectangle(20 + i * 10, 0, i * 10 + 30, 128, pallet[i], FILL, SOLID, 1);
        }
        d2Image.drawText(0, 0, "Hello World", &Font12, BLACK, WHITE);

        d2Image.drawRectangle(0, 0, d2Config.width - 1, d2Config.height - 1, WHITE, NONE, SOLID, 1);

        d2.showImage(d2Image, DEGREE_90);

        delay(2000);
        d2Image.loadBMP("../images/MotorBike-128x128.bmp", 0, 0);
        d2.showImage(d2Image, DEGREE_90);

        delay(4000);
        d2Image.close();
    }

}

int main(void)
{
	wiringPiSetup();

    // just incase there's somehting attached to these pins
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
    digitalWrite(10, HIGH);
    digitalWrite(11, HIGH);


    d2Config.width    = 240;
    d2Config.height   = 320;
    d1Config.CS       = 24;
    d1Config.DC       = 25;
    d1Config.RST      = 26;
    d1Config.BLK      = 7;
    d1Config.spiSpeed = 65000000;
         
    d1.openDisplay(d1Config);
    d1.printConfiguration();
    d1.clear(BLACK);
    d1.pause();

    
    printf("--------------------------------------------\n");
    printf("-----d2 config------------------------------\n");

    

    d2Config.width    = 128;
    d2Config.height   = 128;
    d2Config.CS       = 21;
    d2Config.DC       = 22;
    d2Config.RST      = 23;
    d2Config.xOffset = 2;
    d2Config.yOffset = 1;
    d2Config.spiSpeed = 35000000;

    d2.openDisplay(d2Config);
    d2.printConfiguration();
    d2.init();
    d2.pause();

    
    pthread_t thread1;
    const char message1[256] = "d2 image demo";
    pthread_create(&thread1, NULL, d2ImageDemo, (void*)message1);
    
// ---------------
    d1.resume();
    d1.clear(WHITE);
    delay(10);
    d1.clear(RED);
    delay(10);
    d1.clear(BLUE);
    delay(10);
    d1.clear(GREEN);
    delay(10);
    d1.clear(BLACK);



    Image image = Image(320, 240, BLACK);
    image.loadBMP("../images/BlueAngle4-320x240.bmp", 0, 0);

    long count = 0;
    while (true) {
        
        d1.showImage(image, DEGREE_270);

        delay(1000);

        long long start = currentTimeMillis();

        while (frame(++count, start));
        
    }


    return 0;
}