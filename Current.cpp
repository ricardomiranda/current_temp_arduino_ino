/*
  Emon.cpp - Library for Energy Monitor
  Created by Ricardo Miranda, April 2013
  GNU GPL
*/

#include "Communications.h"      

//#include "WProgram.h" un-comment for use on older versions of Arduino IDE
#include "Current.h"

#if defined(ARDUINO) && ARDUINO >= 100

#include "Arduino.h"

#else

#include "WProgram.h"

#endif



//--------------------------------------------------------------------------------------

void Current::current(int _inPin, double _CAL, double _ARDINPUT)      // _CAL is the max current read from the clamp
                                                                      // _ARDINPUT if input at 3.3 V or 5.0 V
{
   inPin    = _inPin;
   pinMode(inPin, INPUT);
   CAL     = _CAL;
   ARDINPUT = _ARDINPUT;
}

//--------------------------------------------------------------------------------------

void Current::calc(int timeout, Communications _comm)
{
  unsigned long start = millis(); 
  Imax   =-99999.9;
  sample =-99999.9;

  while ((millis()-start)<timeout)
  {
    reading  = analogRead(inPin);                         // Read in raw current signal
    sample   = reading * (ARDINPUT / 1024.0) * CAL;       // Converts analog to digital
    if (Imax < sample) Imax = sample;
    
    timeStamp = millis();
  }
 
  serialprint(_comm);
}

//--------------------------------------------------------------------------------------

void Current::serialprint(Communications _comm)
{ 
  char auxImax1[6];
  dtostrf(Imax, 6, 3, auxImax1);
  String auxImax2(auxImax1);
         auxImax2.trim();
  
  String output_string ="time_stamp=";
         output_string+=timeStamp;
         output_string+="&i_max";
         output_string+=inPin;
         output_string+="=";
         output_string+=auxImax2;
  _comm.calc(output_string);
}



