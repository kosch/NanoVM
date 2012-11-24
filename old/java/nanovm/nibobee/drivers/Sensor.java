package nanovm.nibobee.drivers;

/**
 * Encapsulates the information about the antenna sensors
 * @author Nils Springob
 */
public class Sensor {

  /**
   * get the value of the left antenna sensor
   * @return +1, 0, -1
   */
  public static native int getLeft();

  /**
   * get the value of the right antenna sensor
   * @return +1, 0, -1
   */
  public static native int getRight();
  
}


