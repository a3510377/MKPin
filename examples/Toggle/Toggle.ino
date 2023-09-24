#include <Arduino.h>
#include <MKPin.h>

Pin pin = Pin(13);

void setup() {
  // - pinMode(13, OUTPUT);
  // - pin.setMode(OUTPUT);
  pin.setOutput();
}

void loop() {
  // digitalWrite(digitalRead(13));
  // - pin.value(!pin.value());
  // - pin.setState(!pin.getState());
  pin.toggleState();

  delay(200);
}
