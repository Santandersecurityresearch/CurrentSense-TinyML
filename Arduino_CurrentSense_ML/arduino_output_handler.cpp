/* Copyright 2019 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#include "output_handler.h"

#include "Arduino.h"
#include "constants.h"

// The pin of the Arduino's built-in LED
int led = LED_BUILTIN;

// Track whether the function has run at least once
bool initialized = false;

// Track previous inference outputs...
bool prev_out[3];

// Animates a dot across the screen to represent the current x and y values
void HandleOutput(tflite::ErrorReporter* error_reporter, float x_1, float x_2) {
  // Do this only once
  if (!initialized) {
    // Set the LED pin to output
    pinMode(led, OUTPUT);
    initialized = true;
  }
  bool output = (x_2 == 0) ? HIGH : LOW; // we'll use x_2 as we wanna focus on 'LED ON'.
  // if the previous outputs are the same as the current, then the LED is likely on...
  // this is to remove noisey false outputs from the model...
  if (prev_out[0] == prev_out[1] && prev_out[1] == output){
    digitalWrite(led, output);
  }
  TF_LITE_REPORT_ERROR(error_reporter, "LED guess: %d\n", output);
  prev_out[0] = prev_out[1];
  prev_out[1] = output;
}
