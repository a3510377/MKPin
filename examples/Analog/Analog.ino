#include <Arduino.h>
#include <MKPin.h>

Pin pin = Pin(13);

void setup() {
  // - pinMode(13, INPUT);
  // - pin.setMode(INPUT);
  pin.setInput();
}

void loop() {
  // analogRead();
  Serial.println(pin.getAnalog());

  delay(200);
}
