# MKPin

## Usage

### Import MKPin Library

```cpp
#include <MKPin.h>
```

### Create Pin

```cpp
Pin pin = Pin(13)
```

```cpp
Pin pin[] = {12,13}
```

### set Pin Mode

```cpp
pin.setInput();
pin.setOutput();
pin.setInputPullup();
pin.setInputPulldown();

pin.getMode(); // returns the pin mode (INPUT, OUTPUT, INPUT_PULLUP)
pin.setMode(<mode>); // sets the pin mode (INPUT, OUTPUT, INPUT_PULLUP)
```

### IO

```cpp
// > digitalWrite(<pin>, LOW);
// - pin = LOW;
// - pin.setState(LOW);
pin.setLow();

// > digitalWrite(<pin>, HIGH);
// - pin = HIGH;
// - pin.setState(HIGH);
pin.setHigh();

// - pin.toggle();
pin.toggleState();
// - pin.toggleState();
pin.toggle();

// > digitalWrite(<pin>, <value>);
// - pin = <value>;
// - pin.setState(<value>);
// - pin.value(<value>);
pin.setState(<value>);

// > digitalRead(<pin>)
// - pin.value();
pin.getStatus();
// > digitalRead(<pin>)
// - pin.getStatus();
pin.value();
// > digitalWrite(<pin>, <value>)
// - pin.setState(<value>);
pin.value(<value>);

// > analogRead(<pin>)
pin.getAnalog();
// > analogWrite(<pin>, <value>)
pin.setAnalog(<value>);

// > null
// - get pin output state
pin.getOutputState();
```

pin
getModeReg
getInputReg
getOutputReg
