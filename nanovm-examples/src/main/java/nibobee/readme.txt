 		readme 
	Di 10. Nov 15:18:15 CET 2009
____________________________________________________

[Test]
All *Test.java files are suitable to check
systematically the nibobee of functionality.


LedTest.java
MotorTest.java
SensorTest.java
LedMotorSensor.Test 
LineSensorTest.java
OdometryTest.java

The class LedMotorSensor.Test encapsulate the 
LedTest.java, MotorTest.java and SensorTest.java class.
A movement of the antenna sensor will switch on the LED(red/yellow)
and the motor(forward/backward).

Because the LineSensorTest  class makes use of the Sensors, it is smart
to check SensorTest.java before LineSensorTest.java

Because the OdometryTest class makes use of the Led's, it is smart
to check LedTest.java before OdometryTest.java

[Calibration]
Before you make use of the LineSensors it is neccessary to calibrate
the sensors

Calibration.java

usage:
To calibrate the sensor you will need a white background 
and a black background.
Start by putting the nibobee 
on the white background  and turn the left antenna sensor to back or front.
The left LED's indicate that the white calibration is done.

Do the same thing with a black background and the right antenna
sensor (this time the right LED's indicate that the black calibration
is done).

Because the values are written to the eeprom of the nibobee
this calibration is only necessary to do once. 


[Example]

ObstacleExample.java
LineFollowExample.java

Di 10. Nov 15:18:50 CET 2009
					Torsten Röhl <devel@softure.de>
