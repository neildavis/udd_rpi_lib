#include "DisplayST7789.h"


namespace udd {

    DisplayST7789R::DisplayST7789R() : Display() {}

    void DisplayST7789R::init() {
        reset();

        writeCommand(0x36); // MADCTL
        writeData(0x00);

        writeCommand(0x3A); // COLMOD
        writeData(0x05);

        writeCommand(0x21); // INVON

        writeCommand(0x2A); // CASET
        writeData(0x00);
        writeData(0x00);
        writeData(0x01);
        writeData(0x3F);

        writeCommand(0x2B); // RASET
        writeData(0x00);
        writeData(0x00);
        writeData(0x00);
        writeData(0xEF);

        writeCommand(0xB2); // FRMCTR2 in Idle mode(8-colors) ???
        writeData(0x0C);
        writeData(0x0C);
        writeData(0x00);
        writeData(0x33);
        writeData(0x33);

        writeCommand(0xB7); // GCTRL
        writeData(0x35);

        writeCommand(0xBB); // VCOMS
        writeData(0x1F);

        writeCommand(0xC0); // PWCTR1
        writeData(0x2C);

        writeCommand(0xC2); // PWCTR3
        writeData(0x01);

        writeCommand(0xC3); // PWCTR4
        writeData(0x12);

        writeCommand(0xC4); // PWCTR5
        writeData(0x20);

        writeCommand(0xC6); // FRCTR2
        writeData(0x0F);

        writeCommand(0xD0); // PWCTRL1
        writeData(0xA4);
        writeData(0xA1);

        writeCommand(0xE0); // PVGAMCTRL
        writeData(0xD0);
        writeData(0x08);
        writeData(0x11);
        writeData(0x08);
        writeData(0x0C);
        writeData(0x15);
        writeData(0x39);
        writeData(0x33);
        writeData(0x50);
        writeData(0x36);
        writeData(0x13);
        writeData(0x14);
        writeData(0x29);
        writeData(0x2D);

        writeCommand(0xE1); // NVGAMCTRL
        writeData(0xD0);
        writeData(0x08);
        writeData(0x10);
        writeData(0x08);
        writeData(0x06);
        writeData(0x06);
        writeData(0x39);
        writeData(0x44);
        writeData(0x51);
        writeData(0x0B);
        writeData(0x16);
        writeData(0x14);
        writeData(0x2F);
        writeData(0x31);

        writeCommand(0x21); // INVON (Again ???)

        writeCommand(0x11); // SLPOUT

        writeCommand(0x29); // DISPON
    }






}