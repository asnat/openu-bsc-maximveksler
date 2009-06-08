package lecture11;

public class Time1Mutate {
	public static void main (String[ ] args) {
	    	     PreciseTime lunchtime =
	    	     new PreciseTime(6, 10, 0);
	    	     lunchtime.advanceSeconds(60);
	    	     lunchtime.printTime( );
	    	     System.out.println( );
	    	     lunchtime.advanceSeconds(-61);
	    	     lunchtime.printTime( );
	    	     System.out.println( );
	   }
}
