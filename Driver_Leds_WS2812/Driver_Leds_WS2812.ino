/**
 * Copyright 2021 Marc SIBERT
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 *     
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "application.h"

/// Arduino ATméga 328 (Uno)
#if ARDUINO_AVR_UNO
#define SERIAL true
static const auto PIN_LEDS = 8;
static const auto NB_LED = 4;
static const auto PIN_LDR = A0;
#endif

/// Arduino ATtiny 85++
#if ARDUINO_AVR_ATTINYX5
#define SERIAL false
static const auto PIN_LEDS = 0;
static const auto NB_LED = 8;
static const auto PIN_LDR = A1;
#endif

auto app = Application<NB_LED, PIN_LEDS, PIN_LDR>();

/**
 * Lancée une fois à l'initialisation.
 */
void setup() {
  delay(1000);
  if (SERIAL) {
    Serial.begin(115200);
    while (!Serial);
    Serial.println(F(__FILE__ " compiled " __DATE__ " " __TIME__));
    Serial.println(F("Copyright (c) 2021 par Marc SIBERT"));
    Serial.println();
  }
  
  if (!app.setup()) {
    if (SERIAL) Serial.println("Erreur d'initialisation ! Arrêt !");
    exit(1);
  }
}

/**
 * Lancée itérativement.
 */
void loop() {
  if (!app.loop()) {
    if (SERIAL) Serial.println("Erreur d'exécution ! Arrêt !");
    exit(1);
  }
}
