import nanovm.nibobee.drivers.Clock;
import nanovm.nibobee.drivers.Motor;

/** NibobeeMotorTest.java
  * 
  * test nibobee motor
  *
  * @author Torsten Röhl <informatics4kids.de>
  */

class NibobeeMotorTest {

	          
	public static void main(String[] args) {

                        Clock.delayMilliseconds(1000);
                        Motor.setPWM( 700,700);
                        Clock.delayMilliseconds(1000);
                        Motor.setPWM( -700,-700);
                        Clock.delayMilliseconds(1000);
			Motor.stop();

		
	}
}
