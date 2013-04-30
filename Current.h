/*
  Current.h 
  Created by Ricardo Miranda, April 2013
  GNU GPL
*/

#include "Communications.h"      

#ifndef Current_h
#define Current_h

#if defined(ARDUINO) && ARDUINO >= 100

#include "Arduino.h"

#else

#include "WProgram.h"

#endif

class Current
{
  public:

    void current    (int _inPin, double _CAL, double _ARDINPUT);
    void calc       (int timeout, Communications _comm);

  private:

    void serialprint(             Communications _comm);

    int inPin;
    
    long   timeStamp;

    double sample, 
           reading;                      

    double Imax,
           CAL,
           ARDINPUT;
};

#endif



