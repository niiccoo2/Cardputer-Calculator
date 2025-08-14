#include <M5Unified.h>
#include "M5Cardputer.h"
#include "USB.h"
#include "USBHIDKeyboard.h"

USBHIDKeyboard Keyboard;

void setup() {
    auto cfg = M5.config();
    M5Cardputer.begin(cfg, true);
    M5Cardputer.Display.setRotation(1);
    M5Cardputer.Display.setTextColor(GREEN);
    M5Cardputer.Display.setTextDatum(middle_center);
    M5Cardputer.Display.setTextFont(&fonts::Orbitron_Light_24);
    M5Cardputer.Display.setTextSize(1);
    M5Cardputer.Display.drawString("USB Keyboard",
                                   M5Cardputer.Display.width() / 2,
                                   M5Cardputer.Display.height() / 2);
    Keyboard.begin();
    USB.begin();
}

void loop() {
    M5Cardputer.update();
    // max press 3 button at the same time
    if (M5Cardputer.Keyboard.isChange()) {
        if (M5Cardputer.Keyboard.isPressed()) {
            Keyboard_Class::KeysState status = M5Cardputer.Keyboard.keysState();
            // for (auto i : status.word) {
            //     Keyboard.press(i);
            // }
            KeyReport report = {0};
            report.modifiers = status.modifiers;
            uint8_t index    = 0;
            for (auto i : status.hid_keys) {
                report.keys[index] = i;
                index++;
                if (index > 5) {
                    index = 5;
                }
            }
            Keyboard.sendReport(&report);
            Keyboard.releaseAll();

            // only text for display
            String keyStr = "";
            for (auto i : status.word) {
                if (keyStr != "") {
                    keyStr = keyStr + "+" + i;
                } else {
                    keyStr += i;
                }
            }

            if (keyStr.length() > 0) {
                M5Cardputer.Display.clear();
                M5Cardputer.Display.drawString(
                    keyStr, M5Cardputer.Display.width() / 2,
                    M5Cardputer.Display.height() / 2);
            }

        } else {
            M5Cardputer.Display.clear();
            M5Cardputer.Display.drawString("USB Keyboard",
                                           M5Cardputer.Display.width() / 2,
                                           M5Cardputer.Display.height() / 2);
        }
    }
}

// uint32_t count;


// void setup() { // This is run once at startup

//   auto cfg = M5.config(); // Assign a structure for initializing M5Stack
//   // If config is to be set, set it here
//   // Example.
//   // cfg.external_spk = true;

//   M5.begin(cfg);

//   M5.Display.setTextSize(3);            // change text size
//   M5.Display.print("Hello World!!!") ;  // display Hello World! and one line is displayed on the screen
//   count = 0;                            // initialize count

// }

// void loop() { // Runs and keeps running after setup

//   M5.Display.setCursor(0, 40);             // set character drawing coordinates (cursor position)
//   M5.Display.printf("COUNT: %d\n", count); // display count on screen
//   count++;                              // increase count by 1
//   delay(1000);                          // wait 1 second(1,000msec)

// } 