/*
  LedTest.java
  (c) 2009 Nils Springob <nils@nicai-systems.de>
 */

import nanovm.nibobee.drivers.Clock;
import nanovm.nibobee.drivers.Leds;

class NibobeeLedTest {

	// set status led state and wait a second
	static void led(int led, boolean status, int ms) {
		Leds.setStatus(led, status);
		Clock.delayMilliseconds(ms);
	}

	public static void main(String[] args) {

		while (true) {
			// test leds
			led(Leds.LEFT_YELLOW, true, 200);
			led(Leds.LEFT_RED, true, 200);
			led(Leds.RIGHT_RED, true, 200);
			led(Leds.RIGHT_YELLOW, true, 200);

			led(Leds.RIGHT_YELLOW, false, 200);
			led(Leds.RIGHT_RED, false, 200);
			led(Leds.LEFT_RED, false, 200);
			led(Leds.LEFT_YELLOW, false, 200);

			led(Leds.RIGHT_YELLOW, true, 200);
			led(Leds.RIGHT_RED, true, 200);
			led(Leds.LEFT_RED, true, 200);
			led(Leds.LEFT_YELLOW, true, 200);

			led(Leds.LEFT_YELLOW, false, 200);
			led(Leds.LEFT_RED, false, 200);
			led(Leds.RIGHT_RED, false, 200);
			led(Leds.RIGHT_YELLOW, false, 200);
		}
	}
}
