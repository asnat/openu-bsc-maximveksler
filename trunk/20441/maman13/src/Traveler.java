/**
 * Matala 13 - Using a class to represent a traveler
 * 
 * @author Maxim Veksler
 * @version 140209042009
 */
public class Traveler {
// hilla - missing documentation of instance variables -1
	private boolean _isPayed;
	private Passport _passport;
	
	/**
	 * creates a new Traveler object
	 * 
	 * @param passport the passport information of the traveler
	 * @param isPayed boolean value representing whether the traveler has already paid for his/her flight
	 */
	public Traveler(Passport passport, boolean isPayed) {
		this._passport = passport;// hilla - aliasing!!! it should be: _passport = new Passport(passport); -2
		this._isPayed = isPayed;
	}
	
	/**
	 * Checks whether or not the travel’s passport is valid on the given 
	 * date and if the trip has already been paid  for.
	 * 
	 * @param travelDate date for when travel requested
	 * @return true if travel possible, false otherwise
	 */
	public boolean checkTravel(Date travelDate) {
		return _isPayed && _passport.isValid(travelDate);
	}

	/**
	 * returns whether the traveler has paid or not for his/her trip
	 * @return value of _isPayed
	 */
	public boolean isPayed() {
		return _isPayed;
	}
	
	/**
	 * traveler has paid for his/her trip
	 */
	public void pay() {
		_isPayed = true;
	}
	
	/**
	 * @return String that represents this traveler in the following format: 
	 * Name: 
	 * Pass. num: 
	 * Exp date:
	 */
	public String toString() {
		return _passport.toString();
	}
} // end of class
