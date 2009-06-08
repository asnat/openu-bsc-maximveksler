	

import java.util.Arrays;
import java.util.Calendar;
import java.util.GregorianCalendar;
import java.util.List;
import java.util.Random;

import junit.framework.TestCase;

/**
 * 
 * @author Maxim Veksler
 * @version 021509042009
 */
public class TestDate extends TestCase {
	final static long _DAY_IN_MILLIS = 24*60*60*1000;
	final static long _9999_YEARS_IN_MILLIS = 
		new GregorianCalendar(/*year*/ 10000, /*month*/ 1, /*dayOfMonth*/ 1, /*hourOfDay*/ 0, /*minute*/ 0, /*second*/ 0).getTimeInMillis() - 1;
	final static List<Integer> LEAP_YEARS = Arrays.asList(1804,1808,1812,1816,1820,1824,1828,1832,1836,1840,1844,1848,1852,1856,1860,1864,1868,1872,1876,1880,1884,1888,1892,1896,1904,1908,1912,1916,1920,1924,1928,1932,1936,1940,1944,1948,1952,1956,1960,1964,1968,1972,1976,1980,1984,1988,1992,1996,2000,2004,2008,2012,2016,2020,2024,2028,2032,2036,2040,2044,2048,2052,2056,2060,2064,2068,2072,2076,2080,2084,2088,2092,2096,2104,2108,2112,2116,2120,2124,2128,2132,2136,2140,2144,2148,2152,2156,2160,2164,2168,2172,2176,2180,2184,2188,2192,2196,2204,2208,2212,2216,2220,2224,2228,2232,2236,2240,2244,2248,2252,2256,2260,2264,2268,2272,2276,2280,2284,2288,2292,2296,2304,2308,2312,2316,2320,2324,2328,2332,2336,2340,2344,2348,2352,2356,2360,2364,2368,2372,2376,2380,2384,2388,2392,2396,2400);

	Random random = new Random();

	public final void testBefore() {
		Calendar now = Calendar.getInstance();
		
		int day = now.get(Calendar.DAY_OF_MONTH);
		int month = now.get(Calendar.MONTH) + 1; // January is returned as 0.
		int year = now.get(Calendar.YEAR);
		Date tested = new Date(day, month, year);

		assertFalse(tested.before(tested));

		for(int i=0;  i < 500000; i++) {
			// calculate a random later date.
			
			/* Our date is in days resolution, so we remove a day from the randomness range and 
			 * return it back in the calendar construction down the road, this ensures that all future 
			 * days will started no less then tomorrow. */
			long __futureDeviationMax = (_9999_YEARS_IN_MILLIS - now.getTimeInMillis()) - _DAY_IN_MILLIS;
			
			// We need to randomize long, so we break it into 2 int's (4byte each) random them then compose back
			// to long.
			int futureLsb = Math.abs((int)(__futureDeviationMax & 0x00000000FFFFFFFFl));
			int futureMsb = Math.abs((int)((__futureDeviationMax & 0xFFFFFFFF00000000l) >> 32));
			long randomCappedLong = Math.abs(random.nextInt(futureLsb) + (((long)random.nextInt(futureMsb)) << 32));
			
			long futureTimeInMillis = now.getTimeInMillis() + _DAY_IN_MILLIS + randomCappedLong; // return the missing day.

			// Unit test the unit test... do ignore.
			assertTrue(__futureDeviationMax >= randomCappedLong);
			assertTrue(randomCappedLong > 0);
			assertTrue(futureTimeInMillis >= now.getTimeInMillis());
			
			Calendar futureCalendar = Calendar.getInstance();
			futureCalendar.setTimeInMillis(futureTimeInMillis); 
			
			int futureDay = futureCalendar.get(Calendar.DAY_OF_MONTH);
			int futureMonth = futureCalendar.get(Calendar.MONTH) + 1; // January is returned as 0.
			int futureYear = futureCalendar.get(Calendar.YEAR);

			Date afterDate = new Date(futureDay, futureMonth, futureYear);
			assertTrue(tested.before(afterDate));
			assertFalse(afterDate.before(tested));
		}		
	}
	
	public final void testToString() {
		Calendar calendar = Calendar.getInstance();
		
		int day = calendar.get(Calendar.DAY_OF_MONTH);
		int month = calendar.get(Calendar.MONTH) + 1; // January is returned as 0.
		int year = calendar.get(Calendar.YEAR);
	
		Date tested = new Date(day, month, year);
		assertEquals(String.format("%d/%d/%d", day, month, year), tested.toString());
	}
	
	public final void testConstructors() {
		Date tested;
		
		/*
		 *  Test date verification logic.
		 */
		
		// Test leap (February 29)
		for (int year = 1; year < 3000; year++) {
			
			if(LEAP_YEARS.contains(year)) {
				tested = new Date(29, 2, year);
				assertTrue(tested.getDay() == 29);
				assertTrue(testCopyConstructor(new Date(tested), 29, 2, year));
			} else {
				tested = new Date(28, 2, year);
				assertTrue(tested.getDay() == 28);
				assertTrue(testCopyConstructor(new Date(tested), 28, 2, year));
			}
		}
		
		// Test invalid dates
		tested = new Date(-1, 1, 2009);
		assertFalse(tested.getDay() == -1);
		assertTrue(tested.getDay() == 1);
		assertTrue(testCopyConstructor(new Date(tested), 1, 1, 1));
		
		tested = new Date(1, -1, 2009);
		assertFalse(tested.getMonth() == -1);
		assertTrue(tested.getMonth() == 1);
		assertTrue(testCopyConstructor(new Date(tested), 1, 1, 1));

		
		tested = new Date(1, 1, -1);
		assertFalse(tested.getYear() == -1);
		assertTrue(tested.getYear() == 1);
		assertTrue(testCopyConstructor(new Date(tested), 1, 1, 1));
		
		tested = new Date(0, 1, 2009);
		assertTrue(tested.getDay() == 1);
		assertTrue(testCopyConstructor(new Date(tested), 1, 1, 1));

		tested = new Date(1, 0, 2009);
		assertTrue(tested.getMonth() == 1);
		assertTrue(testCopyConstructor(new Date(tested), 1, 1, 1));

		tested = new Date(1, 1, 0);
		assertTrue(tested.getYear() == 1);
		assertTrue(testCopyConstructor(new Date(tested), 1, 1, 1));
		
		tested = new Date(-11, -11, -10);
		assertTrue(tested.getDay() == 1 && tested.getMonth() == 1 && tested.getYear() == 1 );
		assertTrue(testCopyConstructor(new Date(tested), 1, 1, 1));
		
		tested = new Date(0, 0, 0);
		assertTrue(tested.getDay() == 1 && tested.getMonth() == 1 && tested.getYear() == 1 );
		assertTrue(testCopyConstructor(new Date(tested), 1, 1, 1));

		// Test valid dates
		tested = new Date(5, 5, 5);
		assertTrue(tested.getDay() == 5 && tested.getMonth() == 5 && tested.getYear() == 5 );
		assertTrue(testCopyConstructor(new Date(tested), 5, 5, 5));

		tested = new Date(7, 4, 2009);
		assertTrue(tested.getDay() == 7 && tested.getMonth() == 4 && tested.getYear() == 2009 );
		assertTrue(testCopyConstructor(new Date(tested), 7, 4, 2009));

		tested = new Date(25, 9, 2133);
		assertTrue(tested.getDay() == 25 && tested.getMonth() == 9 && tested.getYear() == 2133 );
		assertTrue(testCopyConstructor(new Date(tested), 25, 9, 2133));
	}
	
	boolean testCopyConstructor(Date date, int expectedDay, int expectedMonth, int expectedYear) {
		if(date == null)
			return false;
		
		return date.getDay() == expectedDay && date.getMonth() == expectedMonth && date.getYear() == expectedYear;
	}
}
