//
// Created by Stepan on 21.09.2019.
//

#ifndef IRCONTROLRGB_IRPROTOCOL_H
#define IRCONTROLRGB_IRPROTOCOL_H

#include <cstdint>

enum RGBLampCommandType {
    RGB_LAMP_RED        = 0b100,
    RGB_LAMP_GREEN      = 0b010,
    RGB_LAMP_BLUE       = 0b001,
    RGB_LAMP_RED_BLUE   = RGB_LAMP_RED   | RGB_LAMP_BLUE,
    RGB_LAMP_RED_GREEN  = RGB_LAMP_RED   | RGB_LAMP_GREEN,
    RGB_LAMP_GREEN_BLUE = RGB_LAMP_GREEN | RGB_LAMP_BLUE,
    RGB_LAMP_WHITE      = RGB_LAMP_RED   | RGB_LAMP_GREEN | RGB_LAMP_BLUE,

    RGB_LAMP_OFF   = 0b10000,
    RGB_LAMP_ON
};

inline uint32_t genIRCommand(uint8_t command) {
    return (0x00FFU << 16U) + (command << 8U) + (command ^ 0xFFU);
}

uint32_t rgbLampCommand(RGBLampCommandType type) {
    uint8_t command = 0;
    switch (type) {
        case RGB_LAMP_OFF:          command = 0b01100000; break;
        case RGB_LAMP_ON:           command = 0b11100000; break;
        case RGB_LAMP_RED:          command = 0b10010000; break;
        case RGB_LAMP_GREEN:        command = 0b00010000; break;
        case RGB_LAMP_BLUE:         command = 0b01010000; break;
        case RGB_LAMP_RED_GREEN:    command = 0b10110000; break;
        case RGB_LAMP_GREEN_BLUE:   command = 0b01110000; break;
        case RGB_LAMP_RED_BLUE:     command = 0b01001000; break;
        case RGB_LAMP_WHITE:        command = 0b11010000; break;
    }
    return genIRCommand(command);
}

#endif //IRCONTROLRGB_IRPROTOCOL_H
