/**
 * A File representing Text data
 * 
 * @author Maxim Veksler
 *
 */
public class TextFile extends MyFile {
	/**
	 * The content of this file, which is a text String
	 */
	private String _fileObject;
	
	/**
	 * _mode represents the editing permission of the file
	 * true - has permission, false - does not have permission
	 */
	private boolean _mode;

	// ####################
	// ### CONSTRUCTOR ####
	// ####################
	
	/**
	 * Construct a Text file with name and text content, file is created allowed for editing.
	 * 
	 * @param name The name of the file as it is represented in the file system
	 * @param text String representing the content of the file
	 */
	public TextFile(String name, String text) {
		this(name, text, _MODE_OPEN);
	}

	/**
	 * Construct a Text file with name, text content and an editing mode
	 * 
	 * @param name The name of the file as it is represented in the file system
	 * @param text String representing the content of the file
	 * @param mode boolean editing mode. true means file content can be modified, false means it can not
	 */
	public TextFile(String name, String text, boolean mode) {
		super(name);
		this._fileObject = text;
		this._mode = mode;
	}

	// ###############
	// ### PUBLIC ####
	// ###############

	/**
	 * Return the length of the text inside the file (number of characters)
	 * 
	 * @return int representing the number of characters in the text of the file
	 */
	public int getSize() {
		return _fileObject.length();
	}

	/**
	 * Returns the content of the file as a String
	 * 
	 * @return Object that represents the content of the file
	 */
	public Object open() {
		return _fileObject;
	}

	/**
	 * Modify the editing permission of the file. A file content can be made unchangeable by setting this to false
	 *  
	 * @param mode boolean representing the mode of the file, true means file can be edited. false means it can not be edited
	 */
	public void setMode(boolean mode) {
		_mode = mode;
	}
	
	/**
	 * Add additional text to the content of the file
	 * 
	 * @param text The text to be added to the file
	 * @return
	 */
	public boolean append(String text) {
		if(_mode != _MODE_OPEN) {
			// If file editing mode is false we refuse to append to the file.
			return false;
		}

		_fileObject = _fileObject + text;
		
		return true;
	}
	
	/**
	 * String representation of the file
	 * 
	 * @return The content of the file, the actual string
	 */
	public String toString() {
		// Aliasing is OK because String is not mutable.
		return _fileObject;
	}
	

}
