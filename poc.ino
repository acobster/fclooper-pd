#include <Bounce2.h>

const int channel = 9;

const int LED = 14;
const int POT = 15;
const int DEBOUNCE_INTERVAL = 55;

int level;

Bounce buttonC = Bounce();
Bounce buttonD = Bounce();
Bounce buttonE = Bounce();
Bounce buttonF = Bounce();

void setup() {
  buttonC.attach(1);
  buttonD.attach(2);
  buttonE.attach(3);
  buttonF.attach(4);

  buttonC.interval(DEBOUNCE_INTERVAL);
  buttonD.interval(DEBOUNCE_INTERVAL);
  buttonE.interval(DEBOUNCE_INTERVAL);
  buttonF.interval(DEBOUNCE_INTERVAL);

  pinMode(LED, OUTPUT);
  pinMode(POT, INPUT);

  // Activate pullup resistors
  pinMode(1, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);

  Serial.begin(38400); // open serial port
  
  // assign incoming MIDI note data to callback function
  usbMIDI.setHandleNoteOn(OnNoteOn);
  usbMIDI.setHandleNoteOff(OnNoteOff);
  Serial.println("setup ran");
}

void loop() {
  // get the volume level
  level = analogRead(POT);
  // do something w/ level...

  buttonC.update();
  buttonD.update();
  buttonE.update();
  buttonF.update();

  usbMIDI.read();

  if (buttonC.fell()) {
    usbMIDI.sendControlChange(1, 127, channel);
    analogWrite(LED, HIGH); // 
  }
  if (buttonD.fell()) {
    usbMIDI.sendControlChange(2, 127, channel);
    analogWrite(LED, HIGH);
  }
  if (buttonE.fell()) {
    usbMIDI.sendControlChange(3, 127, channel);
  }
  if (buttonF.fell()) {
    usbMIDI.sendControlChange(4, 127, channel);
  }

  if (buttonC.rose()) {
    usbMIDI.sendControlChange(1, 0, channel);
    Serial.println("Played a C");
    analogWrite(LED, LOW);
  }
  if (buttonD.rose()) {
    usbMIDI.sendControlChange(2, 0, channel);
    Serial.println("Played a D");
    analogWrite(LED, LOW);
  }
  if (buttonE.rose()) {
    usbMIDI.sendControlChange(3, 0, channel);
    Serial.println("Played an E");
  }
  if (buttonF.rose()) {
    usbMIDI.sendControlChange(4, 0, channel);
    Serial.println("Played an F");
  }
}


// note handling
void OnNoteOn(byte channel, byte note, byte velocity) {
  Serial.println("note on");
}

void OnNoteOff(byte channel, byte note, byte velocity) {
  Serial.println("note off");
}


