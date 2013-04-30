/*
  Communications.h 
  Created by Ricardo Miranda, April 2013
  GNU GPL
*/

#include <SPI.h>
#include <Ethernet.h>

#ifndef Communications_h
#define Communications_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class Communications
{
  public:

    void communications();
    void calc          (String _output_string);

  private:

    EthernetClient client;

//    char server[];
    String server;
};

#endif


