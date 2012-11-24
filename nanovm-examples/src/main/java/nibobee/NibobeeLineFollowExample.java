import nanovm.nibobee.drivers.Clock;
import nanovm.nibobee.drivers.LineDetector;
import nanovm.nibobee.drivers.Motor;

/** NibobeeLineFollowExample.java
  * 
  * 
  * @see code based on c found at www.mikrocontroller.net 
  * @author Torsten Röhl <informatics4kids.de>
  */

class NibobeeLineFollowExample {

	


	public static void main(String[] args) {

		int speed_flt_l=0; 
   		int speed_flt_r=0; 
             	LineDetector.setEnableIR(true);
		
		while(true){
			Clock.delayMilliseconds(1) ;
                	int speed_l = 0;
                	int speed_r = 0;
                	int vL = LineDetector.getValue(LineDetector.LEFT);
                	int vC = LineDetector.getValue( LineDetector.CENTER);
                	int vR = LineDetector.getValue( LineDetector.RIGHT);

                	if( vL + vC + vR < 20){
                       		speed_r = 0;
                       		speed_l = 0;
                	} else if( (vL< vC) && (vL < vR)){
                              speed_r=550;
                              speed_l=450-1*(vC-vL);
		}else if ((vR<vC) && (vR<vL)) { 
    
         		speed_r=450-1*(vC-vR);
	 		speed_l=550; 
     		} else { 
      
         		speed_r=750 + 1*(vR-vC);
	 		speed_l=750 + 1*(vL-vC); 
    			 } 

         	speed_flt_l*=3; speed_flt_l+=speed_l; speed_flt_l/=4; 
         	speed_flt_r*=3; speed_flt_r+=speed_r; speed_flt_r/=4; 
         
         	if(speed_flt_l < 50 && speed_flt_r < 50 ){
        		speed_flt_l = 200;
                	speed_flt_r = 200; 
	  	}
 
        	Motor.setPWM(speed_flt_l, speed_flt_r);

		}
	}

}

