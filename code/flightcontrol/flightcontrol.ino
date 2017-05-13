int buttonPins[] = {10};
int buttonButtons[] = {1};

int togglePins[] = {11, 12};
int toggleButtons[] = {2, 3};
int toggleStates[] = {0, 0};

void setup() {
  // Assign button pins to INPUT_PULLUP
  int i;
  for (i = 0; i < 1; i = i + 1) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
  
  // Assign toggle pins to INPUT
  int j;
  for (j = 0; j < 1; j = j + 1) {
    pinMode(togglePins[j], INPUT);
  }
}

void loop() {
  // Read Sync control and return if not enabled.
  // if (!digitalRead(11)) {
  //   delay(50);
  //   return;
  // }
  
  // Read buttons
  int i;
  for (i = 0; i < 1; i = i + 1) {
    Joystick.button(buttonButtons[i], !digitalRead(buttonPins[i]));
  }
  
  // Read toggle switches
  int j;
  for (j = 0; j < 1; j = j + 1) {
    int currentState = digitalRead(togglePins[j]);
    Joystick.button(toggleButtons[j], (currentState != toggleStates[j]));
    toggleStates[j] = currentState;
  }
  
  // read analog inputs and set X-Y position
  // Joystick.Y(analogRead(0));
  // Joystick.X(analogRead(1));
  // Joystick.Z(analogRead(2));
  // Joystick.sliderLeft(analogRead(4));
  delay(50);
}

