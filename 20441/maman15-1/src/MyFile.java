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
	
	private String _name;
	
	/**
	 * _fileObject Stores the content of the file, the actual object is 
	 * supplied by the extending class
	 */
	protected Object _fileObject; 
	
	/**
	 * _mode represents the editing permission of the file
	 * true - has permission, false - does not have permission
	 */
	protected boolean _mode;
	
	// ##########################
	// ##### Constructors #######
	// ##########################

	/**
	 * Construct a new MyFile object with null content with editing permission granted
	 * 
	 * @param name The name of the file
	 */
	public MyFile(String name) {
		this(name, null, true);
	}

	/**
	 * Construct a new MyFile object with editing permission granted
	 * 
	 * @param name The name of the file
	 * @param fileObject The class which represents the content of the file
	 */
	public MyFile(String name, Object fileObject) {
		this(name, fileObject, true);
	}
	
	/**
	 * Construct a new MyFile object with editing permission granted
	 * 
	 * @param name The name of the file
	 * @param fileObject The class which represents the content of the file
	 * @param mode The editing mode of the file: true means can edit, false means can not edit 
	 */
	public MyFile(String name, Object fileObject, boolean mode) {
		this._name = name;
		this._fileObject = fileObject;
		this._mode = mode;
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
	public Object open() {
		return _fileObject;
	}
	
	/**
	 * Return the size (in bytes) of the content of the file.
	 * 
	 * @return int representing the size of the content of the file
	 */
	public abstract int getSize();
}
