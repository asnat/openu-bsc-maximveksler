/**
 * Matala 13 - Using a class to valid passport
 * 
 * @author Maxim Veksler
 * @version 140209042009
 */
public class Passport {
	private Date _expiryDate;
	private String _name;
	private int _number;
	
	/**
	 * creates a new Passport object
	 * 
	 * @param name the passport owner's name
	 * @param number the passport owner's id number
	 * @param expireDate the passport's expiration date
	 */
	public Passport(String name, int number, Date expiryDate) {
		this._name = name;
		this._number = number;
		this._expiryDate = expiryDate;
	}
	
	/**
	 * Copy Constructor
	 * 
	 * @param other to be copied
	 */
	public Passport(Passport other) {
		// primitives can be simply assigned as they are passed by value.
		_number = other._number;
		
		// Immutable objects can have aliases in various places because they will never change.
		_name = other._name;

		/**
		 * As for mutable objects, either copy primitives by value or share references to the
		 * most complex objects that are assured to be immutable.
		 * 
		 * In this case we copy the content of the Date object to the new instance.
		 */
		_expiryDate = new Date(other._expiryDate.getDay(), 
				other._expiryDate.getMonth(),
				other._expiryDate.getYear());
	}
	
	/**
	 * gets the expiration date
	 * 
	 * @return the expiration date
	 */
	public Date getExpiryDate() {
		return new Date(_expiryDate);
	}
	
	/**
	 * sets the expiration date
	 * 
	 * @param newExpDate the value to be set
	 */
	public void setExpiryDate(Date newExpDate) {
		this._expiryDate = newExpDate;
	}
	
	/**
	 * gets the name
	 * 
	 * @return the name
	 */
	public String getName() {
		return _name;
	}
	
	/**
	 * sets the name of the passport owner
	 * 
	 * @param name the value to be set
	 */
	public void setName(String name) {
		this._name = name;
	}

	/**
	 * determines if a passport is valid or not.
	 * 
	 * If the expiration date on the passport is before or on the date specified by
	 *  the parameter dateChecked then the passport is valid, otherwise it is not
	 * 
	 * @param checkedDate the date that the passport date is to be compared to
	 * @return true if the passport date is on or before the dateChecked
	 */
	public boolean isValid(Date checkedDate) {
		return (checkedDate.before(_expiryDate) || isSameDate(checkedDate, _expiryDate));
	}
	
	/**
	 * @return String that represents this passport in the following format: 
	 * Name:
	 * Pass. num: 
	 * Exp date:
	 */
	public String toString() {
		String result = 
			"Name: " + _name + "\n"
			+ "Pass. num: " + _number + "\n"
			+ "Exp date: " + _expiryDate;
		
		return result;
	}
	
	////////////////////////////////////
	/////// Class local methods ////////
	////////////////////////////////////
	/**
	 * Check if dates represent the same gregorian time (In days resolution).
	 * 
	 * @param date1 First checked date
	 * @param date2 Second checked date
	 * @return true if dates are equal, false if not
	 */
	private boolean isSameDate(Date date1, Date date2) {
		return (date1.getDay() == date2.getDay() && date1.getMonth() == date2.getMonth() && date1.getYear() == date2.getYear());
	}
} // end of class
