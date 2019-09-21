//
// Created by Stepan on 26.08.2019.
//

#ifndef BLYNKLAMP_RUNMODE_H
#define BLYNKLAMP_RUNMODE_H

extern "C" {
    #include "user_interface.h"
}

#include <BlynkSimpleEsp8266.h>
#include "Settings.h"

void enterRunMode() {
    if (WiFi.status() != WL_CONNECTED) {
        DEBUG_PRINT("WiFi connection missed")
        BlynkState::set(MODE_WAIT_CONFIG);
    }
    Blynk.run();
}

#endif //BLYNKLAMP_RUNMODE_H
