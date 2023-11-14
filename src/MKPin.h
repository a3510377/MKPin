#include <Arduino.h>

#pragma once

#define __SET_HIGH (*_out |= _bitMask)
#define __SET_LOW (*_out &= _bitNotMask)
#define __SET_TOGGLE (*_out ^= _bitMask)

#define __REG_IN (*_reg &= _bitNotMask)
#define __REG_OUT (*_reg |= _bitMask)

class Pin {
 public:
  /**
   * Default constructor
   */
  Pin() : Pin(0) {}

  Pin(uint8_t pin) : _pin(pin) {
    _bitMask = digitalPinToBitMask(pin);
    _bitNotMask = ~_bitMask;

    uint8_t port = digitalPinToPort(pin);
    _reg = portModeRegister(port);
    _in = portInputRegister(port);
    _out = portOutputRegister(port);
  }

  Pin(uint8_t pin, uint8_t bitMask, uint8_t timer, volatile uint8_t *reg,
      volatile uint8_t *in, volatile uint8_t *out)
      : _pin(pin),
        _bitMask(bitMask),
        _bitNotMask(~bitMask),
        _reg(reg),
        _in(in),
        _out(out) {}

  /**
   * Get the current state of the pin
   *
   * @return The current state of the pin
   */
  operator bool() const {
    return !!value();
  }

  /**
   * Set the pin output to state
   *
   * @param state pin state (HIGH, LOW)
   */
  Pin &operator=(uint8_t state) {
    setState(state);

    return *this;
  }

  /**
   * Set the pin mode to input
   */
  void setInput() {
    uint8_t oldSREG = SREG;
    cli();
    __REG_IN;
    __SET_LOW;
    SREG = oldSREG;
  }

  /**
   * Set the pin mode to output
   */
  void setOutput() {
    uint8_t oldSREG = SREG;
    cli();
    __REG_OUT;
    SREG = oldSREG;
  }

  /**
   * Set the pin mode to input pullup
   */
  void setInputPullup() {
    uint8_t oldSREG = SREG;
    cli();
    __REG_IN;
    __SET_HIGH;
    SREG = oldSREG;
  }

  /**
   * Set the pin mode to input pulldown
   */
  void setInputPulldown() {
    uint8_t oldSREG = SREG;
    cli();
    __REG_IN;
    __SET_LOW;
    SREG = oldSREG;
  }

  /**
   * Get pin mode
   *
   * @return mode (INPUT, OUTPUT, INPUT_PULLUP)
   */
  uint8_t getMode() const {
    // OUTPUT
    if (*_reg & _bitMask) {
      return OUTPUT;
    }

    // if output is HIGH is INPUT_PULLUP else only INPUT
    return getOutputState() ? INPUT_PULLUP : INPUT;
  }

  /**
   * Set the pin mode
   *
   * @param mode (INPUT, OUTPUT, INPUT_PULLUP)
   */
  void setMode(uint8_t mode) {
    if (mode == INPUT) setInput();
    else if (mode == INPUT_PULLUP) setInputPullup();
    else setOutput();
  }

  /**
   * Set the pin output to LOW
   */
  void setLow() {
    uint8_t oldSREG = SREG;
    cli();
    __SET_LOW;
    SREG = oldSREG;
  }

  /**
   * Set the pin output to HIGH
   */
  void setHigh() {
    uint8_t oldSREG = SREG;
    cli();
    __SET_HIGH;
    SREG = oldSREG;
  }

  /**
   * Toggle the pin output (HIGH -> LOW, LOW -> HIGH)
   */
  void toggleState() {
    uint8_t oldSREG = SREG;
    cli();
    __SET_TOGGLE;
    SREG = oldSREG;
  }

  /**
   * Toggle the pin output (HIGH -> LOW, LOW -> HIGH), equivalent to
   * toggleState()
   */
  inline void toggle() {
    toggleState();
  }

  /**
   * Set the pin output to state
   *
   * @param state pin state (HIGH, LOW)
   */
  inline void setState(uint8_t state) {
    if (state) setHigh();
    else setLow();
  }

  /**
   * Get the pin input state
   *
   * @return pin state (HIGH, LOW)
   */
  inline uint8_t getState() const {
    return *_in & _bitMask ? HIGH : LOW;
  }

  /**
   * Get the pin input state, equivalent to getState()
   *
   * @return pin state (HIGH, LOW)
   */
  inline uint8_t value() const {
    return getState();
  }

  /**
   * Get the pin input state, equivalent to setState()
   *
   * @param state pin state (HIGH, LOW)
   */
  inline void value(uint8_t state) {
    setState(state);
  }

  /**
   * Get the pin analog input value, equivalent to analogRead()
   *
   * @return pin analog input value (0~1023)
   */
  inline int getAnalog() const {
    return analogRead(_pin);
  }

  /**
   * Get the pin output state, equivalent to analogWrite()
   *
   * @param state pin output state (0-255)
   */
  inline void setAnalog(int value) {
    analogWrite(_pin, value);
  }

  /**
   * Get the pin output state
   *
   * @return pin state (HIGH, LOW)
   */
  inline uint8_t getOutputState() const {
    return *_out & _bitMask ? HIGH : LOW;
  }

  /**
   * Get the pin number
   *
   * @return the pin number
   */
  inline uint8_t pin() const {
    return _pin;
  }

  /**
   * Get the pin Mode Register
   */
  inline volatile uint8_t *getModeReg() const {
    return _reg;
  }
  /**
   * Get the pin Input Register
   */
  inline volatile uint8_t *getInputReg() const {
    return _in;
  }
  /**
   * Get the pin Output Register
   */
  inline volatile uint8_t *getOutputReg() const {
    return _out;
  }

 protected:
  uint8_t _pin, _bitMask, _bitNotMask;
  volatile uint8_t *_reg, *_in, *_out;
};

#undef __SET_HIGH
#undef __SET_LOW
#undef __SET_TOGGLE

#undef __REG_IN
#undef __REG_OUT
