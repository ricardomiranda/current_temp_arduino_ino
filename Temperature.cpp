/*
  Temperature.cpp - Library for Temperature Monitor
  Created by Ricardo Miranda, April 2013
  GNU GPL
*/

#include "Communications.h"      

//#include "WProgram.h" un-comment for use on older versions of Arduino IDE
#include "Temperature.h"

#if defined(ARDUINO) && ARDUINO >= 100

#include "Arduino.h"

#else

#include "WProgram.h"

#endif



//--------------------------------------------------------------------------------------

void Temperature::temperature(int _inPin, double _CAL, double _ARDINPUT)        // _CAL is the temperature calibration
                                                                                  // _ARDINPUT if input at 3.3 V or 5.0 V
{
   inPin    = _inPin;
   pinMode(inPin, INPUT);
   CAL     = _CAL;
   ARDINPUT = _ARDINPUT;
}

//--------------------------------------------------------------------------------------

void Temperature::calc(Communications _comm)
{
  reading  = analogRead(inPin);                         // Read in raw current signal
  temp   = reading * (ARDINPUT / 1024.0) * CAL;          // Converts analog to digital
    
  timeStamp = millis();
 
  serialprint(_comm);
}

//--------------------------------------------------------------------------------------

void Temperature::serialprint(Communications _comm)
{
  char auxTemp1[6];
  dtostrf(temp, 6, 3, auxTemp1);
  String auxTemp2(auxTemp1);
         auxTemp2.trim();

  
  String output_string ="time_stamp=";
         output_string+=timeStamp;
         output_string+="&temp=";
         output_string+=auxTemp2;
  _comm.calc(output_string);
  
}



