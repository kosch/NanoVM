import nanovm.nibobee.drivers.Clock;
import nanovm.nibobee.drivers.Leds;
import nanovm.nibobee.drivers.LineDetector;
import nanovm.nibobee.drivers.Sensor;

/** NibobeeLineSensorTest.java
  * 
  * test nibobee line sensors
  *
  * @author Torsten Röhl <informatics4kids.de>
  */

class NibobeeLineSensorTest {

	static void led(int led, boolean status) {
		Leds.setStatus(led, status);
	}

	static void ledOff() {
		led(Leds.LEFT_YELLOW, false);
		led(Leds.LEFT_RED, false);
	        Clock.delayMilliseconds(200);
	}

	public static void main(String[] args) {
	
		LineDetector.setEnableIR(true);

		while (true) {

                       int test  = 0;
                       ledOff();
  
 		       // choose lineDetector LEFT, RIGHT or CENTER to test                     
                       int value = Sensor.getLeft();
                       if( value == -1 )
				test = LineDetector.getValue(LineDetector.LEFT);
                       if( value == 1 )
				test = LineDetector.getValue(LineDetector.RIGHT);
                       
                       value = Sensor.getRight();
                       
                       if(value != 0 )
				test = LineDetector.getValue(LineDetector.CENTER);

                        
                        // test 
			if ( test > 160) {
				led(Leds.LEFT_YELLOW, true);
				led(Leds.LEFT_RED, false);
				Clock.delayMilliseconds(200);

			}

			if ( test > 240) {
				led(Leds.LEFT_YELLOW, true);
				led(Leds.LEFT_RED, true);
				Clock.delayMilliseconds(200);

			}
		}

		
	}
}
