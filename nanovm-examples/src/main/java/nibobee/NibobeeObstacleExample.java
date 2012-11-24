import nanovm.nibobee.drivers.Clock;
import nanovm.nibobee.drivers.Motor;
import nanovm.nibobee.drivers.Sensor;

/** NibobeeObstacleExample.java
  * 
  * 
  * @see code based on nicai-systems c-library
  * @author Torsten Röhl <informatics4kids.de>
  */

class NibobeeObstacleExample {

	static final int MODE_STOP = 1;
	static final int MODE_DRIVE = 2;
	static final int MODE_BACK = 3;
	static final int MODE_STEER_R = 4;
	static final int MODE_STEER_L = 5;
	static final int MODE_AVOID_R = 6;
	static final int MODE_AVOID_L = 7;

	static int counter_ms = 0;

	static public int perform_check(int mode) {

		if ((Sensor.getLeft() != 0) && (Sensor.getRight() != 0)) {
			if ((Sensor.getLeft() == -1) && (Sensor.getRight() == -1)) {
				mode = MODE_BACK;
			} else {
				mode = MODE_STOP;
			}
		}
		return mode;
	}

	static public int do_stop() {
		if ((Sensor.getLeft() == 0) && (Sensor.getRight() == 0)) {
			return MODE_DRIVE;
		}
		return MODE_STOP;
	}

	static public int do_drive() {

		if (Sensor.getRight() == 1)
			return MODE_STEER_L;

		if (Sensor.getLeft() == 1)
			return MODE_STEER_R;

		if (Sensor.getRight() == -1)
			return MODE_AVOID_L;

		if (Sensor.getLeft() == -1)
			return MODE_AVOID_R;

		return MODE_DRIVE;
	}

	static public int do_back() {

		if (Sensor.getLeft() == 0)
			return MODE_AVOID_L;

		if (Sensor.getRight() == 0)
			return MODE_AVOID_R;

		return MODE_BACK;
	}

	static public int do_steer_r() {
		if (Sensor.getLeft() == 0)
			return MODE_DRIVE;

		return MODE_STEER_R;
	}

	static public int do_steer_l() {
		if (Sensor.getRight() == 0)
			return MODE_DRIVE;

		return MODE_STEER_L;
	}

	static public int do_avoid_r() {
		if (counter_ms == 0) {
			counter_ms = 1000;
		} else {
			counter_ms--;
		}
		if (counter_ms > 0) {
			return MODE_AVOID_R;
		} else {
			return MODE_DRIVE;
		}
	}

	static public int do_avoid_l() {
		if (counter_ms == 0) {
			counter_ms = 1000;
		} else {
			counter_ms--;
		}
		if (counter_ms > 0) {
			return MODE_AVOID_L;
		} else {
			return MODE_DRIVE;
		}
	}

	public static void main(String[] args) {

		final int MODE_STOP = 1;
		final int MODE_DRIVE = 2;
		final int MODE_BACK = 3;
		final int MODE_STEER_R = 4;
		final int MODE_STEER_L = 5;
		final int MODE_AVOID_R = 6;
		final int MODE_AVOID_L = 7;

		int speed_l = 500;
		int speed_r = 500;

		int mode = 2;

		while (1 == 1) {

			Clock.delayMilliseconds(1);
			mode = perform_check(mode);

			switch (mode) {
			case MODE_STOP:
				mode = do_stop();
				break;
			case MODE_DRIVE:
				mode = do_drive();
				break;
			case MODE_BACK:
				mode = do_back();
				break;
			case MODE_STEER_R:
				mode = do_steer_r();
				break;
			case MODE_STEER_L:
				mode = do_steer_l();
				break;
			case MODE_AVOID_R:
				mode = do_avoid_r();
				break;
			case MODE_AVOID_L:
				mode = do_avoid_l();
				break;
			}

			switch (mode) {
			case MODE_STOP:
				speed_l = 0;
				speed_r = 0;
				break;
			case MODE_DRIVE:
				speed_l = 500;
				speed_r = 500;
				break;
			case MODE_BACK:
				speed_l = -500;
				speed_r = -500;
				break;
			case MODE_STEER_R:
				speed_l = 600;
				speed_r = 400;
				break;
			case MODE_STEER_L:
				speed_l = 400;
				speed_r = 600;
				break;
			case MODE_AVOID_R:
				speed_l = -400;
				speed_r = -600;
				break;
			case MODE_AVOID_L:
				speed_l = -600;
				speed_r = -400;
				break;
			}

			Motor.setPWM(speed_l, speed_r);
		}

	}
}
