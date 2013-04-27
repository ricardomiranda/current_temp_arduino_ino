/*
  Energy Monitor program
  Created by Ricardo Miranda, April 2013
  GNU GPL
*/

#include <SPI.h>
#include <Ethernet.h>

#include "Current.h"             // Include Energy Monitor Library
#include "Temperature.h"      
#include "Communications.h"      

Current        emon1;             // Create an instance for phase   I
Current       emon2;              // Create an instance for phase  II
//Current       emon3;              // Create an instance for phase III

Temperature    temp;
Communications comm;

long startTemp =-9999; 

void setup()
{  
  startTemp = millis(); 
  
  emon1.current(0, 30.0, 5.0);         // Current: input pin, clamp Max I, Input Arduino (5.0 V or 3.3 V)
  emon2.current(1, 30.0, 5.0);         // Current: input pin
//  emon3.current(2, 30.0, 5.0);         // Current: input pin

  temp.temperature(3, 100.0, 5.0);
  comm.communications();
}

//--------------------------------------------------------------------------------------

void loop()
{
  if ((millis()-startTemp)>=900000) {    
    temp.calc(comm);                      // temp in 15' intervals
    startTemp = millis();
  }
 
  
  emon1.calc(1000, comm);                   // time-out (millis)
  emon2.calc(2000, comm);                  // time-out (millis)
//  emon3.calc(2000, comm);                  // time-out (millis)

  delay(10000);
}

