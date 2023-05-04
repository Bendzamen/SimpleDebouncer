/*
  SimpleDebouncer library button example

  Press the pushbutton to turn the BUILTIN LED on
  Release the pushbutton to turn the BUILTIN LED off

  Connect one of the pushbuttons pin to the ground 
  and the second one to the pin 11 

  Created by Benjamin Lapos May 2023
*/

#include "SimpleDebouncer.h"

//define input pin of the button
const int button_pin = 11;

/*
 create an instance of SimpleDebouncer with the name ButtonDebouncer
 required parameter is the pin to use
 optional parameters 
     - sample interval = default 5 (in ms)
     - samples count = default 5
*/
SimpleDebouncer ButtonDebouncer(button_pin);

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  // .setup() function
  // sets all the starting variables and reads first input
  ButtonDebouncer.setup();
}

void loop() {
  // .process() function
  // reads the input and processes the signal
  // supposed to be called every loop
  ButtonDebouncer.process();

  /*
    Uncomment if needed
    .status() function returns current cleaned-up input state
    beware it returns value 1 when the button is pressed and 0 when not pressed
    the values are switched compared to the actual wiring
  */ 
  //Serial.println(ButtonDebouncer.status());
  /*
    if you want to get the original cleaned-up value of the input
    (0 when presssed, 1 when not, as the button is connected to the ground through pullup resistor)
    you can get the value by calling the public variable ButtonDebouncer.output
  */
  
  // .pressed() function 
  // returns true immediately after the button was pressed
  if (ButtonDebouncer.pressed()){
    digitalWrite(LED_BUILTIN, HIGH);
  }

  // .released() function 
  // returns true immediately after the button was released
  if (ButtonDebouncer.released()){
    digitalWrite(LED_BUILTIN, LOW);
  }
}
