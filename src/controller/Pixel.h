#pragma once


#include "Color.h"
#include "Point.h"

namespace udd {
    class Pixel {
    public:
        Color color;
        Point point;

        Pixel();
        Pixel(int x, int y, Color color);
    };
}
