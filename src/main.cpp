//#include <M5Unified.h>
#include "M5Cardputer.h"
#include "USBHIDKeyboard.h"

USBHIDKeyboard Keyboard;

void setup() {
    auto cfg = M5.config();
    M5Cardputer.begin(cfg, true);
    M5Cardputer.Display.setRotation(1);
    M5Cardputer.Display.setTextColor(GREEN);
    M5Cardputer.Display.setTextDatum(middle_center);
    M5Cardputer.Display.setFont(&fonts::Orbitron_Light_24);
    M5Cardputer.Display.setTextSize(1);
    M5Cardputer.Display.drawString("USB Keyboard",
                                   M5Cardputer.Display.width() / 2,
                                   M5Cardputer.Display.height() / 2);
}

String equation = "";

void loop() {
    M5Cardputer.update();
    
    if (M5Cardputer.Keyboard.isChange()) {
        if (M5Cardputer.Keyboard.isPressed()) {
            Keyboard_Class::KeysState status = M5Cardputer.Keyboard.keysState();
          
            for (auto i : status.word) {
                if (equation != "") {
                    equation = equation + i;
                } else {
                    equation += i;
                }
            }

            M5Cardputer.Display.clear();
            M5Cardputer.Display.drawString(
                equation, M5Cardputer.Display.width() / 2,
                M5Cardputer.Display.height() / 2);
            
          }
        // } else {
        //     M5Cardputer.Display.clear();
        //     M5Cardputer.Display.drawString("USB Keyboard",
        //                                    M5Cardputer.Display.width() / 2,
        //                                    M5Cardputer.Display.height() / 2);
        // }
    }
}