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
    M5Cardputer.Display.drawString("Enter equation",
                                   M5Cardputer.Display.width() / 2,
                                   M5Cardputer.Display.height() / 2);
    
}

void waitForEnter() {
  while (true) {
    if (M5Cardputer.Keyboard.isChange()) {
      if (M5Cardputer.Keyboard.isPressed()) {
          Keyboard_Class::KeysState status = M5Cardputer.Keyboard.keysState();
          if (status.enter) {
            return;
          }
      }
    }
  }
}

String getUserInput() {
    M5Cardputer.Display.drawString("Enter equation",
        M5Cardputer.Display.width() / 2,
        M5Cardputer.Display.height() / 2);
    
    String equation = "";
    while (true)
      {
          M5Cardputer.update();
          
          
          if (M5Cardputer.Keyboard.isChange()) {
              if (M5Cardputer.Keyboard.isPressed()) {
                  Keyboard_Class::KeysState status = M5Cardputer.Keyboard.keysState();

                  if (status.enter) {
                    return equation;
                  }

                  for (auto i : status.word) {
                      if (equation.length() >= 10) { // Use >= becuase it checks BEFORE it adds a new char
                        equation = equation; // Do nothing so max input is 10
                      } else if (equation != "") {
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
          }
      } 
}

void loop() {
    String equation = "Got: " + getUserInput();
    M5Cardputer.Display.clear();
    M5Cardputer.Display.drawString(
          equation, M5Cardputer.Display.width() / 2,
          M5Cardputer.Display.height() / 2);
}