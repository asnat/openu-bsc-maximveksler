/**
 * Date representation Class. Each instance holds a single date
 * Matala 13 - Using a class to represent a given date in the Gregorian Calendar
 * 
 * @author Maxim Veksler 303856983
 * @version 010017042009
 *
 */
public class Date {
	private int _day;
	private int _month;
	private int _year;
	
	//////////////////////////////
	// Constructors        ///////
	//////////////////////////////
	/** 
	  * creates a new Date object 
	  * 
	  * Input sanity is enforced - if provided date parameters are found to be invalid, instance 
	  * 	will be created with default date "01/01/0001".
	  * 
	  * @param day the day in the month(1-31) 
	  * @param month the month in the year 
	  * @param year the year (in 4 digits) 
	 */
	public Date(int day, int month, int year) {
		if(isValidDate(day, month, year)) {
			this._day = day;
			this._month = month;
			this._year = year;
		} else {
			logError();
			
			this._day = 1;
			this._month = 1;
			this._year = 1;
		}
	}
	
	/**
	 * Copy Constructor
	 * 
	 * @param date date to be copied
	 */
	public Date(Date date) {
		// No need to check validity here because supplied date already contains a valid date format.
		this._day = date._day;
		this._month = date._month;
		this._year = date._year;
	}

	
	//////////////////////////////
	// Instance methods    ///////
	//////////////////////////////
	/**
	 * gets the Day
	 * 
	 * @return the day
	 */
	public int getDay() {
		return _day;
	}

	/**
	 * Change the day if the day is valid, otherwise the day remains unchanged
	 * 
	 * @param dayToSet - the value to be set
	 */
	public void setDay(int dayToSet) {
		if(isValidDate(dayToSet, _month, _year))
			this._day = dayToSet;
		else 
			logError();
	}

	/**
	 * gets the month
	 * 
	 * @return the month
	 */
	public int getMonth() {
		return _month;
	}

	/**
	 * Change the month if the month is valid, otherwise the month remains unchanged
	 * 
	 * @param monthToSet the value to be set
	 */
	public void setMonth(int monthToSet) {
		if(isValidDate(_day, monthToSet, _year))
			this._month = monthToSet;
		else
			logError();
	}

	/**
	 * gets the year
	 * 
	 * @return the year
	 */
	public int getYear() {
		return _year;
	}

	/**
	 * Change the year if the year is valid, otherwise the year remains unchanged
	 * 
	 * @param yearToSet the value to be set
	 */
	public void setYear(int yearToSet) {
		if(isValidDate(_day, _month, yearToSet))
			this._year = yearToSet;
		else
			logError();
	}

	/**
	 * String that represents this date in the following format: day.month.year (30/9/1917)
	 */
	public String toString() {
		return _day + "/" + _month + "/" + _year;
	}
	
	/**
	 * checks if this date comes before a given date
	 * 
	 * @param date the given date
	 * @return true if instance is before supplied parameter, false otherwise. 
	 */
	public boolean before(Date date) {
		// short circuiting logic: If year is smaller then return true, else if years equals check month and day following the same logic. 
		return (_year < date._year) 
			|| (_year == date._year && _month < date._month) 
			|| (_year == date._year && _month == date._month && _day < date._day);
	}
	
	//////////////////////////////
	// Class local methods ///////
	//////////////////////////////
	/**
	 * Check if supplied date is legal in the Gregorian calendar.
	 * 
	 * @param day 
	 * 		int value representing the day (legal input 1 - 31)
	 * @param month
	 * 		int value representing the month (legal input 1 - 12)
	 * @param year
	 * 		int value representing the year (legal input 1 - 9999)
	 * @return 
	 * 		true if is found to be a legal date by the Gregorian calendar, false if not
	 */
	private boolean isValidDate(int day, int month, int year) {
		// Verify lower bound.
		if(day <= 0 || month <= 0 || year <= 0)
			return false;
		
		// Verify upper bounds
		if(day > 31 || month > 12 || year > 9999)
			return false;
		
		switch (month) {
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			// If a month that can accept 31 days is given no further checks are required 
			// (upper bound verification has been tested above), return true. 
			return true;

		case 4:
		case 6:
		case 9:
		case 11:
			// These months can have a maximum of 30 days.
			if(day <= 30)
				return true;

		case 2:
			// February is a special case because it needs to account for leap year logic.
			if(isLeapYear(year)) {
				// If leap year February can have 29 days
				if(day <= 29)
					return true;
			} else {
				// else February has 28 days.
				if(day <= 28)
					return true;
			}
		}
		
		return false;
	}
	
	/**
	 * Check if year can be accounted as "leap" year
	 * 
	 * @param year 
	 * 		int value representing tested year
	 * @return 
	 * 		true if year is indeed a leap year, false otherwise 
	 */
	private boolean isLeapYear(int year) {
		// A leap year is every 4 years
		if (year % 4 == 0) {
			// but not every 100 years, then again every 400 years.
			if((!(year % 100 == 0)) || (year % 400 == 0))
				return true;
		}
		
		return false;
	}
	
	/**
	 * Write error to stdout.
	 */
	private void logError() {
		System.out.println("ERROR");
	}
} // end of class
