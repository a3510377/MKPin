#include <Arduino.h>
#include <MKPin.h>

Pin pin = Pin(13);

void setup() {
  // - pinMode(13, OUTPUT);
  // - pin.setMode(OUTPUT);
  pin.setOutput();
}

void loop() {
  for (int i = 0; i <= 255; i++) {
    // analogWrite(i);
    pin.setAnalog(i);
    delay(200);
  }
}
