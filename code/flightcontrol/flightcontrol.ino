int buttonPins[]    = {0,   2,  3,  25};
int buttonButtons[] = {11,  14, 15, 16};

int togglePins[]    = {27,  1,  24, 23};
int toggleButtons[] = {13,  12, 17, 18};
int toggleStates[]  = {0,   0,  0,  0};

void setup() {  
  // Assign button pins to INPUT_PULLUP
  int i;
  for (i = 0; i < 4; i = i + 1) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
  
  // Assign toggle pins to INPUT
  int j;
  for (j = 0; j < 4; j = j + 1) {
    // Control Mode needs resistor enabled.
    if (togglePins[j] == 27) {
      pinMode(togglePins[j], INPUT_PULLUP);
    } else {
      pinMode(togglePins[j], INPUT);
    }
  }
}

void loop() {
  
  // Read buttons
  int i;
  for (i = 0; i < 4; i = i + 1) {
    Joystick.button(buttonButtons[i], !digitalRead(buttonPins[i]));
  }
  
  // Read toggle switches
  int j;
  for (j = 0; j < 4; j = j + 1) {
    int currentState = digitalRead(togglePins[j]);
    if (toggleButtons[j] == 12) {
      if (currentState == toggleStates[j]) {
        continue;
      }
      // Staging Lock
      Keyboard.begin();
      Keyboard.press(KEY_LEFT_ALT);
      delay(1);
      Keyboard.press('l');
      delay(1);
      Keyboard.release('l');
      delay(1);
      Keyboard.release(KEY_LEFT_ALT);
      Keyboard.end();
    } else  if (toggleButtons[j] == 13) {
      // Control Mode
      if (currentState == toggleStates[j]) {
        continue;
      }
      Keyboard.begin();
      if (currentState == 0) {
        // Flight
        Keyboard.press('y');
        delay(1);
        Keyboard.release('y');
      } else if (currentState == 1) {
        // Docking
        Keyboard.press(KEY_DELETE);
        delay(1);
        Keyboard.release(KEY_DELETE);
      }
      Keyboard.end();
    } else {
//      if ¬
      Joystick.button(toggleButtons[j], (currentState != toggleStates[j]));
    }
    toggleStates[j] = currentState;
  }
  
  // Right Joystick
  Joystick.X(analogRead(0));
  Joystick.Y(analogRead(1));
  Joystick.Z(analogRead(2));

  // Left Joystick
  Joystick.Zrotate(analogRead(3));
  Joystick.sliderRight(analogRead(4));
  Joystick.button(31, (analogRead(5) < 341));
  Joystick.button(32, (analogRead(5) > 680));

  // Throttle
  int throttleAmount = analogRead(6);
  if (throttleAmount < 40) {
    throttleAmount = 0;
  } else if (throttleAmount > 1010) {
    throttleAmount = 1023;
  }
  Joystick.sliderLeft(throttleAmount);
  
  delay(5);
}

