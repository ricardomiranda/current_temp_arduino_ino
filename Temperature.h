/*
  Temperature.h 
  Created by Ricardo Miranda, April 2013
  GNU GPL
*/

#include "Communications.h"      

#ifndef Temperature_h
#define Temperature_h

#if defined(ARDUINO) && ARDUINO >= 100

#include "Arduino.h"

#else

#include "WProgram.h"

#endif

class Temperature
{
  public:

    void temperature(int _inPinI, double _CAL, double _ARDINPUT);
    void calc       (Communications _comm);

  private:

    void serialprint(Communications _comm);
    
    int inPin;

    long timeStamp;

    double reading;                      

    double temp,
           CAL,
           ARDINPUT;
};

#endif



