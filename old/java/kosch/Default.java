import nanovm.avr.*;

class Default {
  public static void main(String[] args) {
    //System.out.println("Clock=" + AVR.getClock());
    //System.out.println("Timer="+Timer.get());

    // pin 1 output
    AVR.portB.setOutput(0);
    
    // no need to setup timer, since 100Hz is default ...

    while(true) {
      AVR.portB.setBit(0);
      Timer.wait(200);
      AVR.portB.clrBit(0);
      Timer.wait(200);
    }
  }
}
