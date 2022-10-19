#include "Pixel.h"

using namespace udd;

Pixel::Pixel() 
    : color(BLACK)
    , point(Point()) {
} 

Pixel::Pixel(int x, int y, Color color)
    : color(color)
    , point(Point(x,y)) {
}
