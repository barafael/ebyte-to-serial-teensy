/*
  How to connect an EBYTE transceiver with a Teensy 3.2.
  It connects the EByte serial to Serial1 (bidirectional).

  Connections
  Module      Teensy
  M0          2
  M1          3
  Rx          1 (This is the MCU Tx lined)
  Tx          0 (This is the MCU Rx line)
  Aux         4
  Vcc         3v3
  Gnd         Gnd
*/

#include "EBYTE.h"

#define ESerial Serial1

#define PIN_M0 2
#define PIN_M1 3
#define PIN_AX 4

EBYTE Transceiver(&ESerial, PIN_M0, PIN_M1, PIN_AX);

void setup() {
  Serial.begin(9600);

  while (!Serial) {}

  pinMode(LED_BUILTIN, OUTPUT);

  ESerial.begin(9600);
  Serial.println("Starting Reader");

  Transceiver.init();
  Transceiver.SetAirDataRate(0);
  Transceiver.SetAddressH(0);
  Transceiver.SetAddressL(1);
  Transceiver.SetChannel(2);

  Transceiver.SaveParameters(TEMPORARY);

  Transceiver.PrintParameters();
}

void loop() {
  if (Transceiver.available()) {
    byte b = Transceiver.GetByte();
    Serial.print((char)b);
  }
  if (Serial.available()) {
    byte b = Serial.read();
    Transceiver.SendByte(b);
  }
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}
