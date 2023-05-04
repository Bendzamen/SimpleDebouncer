Simple Debouncer

Solid Arduino digital signal debouncer library that works as it should, based on an algorithm from https://www.kennethkuhn.com/electronics/debounce.c



#Wiring

Connect one end of the button to the digital input pin of your choice and the second one to the ground
The library uses internal pullup resistor on the chosen pin


#Usage:

Create an instance of the SimpleDebouncer

    SimpleDebouncer Button(byte pin, unsigned int sampleIntervalMs, unsigned int samplesCount);

    - 'sampleIntervalMs' and 'samplesCount' are optional parameters, default values are 5 for each
    - 'pin' defines the input pin


Initialize the instance with the .setup() function

    Button.setup();

    - inside a void setup() initialize the instance
    - it sets the pin, sets all the variables and reads the first input


Update with the .process() function

    Button.process()

    - to be called at the beginning of the void loop()
    - reads the input, performs all the computation and updates the output


Get the current value
    - there are 2 ways to obtain the current value
    - to get the actual debounced value of the input, use the 'output' variable

    bool current_output = Button.output;

    - however this gives you 0 when the button is pressed and 1 when it is not pressed
    due to the wiring and the pullup resistor


    - to get the inverted value, you can call the .status() function which 
    gives the current inverted value (1 when the button is pressed, otherwise 0)

    bool current_output = Button.status();


Check whether the button was pressed with the .pressed() function
    
    Button.pressed();

    - this function returns 'true' once, immediately after the button was pressed
    - else, it returns 'false'


Check whether the button was released with .released() function

    Button.released();

    - this function returns 'true' once, immediately after the button was released
    - else, it returns 'false'



Created by Benjamin Lapos, May 2023
