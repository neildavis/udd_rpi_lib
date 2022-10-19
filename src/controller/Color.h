#pragma once

#include "inttypes.h"

namespace udd {
    typedef uint32_t Color;

    inline Color ColorRGBA(uint8_t red, uint8_t green, uint8_t blue, uint8_t opacity) {
        return (uint32_t)red | (((uint32_t)green) << 8) | (((uint32_t)blue) << 16) | (((uint32_t)opacity) << 24);
    }

    inline Color ColorRGB(uint8_t red, uint8_t green, uint8_t blue) {
        return ColorRGBA(red, green, blue, 0xff);
    }

    inline uint8_t ColorRed(Color color) {
        return (uint8_t)(color & 0xff);
    }

    inline uint8_t ColorGreen(Color color) {
        return (uint8_t)(((color & 0xff00) >> 8));
    }

    inline uint8_t ColorBlue(Color color) {
        return (uint8_t)(((color & 0xff0000) >> 16));
    }

    inline uint8_t ColorOpacity(Color color) {
        return (uint8_t)(((color & 0xff000000) >> 24));
    }

    Color ColorHex(const char* hexbytes);
    void ColorPrint(Color color);

    // original 8
    extern const Color BLACK;
    extern const Color RED;
    extern const Color GREEN;
    extern const Color BLUE;
    extern const Color YELLOW;
    extern const Color MAGENTA;
    extern const Color CYAN;
    extern const Color WHITE;

    extern const Color GRAY;
    extern const Color BROWN;
    extern const Color ORANGE;

    extern const Color LIGHT_BLUE;
    extern const Color LIGHT_GRAY;

    extern const Color DARK_BLUE;
    extern const Color DARK_RED;
    extern const Color DARK_GREEN;

    extern const Color DARK_GRAY_BLUE;
}

