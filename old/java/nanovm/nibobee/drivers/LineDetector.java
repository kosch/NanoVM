package nanovm.nibobee.drivers;

/**
 * Encapsulates the information about the two IR-reflex-sensors for line
 * detection. The values will be updated automatically by interrupt.
 * @author Nils Springob
 */
public class LineDetector {
  /**
   * Maximum value from IR-sensor
   */
  public static final int MAXIMUM = 255;
  
  /**
   * Minimum value from IR-sensor
   */
  public static final int MINIMUM = 0;

  /**
   * Index for left sensor
   */
  public static final int LEFT = 0;
  
  /**
   * Index for center sensor
   */
  public static final int CENTER = 1;

  /**
   * Index for right sensor
   */
  public static final int RIGHT = 2;

  /**
   * Get the normalized value of the given sensor.
   * @return measured value, between 0 and 255
   */
  public static native int getValue(int index);

  /**
   * Calibration with white reference surface.
   */
  public static native void calibrateWhite();

  /**
   * Calibration with black reference surface.
   */
  public static native void calibrateBlack();

  /**
   * enable and disable the IR LED
   * @param enable true for enable
   */
  public static native void setEnableIR(boolean enable);

  /**
   * get status of IR LED enabling
   * @return true when enabled
   */
  public static native boolean getEnableIR();



}


