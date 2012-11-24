import nanovm.nibobee.drivers.Clock;
import nanovm.nibobee.drivers.Leds;
import nanovm.nibobee.drivers.Motor;
import nanovm.nibobee.drivers.Sensor;

/** NibobeeLedMotorSensorTest.java
  *
  * @author Torsten Röhl <informatics4kids.de>
  */

class NibobeeLedMotorSensorTest {

	static void led(int led, boolean status) {
		Leds.setStatus(led, status);
		Clock.delayMilliseconds(200);
	}
	
	public static void main(String[] args) {

		while (true) {

			int value = Sensor.getLeft();
			switch (value) {
			case -1: {
				led(Leds.LEFT_RED, false);
				led(Leds.LEFT_YELLOW, true);
				Motor.setPWM(-700, 0);
				break;
			}
			case +1: {
				led(Leds.LEFT_RED, true);
				led(Leds.LEFT_YELLOW, false);
				Motor.setPWM( 700,0);
				break;
			}
			case 0: {
				led(Leds.LEFT_RED, false);
				led(Leds.LEFT_YELLOW, false);
				Motor.stop();
				break;
			}

			}
			value = Sensor.getRight();
			switch (value) {
			case -1: {
				led(Leds.RIGHT_RED, false);
				led(Leds.RIGHT_YELLOW, true);
				Motor.setPWM( 0,-700);
				break;
			}
			case +1: {
				led(Leds.RIGHT_RED, true);
				led(Leds.RIGHT_YELLOW, false);
				Motor.setPWM( 0,700);
				break;
			}
			case 0: {
				led(Leds.RIGHT_RED, false);
				led(Leds.RIGHT_YELLOW, false);
				Motor.stop();
				break;
			}
			}
		}

	}
}
