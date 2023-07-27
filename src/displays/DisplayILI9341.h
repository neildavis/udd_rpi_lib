#pragma once
#include "Display.h"

namespace udd {

    class DisplayILI9341 : public Display {
    public:
        DisplayILI9341();

        void init() override;


    };
}
