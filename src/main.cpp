#include <Arduino.h>
#include <IRsend.h>
#include "IRProtocol.h"

#define BLYNK_PRINT Serial // Enables Serial Monitor

#include "BlynkProvisioning.h"

String serialData;
unsigned long irCode;

IRsend irsend(D2);

void setup() {
    BLYNK_PRINT.begin(115200);
    BlynkProvisioning.begin();

    pinMode(D2, OUTPUT);
}

/**
 * Performs when user write value to V20. Set reset state if writen value is 1.
 * (Blynk and WIFI configuration will be reset in BlynkProvisioning.run() )
 *
 */
BLYNK_WRITE(V20) {
    bool isVirtualPinReset = param.asInt() == 1;
    if (isVirtualPinReset) {
        BlynkState::set(MODE_RESET_CONFIG);
    }
}

BLYNK_WRITE(V0) {
    uint32_t irCommand = rgbLampCommand(param.asInt() == 1 ? RGB_LAMP_ON : RGB_LAMP_OFF); 
    irsend.sendNEC(irCommand, 32);
}

BLYNK_WRITE(V1) {
    uint8 r = (uint8)(param[0].asInt() != 0) << 2u;
    uint8 g = (uint8)(param[1].asInt() != 0) << 1u;
    uint8 b = (uint8)(param[2].asInt() != 0) << 0u;
    uint8 rgb = r | g | b;
    irsend.sendNEC(rgbLampCommand((RGBLampCommandType)rgb), 32);
}

BLYNK_CONNECTED() {
    Blynk.syncAll();
}

void loop() {
    BlynkProvisioning.run();

//    serialData += Serial.readStringUntil('\n');
//
//    uint8 command = 0;
//
//    while (serialData.length() > 0) {
//        if (serialData == "on")       command = 0b11100000;
//        else if (serialData == "off") command = 0b01100000;
//        else if (serialData == "r")   command = 0b10010000;
//        else if (serialData == "g")   command = 0b00010000;
//        else if (serialData == "w")   command = 0b11010000;
//        else if (serialData == "b")   command = 0b10100000;
//        else if (serialData.startsWith("0b")) {
//            for (uint32_t i = 2; i < serialData.length(); ++i) {
//                command = (command << 1u) | (serialData[i] == '1');
//            }
//            command <<= 3u;
//        }
//        serialData.remove(0, serialData.length());
//    }
//
//    if (command != 0) {
//        irsend.sendNEC(genIRCommand(command), 32);
//        delay(40);
//    }
}
