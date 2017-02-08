/*
Exploring Arduino - Code Listing 2-5: Debounced Button Toggling
http://www.exploringarduino.com/content/ch2

Copyright 2013 Jeremy Blum ( http://www.jeremyblum.com )
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License v3 as published by
the Free Software Foundation.
*/

boolean activated = 0;
const int LED=3;             //The LED is connected to pin 9
const int BUTTON=2;          //The Button is connected to pin 2
boolean lastButton = LOW;    //Variable containing the previous button state
boolean currentButton = LOW; //Variable containing the current button state
boolean ledOn = false;       //The present state of the LED (on/off)

void setup()
{
  pinMode (LED, OUTPUT);     //Set the LED pin as an output
  pinMode (BUTTON, INPUT);   //Set button as input (not required)
}

/*
* Debouncing Function
* Pass it the previous button state,
* and get back the current debounced button state.
*/
boolean debounce(boolean last, int BUTTON)
{
  boolean current = digitalRead(BUTTON);       //Read the button state
  if (last != current)                         //if it's different…
  {
    delay(5);                                  //wait 5ms
    current = digitalRead(BUTTON);             //read it again
  }
  return current;                              //return the current value
}   

void loop()
{
  
  currentButton = debounce(lastButton, BUTTON);
  if (currentButton == HIGH && lastButton == LOW)
  {
    ledOn = !ledOn;
    digitalWrite(LED,ledOn);
  }
  lastButton = currentButton;
  //else
  //{
   // digitalWrite(LED,LOW);
  //}
 
}

