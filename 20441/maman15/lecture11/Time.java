package lecture11;


/**
 * Write a description of class Time here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class Time
{
    protected int _hour, _minute;
 
     /**
     * Constructor for objects of class Time
     */
    public Time (int h, int m)  { 
       _hour = h; _minute = m; 
    }
    
    public void advanceMinutes (int m) {
        int totalMinutes =  ((60*_hour) + _minute + m)% (24*60);
        if (totalMinutes < 0)
            totalMinutes = totalMinutes + (24*60);
       _hour = totalMinutes / 60;
       _minute = totalMinutes % 60;
    }

    public void printTime ( ) {
    	     if ((_hour == 0) && (_minute == 0))
    			System.out.print("midnight");
    	     else if ((_hour == 12) && (_minute == 0))
    			System.out.print("noon");
    	     else {
    		         if (_hour == 0)                      System.out.print(12);
            		else if (_hour > 12)	   System.out.print(_hour - 12);
            		          else	                      System.out.print(_hour);
            
                            if (_minute < 10)
            				System.out.print(":0"+ _minute);
            		else	System.out.print(":" + _minute);
            
            		if (_hour < 12)	    System.out.print("AM");
             		else		    System.out.print("PM");
            	     }
    }
            
}
