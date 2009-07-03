/**
 * Super class of a file object
 * 
 * @author Maxim Veksler 303856983
 */
public abstract class MyFile {
	/**
	 * _MODE_OPEN means file is mutable.
	 */
	protected static final boolean _MODE_OPEN = true;

	/**
	 * _MODE_CLOSED means file is immutable.
	 */
	protected static final boolean _MODE_CLOSED = false;
	
	/**
	 * The name of the file object.
	 */
	private String _name;
	

	// ##########################
	// ##### Constructors #######
	// ##########################

	/**
	 * Construct a new MyFile object.
	 * 
	 * @param name The name of the file
	 * @param fileObject The class which represents the content of the file
	 * @param mode The editing mode of the file: true means can edit, false means can not edit 
	 */
	public MyFile(String name) {
		this._name = name;
	}

	// #####################
	// ##### PUBLIC  #######
	// #####################

	/**
	 * Return the file name
	 * 
	 * @return String representing file name as it is appears in the file system
	 */
	public String getName() {
		return _name;
	}
	
	/**
	 * Returns the content of the file as an object 
	 * 
	 * @return Object that represents the content of the file
	 */
	public abstract Object open(); 
	
	/**
	 * Return the size (in bytes) of the content of the file.
	 * 
	 * @return int representing the size of the content of the file
	 */
	public abstract int getSize();
}
