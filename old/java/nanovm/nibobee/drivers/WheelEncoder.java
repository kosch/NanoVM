package nanovm.nibobee.drivers;

/**
 * Encapsulates the information about the wheels rotation. All wheel encoder
 * information is given in ticks, a tick is 1/20 of a wheel rotation.
 * @author Nils Springob
 */
public class WheelEncoder {

  /**
   * maximum value for tick increment
   */
  public static final int MAXIMUM = 32767;

  /**
   * minimum value for tick increment
   */
  public static final int MINIMUM = -32768;

  /**
   * minimum value for speed
   */
  public static final int MAXIMUM_SPEED = 200;

  /**
   * maximum value for speed
   */
  public static final int MINIMUM_SPEED = -200;

  /**
   * get tick-count from left wheel since last call
   * @return ticks since last call
   */
  public static native int getLeftInc();

  /**
   * get tick-count from right wheel since last call
   * @return ticks since last call
   */
  public static native int getRightInc();

  /**
   * get actual speed (ticks/second) from left wheel
   * @return ticks per second
   */
  public static native int getLeftSpeed();

  /**
   * get actual speed (ticks/second) from right wheel
   * @return ticks per second
   */
  public static native int getRightSpeed();

}


