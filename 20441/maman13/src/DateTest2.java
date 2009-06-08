import java.util.Calendar;

//import junit.framework.TestCase;

public class DateTest2 /*extends TestCase*/{
	final static long _DAY_IN_MILLIS = 24*60*60*1000;
	final static long _9999_YEARS_IN_MILLIS = _DAY_IN_MILLIS * 365 * 9999;

	public final void testBefore() {
		printCalendar(0);
		printCalendar(_DAY_IN_MILLIS);
		printCalendar(_DAY_IN_MILLIS * 365);
		printCalendar(_9999_YEARS_IN_MILLIS);
	}
	
	void printCalendar(long timeInMillis) {
		Calendar calendar = Calendar.getInstance();
		calendar.setTimeInMillis(timeInMillis);
		
		int futureDay = calendar.get(Calendar.DAY_OF_MONTH);
		int futureMonth = calendar.get(Calendar.MONTH) + 1; // January is returned as 0.
		int futureYear = calendar.get(Calendar.YEAR);

		System.out.println("Print for timeInMillis = " + timeInMillis + "\n"
				+ "futureDay " + futureDay + "\n"
				+ "futureMonth " + futureMonth + "\n"
				+ "futureYear " + futureYear + "\n"
				+ "-------------------------------------");
	}
	
	public static void main(String[] args) {
		// This is here only for the forum example so that people that don't know what
		// JUnit is could run the example and it would compile and run for them
		DateTest2 dateTest2 = new DateTest2();
		dateTest2.testBefore();
	}
}
