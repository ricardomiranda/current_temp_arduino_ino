current_temp_arduino_ino
========================

Arduino project to monitor energy and temperature

This project has 3 classes:
 - a class to monitor temperature usng a LM35 sensor;
 - a class to monitor electrical energy using clamps (Non-invasive AC current sensor SCT-013 (30A max));
 - a class to send data to a server.

The monitor classes may be instantiated for each sensor (one object per sensor).
