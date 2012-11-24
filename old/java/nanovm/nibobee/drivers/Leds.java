package nanovm.nibobee.drivers;

/**
 * Provides methods to control the LEDs.
 * @author Nils Springob
 */
public class Leds {
  public static final int LEFT_YELLOW  = 0;
  public static final int LEFT_RED     = 1;
  public static final int RIGHT_RED    = 2;
  public static final int RIGHT_YELLOW = 3;

  /**
   * set given status LED
   * @param led id of the status LED
   * @param status  true: on  false: off
   */
  public static native void setStatus(int led, boolean status);
  
  /**
   * get current status of a given LED
   * @param led id of the status LED
   * @return current status of the LED
   */
  public static native boolean getStatus(int led);

}


