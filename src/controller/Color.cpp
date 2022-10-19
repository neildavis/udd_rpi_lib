#include "Color.h"
#include <string.h>
#include <stdio.h>

namespace udd {

    udd::Color ColorHex(const char* hexbytes) {
        udd::Color ret = 0;
        char buf[3];
        int intensity;
        int offset = 0;
        if (hexbytes[0] == '#') {
            offset = 1;
        }

        // Red
        if (strlen(&hexbytes[offset]) == 5) {
            memset(buf, 0, sizeof(buf));
            strncpy(buf, &hexbytes[offset], 1);
            sscanf(buf, "%x", &intensity);
            ret |= (intensity & 0xff);
            offset += 1;
        } else {
            memset(buf, 0, sizeof(buf));
            strncpy(buf, &hexbytes[offset], 2);
            sscanf(buf, "%x", &intensity);
            ret |= (intensity & 0xff);
            offset += 2;
        }    
        // Green
        memset(buf, 0, sizeof(buf));
        strncpy(buf, &hexbytes[offset], 2);
        sscanf(buf, "%x", &intensity);
        ret |= ((intensity & 0xff) << 8);
        // Blue
        offset += 2;
        memset(buf, 0, sizeof(buf));
        strncpy(buf, &hexbytes[offset], 2);
        sscanf(buf, "%x", &intensity);
        ret |= ((intensity & 0xff) << 16);
        // Opacity
        if (strlen(hexbytes) > 7) {
            offset += 2;
            memset(buf, 0, sizeof(buf));
            strncpy(buf, &hexbytes[offset], 2);
            sscanf(buf, "%x", &intensity);
            ret |= ((intensity & 0xff) << 24);
        }
        else {
            ret |= 0xff000000;  // max opacity
        }
        return ret;
    }

    void ColorPrint(Color color) {
        uint8_t r = ColorRed(color), g = ColorGreen(color), b = ColorBlue(color);
        printf("color::print: 0x%02x%02x%02x  (%3d,%3d,%3d)\n", r, g, b, r, g, b);
    }

    // Original 8
    const udd::Color BLACK             = ColorRGB(0,     0,   0);
    const udd::Color RED               = ColorRGB(255,   0,   0);
    const udd::Color GREEN             = ColorRGB(0,   255,   0);
    const udd::Color BLUE              = ColorRGB(0,     0, 255);
    const udd::Color YELLOW            = ColorRGB(255, 255,   0);
    const udd::Color MAGENTA           = ColorRGB(255,   0, 255);
    const udd::Color CYAN              = ColorRGB(0,   255, 255);
    const udd::Color WHITE             = ColorRGB(255, 255, 255);
    // extended colors
    const udd::Color GRAY              = ColorRGB(128, 128, 128);
    const udd::Color BROWN             = ColorRGB(165,  42,  42);
    const udd::Color ORANGE            = ColorRGB(255, 128,   0);
    const udd::Color DARK_RED          = ColorRGB(128,   0,   0);
    const udd::Color DARK_GREEN        = ColorRGB(0,   128,   0);
    const udd::Color DARK_BLUE         = ColorRGB(0,     0, 128);
    const udd::Color LIGHT_BLUE        = ColorRGB(204, 228, 255);
    const udd::Color LIGHT_GRAY        = ColorRGB(224, 224, 224);
    const udd::Color DARK_GRAY_BLUE    = ColorRGB(0,   51, 102);

}