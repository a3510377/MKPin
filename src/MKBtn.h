#include <Arduino.h>

#pragma once

class MKBtn {
 public:
  MKBtn() : MKBtn(0) {}

  MKBtn(uint8_t pin) : MKBtn(pin, INPUT_PULLUP) {}

  MKBtn(uint8_t pin, uint8_t mode) : _pin(pin) {
    _port = digitalPinToPort(pin);
    _in = portInputRegister(_port);
    _bitMask = digitalPinToBitMask(pin);

    pinMode(_port, mode);
  }

 private:
  uint8_t _pin, _port, _bitMask;
  volatile uint8_t *_in;
  void (*_callback)(void);

  inline uint8_t _state() const {
    return *_in & _bitMask ? HIGH : LOW;
  }
};
