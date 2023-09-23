#include <Arduino.h>
#include <MKPin.h>

Pin pins[] = {2, 4, 6, 8};
int pinsCount = sizeof(pins) / sizeof(Pin);

void setup() {
  for (int i = 0; i < pinsCount; i++) {
    Pin pin = pins[i];

    pin.setOutput();
    if (i % 2 == 0) {
      pin.setHigh();
    }
  }
}

void loop() {
  for (int i = 0; i < pinsCount; i++) {
    // - pins[i].toggleState()
    pins[i].toggle();
    delay(200);
  }
}
