package nanovm.nibobee.drivers;

/**
 * Gives access to general information about the Nibo robot.
 * You will have to call update first to get actual values.
 * @author Nils Springob
 */
public class Bot {
  
  /**
   * get the supply voltage. Result will be returned in millivolts.
   * 4500 is equivalent to 4.5 V
   * @return supply voltage in 1/1000 V
   */
  public static native int getSupplyVoltage();
}

