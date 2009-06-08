import java.util.Calendar;

import junit.framework.TestCase;


public class TestPassport extends TestCase {

	public void testPassportStringIntDate() {
		Passport passport = new Passport("Maxim Veksler", 5000, new Date(3,5,1983));
		assertEquals(passport.getName(), "Maxim Veksler");
		assertTrue(dateEqual(passport.getExpiryDate(), new Date(3,5,1983)));
	}

	public void testPassportPassport() {
		Passport passport = new Passport("Maxim Veksler", 5000, new Date(3,5,1983));
		Passport passport2 = new Passport(passport);
		
		assertEquals(passport.getName(), passport2.getName());
		assertSame(passport.getName(), passport2.getName());
		assertNotSame(passport.getExpiryDate(), passport2.getExpiryDate());
		
		assertEquals(passport.getExpiryDate().getDay(), passport2.getExpiryDate().getDay());
		assertEquals(passport.getExpiryDate().getMonth(), passport2.getExpiryDate().getMonth());
		assertEquals(passport.getExpiryDate().getYear(), passport2.getExpiryDate().getYear());
	}

	public void testGetExpiryDate() {
		Passport passport = new Passport("Maxim Veksler", 5000, new Date(3,5,1983));
		
		// Try modifying value in one of the objects and making sure not modified in the other.
		Date dateCopy = passport.getExpiryDate();
		dateCopy.setDay(4);
		
		assertFalse(passport.getExpiryDate().getDay() == dateCopy.getDay());
	}
	
	public void testIsValid() {
		Passport tested;
		
		Calendar today = Calendar.getInstance();
		Date todayDate = fromCalendarToDate(today);
		
		Calendar tomorrow = Calendar.getInstance();
		tomorrow.add(Calendar.DAY_OF_MONTH, 1);
		Date tomorrowDate = fromCalendarToDate(tomorrow);
		
		Calendar yesterday = Calendar.getInstance();
		yesterday.add(Calendar.DAY_OF_MONTH, -1);
		Date yesterdayDate = fromCalendarToDate(yesterday);

		// Test for passport that ends tomorrow
		tested = new Passport("tomorrowPassport", 1, tomorrowDate);
		assertTrue(tested.isValid(yesterdayDate));
		assertTrue(tested.isValid(todayDate));
		assertTrue(tested.isValid(tomorrowDate));

		// Test for passport that ends today
		tested = new Passport("tomorrowPassport", 1, todayDate);
		assertTrue(tested.isValid(yesterdayDate));
		assertTrue(tested.isValid(todayDate));
		assertFalse(tested.isValid(tomorrowDate));

		// Test for passport that ends yesterday
		tested = new Passport("tomorrowPassport", 1, yesterdayDate);
		assertTrue(tested.isValid(yesterdayDate));
		assertFalse(tested.isValid(todayDate));
		assertFalse(tested.isValid(tomorrowDate));

	}

	public void testToString() {
		Date date = new Date(12, 12, 2009);
		String name = "Maxim Veksler";
		int num = 123403434;
		
		Passport passport = new Passport(name, num, date);
		
		String expected =  "Name: " + name
		+ "\nPass. num: " + num
		+ "\nExp date: " + "12/12/2009";
		
		assertEquals(expected, passport.toString());
	}

	boolean dateEqual(Date date1, Date date2) {
		return date1.getDay() == date2.getDay() && date1.getMonth() == date2.getMonth() && 
			date1.getYear() == date2.getYear();
	}
	
	Date fromCalendarToDate(Calendar calendar) {
		int day = calendar.get(Calendar.DAY_OF_MONTH);
		int month = calendar.get(Calendar.MONTH) + 1; // January is returned as 0.
		int year = calendar.get(Calendar.YEAR);

		Date date = new Date(day, month, year);
		
		return date;
	}
}
