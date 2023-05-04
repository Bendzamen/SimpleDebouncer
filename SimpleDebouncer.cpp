/*  
    SimpleDebouncer.cpp - Library for digital debouncing
    Simple but powerful digital input debouncer
    Ecellent for debouncing buttons
    Returns 0 or 1 based on the input signal
    Based on an algorithm from https://www.kennethkuhn.com/electronics/debounce.c
    Created by Benjamin Lapos May 2023
*/

#include "Arduino.h"
#include "SimpleDebouncer.h"

SimpleDebouncer::SimpleDebouncer(byte pinAttachTo, unsigned int sampleIntervalMs, unsigned int  samplesCount){
    _pin = pinAttachTo;
    _sampleIntervalMs = sampleIntervalMs;
    _samplesCount = samplesCount;
}

void SimpleDebouncer::setup(){
    pinMode(_pin, INPUT_PULLUP);
    input =  digitalRead(_pin); // read the input first time
    _lastSampleMs = millis();   // set the starting time
    output = input; // at the beginning, set the output to the input
    // set the initial value of the integrator based on the input
    if (input)  _integrator = _samplesCount;  // if the input is logic 1
    else  _integrator = 0;                    // if the input is logic 0
    previousP = 0;
    previousR = 0;
}


// main process function
// called every cycle in "void loop()" to process the digital input
void SimpleDebouncer::process(){
    if ((millis() - _lastSampleMs) >= _sampleIntervalMs) {
        // start of sample processing
        input = digitalRead(_pin);
        _lastSampleMs = millis(); // time of sample being taken
        /* Step 1: Update the integrator based on the input signal.  Note that the
        integrator follows the input, decreasing or increasing towards the limits as
        determined by the input state (0 or 1). */


        if (input == false) // logic 0
            {
            if (_integrator > 0)
            _integrator--;
            }
        else if (_integrator < _samplesCount) // branch if the input is logic 1
            _integrator++;

        /* Step 2: Update the output state based on the integrator.  Note that the
        output will only change states if the integrator has reached a limit, either
        0 or MAXIMUM. */

        if (_integrator == 0)
            output = false; // output logic 0
        else if (_integrator >= _samplesCount)
            {
            output = true; // output logic 1
            _integrator = _samplesCount;  //defensive code if integrator got corrupted
            }
    } // end of sample processing
}


/*
    funtion that returns true once, 
    immediately after the first high output 
    (when the button is pressed), 
    else always returns false
*/
bool SimpleDebouncer::pressed(){
    if (!previousP && !output){
        previousP = 1;
        return true;
    }
    else if (previousP && output){
        previousP = 0;
    }
    /*
    if (previousP == 0 && output == 0){
        previousP = 1;
        return true;
    }
    else if (previousP == 1 && output == 1){
        previousP = 0;
    }
    */
    return false;
}


/*
    funtion that returns true once, 
    immediately after the last high output 
    (when the button is released), 
    else always returns false
*/
bool SimpleDebouncer::released(){
    if (!previousR && output){
        previousR = 1;
        return true;
    }
    else if (previousR && !output){
        previousR = 0;
    }

    /*
    if (previousR == 0 && output == 1){
        previousR = 1;
        return true;
    }
    else if (previousR == 1 && output == 0){
        previousR = 0;
    }
    */
    return false;
}


/*
    simple function that returns the current cleaned-up input
    beware, this functions returns 1 if the button is pressed
    returns 0 if it isn't
    (actual input signal is switched as the button is connected
    to the ground with pullup resistor on the pin)
    If you want to get the original cleaned-up value you can
    call the public variable output
*/ 
bool SimpleDebouncer::status(){
    return !output;
}