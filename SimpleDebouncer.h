/*  
    SimpleDebouncer.h - Library for digital debouncing 
    Simple but powerful digital input debouncer
    Excellent for debouncing buttons
    Returns 0 or 1 based on the input signal
    Based on an algorithm from https://www.kennethkuhn.com/electronics/debounce.c
    Created by Benjamin Lapos May 2023
*/

#ifndef SIMPLEDEBOUNCER_H
#define SIMPLEDEBOUNCER_H

#include "Arduino.h"

class SimpleDebouncer{
    private:
        byte                _pin;               // used GPIO pin (parameter)
        unsigned int        _sampleIntervalMs;  // sample interval (parameter)
        unsigned int        _samplesCount;      // desired number of samples during integration (parameter)
        unsigned int        _integrator;        // Will range from 0 to the specified samplesCount
        unsigned long       _lastSampleMs;      // time of the last sample
        bool                input;              // 0/1 depending on the input signal
        bool                previousP;          // variable storing previous value of the function "pressed"
        bool                previousR;          // variable storing previous value of the function "released"

    public:
        bool                output;             // Cleaned-up version of the input signal, output 0/1
        // creation of SimpleDebouncer instance
        SimpleDebouncer(byte pin, unsigned int sampleIntervalMs = 5, unsigned int samplesCount = 5);       
        void setup();       // function that sets pin and initializes the function
        void process();     // function that conducts the debouncing and updates the output
        bool pressed();     // function that returns true if the button was pressed
        bool released();    // function that returns true if the button was released
        bool status();      // if called, returns boolean current state of the button (true == pressed)
};

#endif