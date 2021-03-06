/*
 *  PinDefinitionsAndMore.h
 *
 *  Contains pin definitions for IRremote examples for various platforms
 *  as well as definitions for feedback LED and tone() and includes
 *
 *  Copyright (C) 2021  Armin Joachimsmeyer
 *  armin.joachimsmeyer@gmail.com
 *
 *  This file is part of IRMP https://github.com/Arduino-IRremote/Arduino-IRremote.
 *
 *  IRMP is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/gpl.html>.
 *
 */

/*
 * Pin mapping table for different platforms
 *
 * Platform     IR input    IR output   Tone
 * -----------------------------------------
 * DEFAULT/AVR  2           3           4
 * ATtinyX5     0           4           3
 * ATtin167     9           8           5 // Digispark pro number schema
 * ATtin167     3           2           7
 * ATtin3217    10          11          3 // TinyCore schema
 * SAMD21       3           4           5
 * ESP8266      14 // D5    12 // D6    %
 * ESP32        15          4           %
 * BluePill     PA6         PA7         PA3
 * APOLLO3      11          12          5
 */
//#define IRMP_MEASURE_TIMING // For debugging purposes.
//
#if defined(ESP8266)
#define FEEDBACK_LED_IS_ACTIVE_LOW // The LED on my board is active LOW
#define IR_RECEIVE_PIN  14 // D5
#define IR_SEND_PIN     12 // D6 - D4/2 is internal LED
#define tone(a,b) void() // tone() inhibits receive timer
#define noTone(a) void()
#define TONE_PIN        42 // Dummy for examples using it
#define IR_TIMING_TEST_PIN 13 // D7

#elif defined(ESP32)
#define IR_RECEIVE_PIN  15  // D15
#define IR_SEND_PIN      4  // D4
#define tone(a,b) void() // no tone() available on ESP32
#define noTone(a) void()
#define TONE_PIN        42 // Dummy for examples using it

#elif defined(ARDUINO_ARCH_STM32) || defined(ARDUINO_ARCH_STM32F1)
// BluePill in 2 flavors
// Timer 3 of IRMP blocks PA6, PA7, PB0, PB1 for use by Servo or tone()
#define IR_RECEIVE_PIN          PA6
#define IR_RECEIVE_PIN_STRING   "PA6"
#define IR_SEND_PIN             PA7
#define IR_SEND_PIN_STRING      "PA7"
#define TONE_PIN                PA3
#define IR_TIMING_TEST_PIN      PA5

#elif defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__) || defined(__AVR_ATtiny87__) || defined(__AVR_ATtiny167__)
//#include "ATtinySerialOut.h"
#  if  defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
#    if defined(ARDUINO_AVR_DIGISPARK)
#define LED_BUILTIN     PB1
#    endif
#define IR_RECEIVE_PIN  0
#define IR_SEND_PIN     4 // Pin 2 is serial output with ATtinySerialOut. Pin 1 is internal LED and Pin3 is USB+ with pullup on Digispark board.
#define TONE_PIN        3
//#define IR_TIMING_TEST_PIN 3

#  else
// ATtiny87 + ATtiny167 here. For ATtiny167 Pins PB6 and PA3 are usable as interrupt source.
#    if defined(ARDUINO_AVR_DIGISPARKPRO)
#define LED_BUILTIN      1 // PB1 - on Digispark board labeled as pin 1 / for ATtinyCore lib use D9
#define IR_RECEIVE_PIN   9 // PA3 - on Digispark board labeled as pin 9
//#define IR_RECEIVE_PIN  14 // PB6 / INT0 is connected to USB+ on DigisparkPro boards
#define IR_SEND_PIN      8 // PA2 - on Digispark board labeled as pin 8
#define TONE_PIN         5 // PA7
#define IR_TIMING_TEST_PIN 10 // PA4

#    else
#define IR_RECEIVE_PIN  3
#define IR_SEND_PIN     2
#define TONE_PIN        7
#    endif
#  endif

#elif defined(__AVR_ATtiny3217__)
#define IR_RECEIVE_PIN  10
#define IR_SEND_PIN     11
#define TONE_PIN         3

#elif defined(ARDUINO_ARCH_APOLLO3)
#define IR_RECEIVE_PIN  11
#define IR_SEND_PIN     12
#define TONE_PIN         5

#elif defined(ARDUINO_ARCH_MBED) // Arduino Nano 33 BLE
#define IR_RECEIVE_PIN  3
#define IR_SEND_PIN     4
#define TONE_PIN        5
#define IR_TIMING_TEST_PIN 6

#elif defined(TEENSYDUINO)
#define IR_RECEIVE_PIN  3
#define IR_SEND_PIN     4
#define TONE_PIN        5
#define IR_TIMING_TEST_PIN 6

#elif defined(__AVR__)
#define IR_RECEIVE_PIN  2 // To be compatible with interrupt example, pin 2 is chosen here.
#define IR_SEND_PIN     3
#define TONE_PIN        4
#define IR_TIMING_TEST_PIN 6

#elif defined(ARDUINO_ARCH_SAMD) || defined(ARDUINO_ARCH_SAM)
#define IR_RECEIVE_PIN  2 // To be compatible with interrupt example, pin 2 is chosen here.
#define IR_SEND_PIN     3
#define TONE_PIN        4
#define IR_TIMING_TEST_PIN 6

// On the Zero and others we switch explicitly to SerialUSB
#define Serial SerialUSB

// Definitions for the Chinese SAMD21 M0-Mini clone, which has no led connected to D13/PA17.
// Attention!!! D2 and D4 are switched on these boards!!!
// If you connect the LED, it is on pin 24/PB11. In this case activate the next two lines.
//#undef LED_BUILTIN
//#define LED_BUILTIN 24 // PB11
// As an alternative you can choose pin 25, it is the RX-LED pin (PB03), but active low.In this case activate the next 3 lines.
//#undef LED_BUILTIN
//#define LED_BUILTIN 25 // PB03
//#define FEEDBACK_LED_IS_ACTIVE_LOW // The RX LED on the M0-Mini is active LOW

#else
#warning Board / CPU is not detected using pre-processor symbols -> using default values, which may not fit. Please extend PinDefinitionsAndMore.h.
// Default valued for unidentified boards
#define IR_RECEIVE_PIN  2
#define IR_SEND_PIN     3
#define TONE_PIN        4
#define IR_TIMING_TEST_PIN 6
#endif // defined(ESP8266)

/*
 * Helper macro for getting a macro definition as string
 */
#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)