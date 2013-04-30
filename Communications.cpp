/*
  DHCP-based IP printer
 
 This sketch uses the DHCP extensions to the Ethernet library
 to get an IP address via DHCP and print the address obtained.
 using an Arduino Wiznet Ethernet shield. 
 
 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 
Base on work from:
 created 12 April 2011
 modified 9 Apr 2012
 by Tom Igoe

-----------------
 
  Communications.cpp - Library for Communications
  Created by Ricardo Miranda, April 2013
  GNU GPL
*/

#include <SPI.h>
#include <Ethernet.h>

//#include "WProgram.h" un-comment for use on older versions of Arduino IDE
#include "Communications.h"

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

//--------------------------------------------------------------------------------------

void Communications::communications() 
{
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
  // this check is only needed on the Leonardo:
   while (!Serial) 
  {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  byte mac[] = { 0x90, 0xA2, 0xDA, 0x0D, 0x06, 0x36 };

// nslookup arduino.irradiare.biz
  this->server = "192.168.0.99";
//  this->server = "89.153.254.164";

  this->client;

  // start the Ethernet connection:
  if (!Ethernet.begin(mac)) 
  {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    for(;;)
    ;
  }
  
  // Give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.println("connecting...");
  // print your local IP address:
  Serial.print  ("My IP address is: ");
  Serial.print(Ethernet.localIP());
  Serial.println();
}

//--------------------------------------------------------------------------------------

void Communications::calc(String _output_string)
{
  // if the server's connected, send message:
  char charServer[server.length()];
  this->server.toCharArray(charServer, this->server.length()+1);
  if (this->client.connect(charServer, 80))
  {
    String httpSring ="GET /store.php?";
           httpSring+=_output_string;
           httpSring+=" HTTP/1.1";

    char charhttpSring[httpSring.length()];
    httpSring.toCharArray(charhttpSring, httpSring.length()+1);

    this->client.println(charhttpSring);
    this->client.println("Host: arduino.irradiare.biz");
    this->client.println();
    
    Serial.print  (charhttpSring);
    Serial.println();
  }
  else // if the server's disconnected, stop the client:
  {
    // kf you didn't get a connection to the server:
    Serial.println("Connection failed");
    Serial.println(this->client.status());

    Serial.println();
    Serial.println("disconnecting.");
    this->client.stop();

    // Restart arduino
    void(* resetFunc) (void) = 0; //declare reset function @ address 0
    resetFunc();  //call reset
  }

/*
  // if there are incoming bytes available
  // from the server, read them and print them:
  if (this->client.available()) 
  {
    char c = this->client.read();
    Serial.print(c);
  }
*/
}

//--------------------------------------------------------------------------------------


