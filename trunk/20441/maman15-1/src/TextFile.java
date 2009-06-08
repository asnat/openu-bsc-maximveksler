/**
 * A File representing Text data
 * 
 * @author Maxim Veksler
 *
 */
public class TextFile extends MyFile {

	// ####################
	// ### CONSTRUCTOR ####
	// ####################
	
	/**
	 * Construct a Text file with name and text content
	 * 
	 * @param name The name of the file as it is represented in the file system
	 * @param text String representing the content of the file
	 */
	public TextFile(String name, String text) {
		this(name, text, _MODE_OPEN);
	}

	/**
	 * Construct a Text file with name, text content and a editing mode
	 * 
	 * @param name The name of the file as it is represented in the file system
	 * @param text String representing the content of the file
	 * @param mode boolean editing mode. true means file content can be modified, false means it can not
	 */
	public TextFile(String name, String text, boolean mode) {
		super(name, text, mode);
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
		return openAsString().length();
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

		_fileObject = openAsString() + text;
		
		return true;
	}
	
	/**
	 * String representation of the file
	 * 
	 * @return The content of the file, the actual string
	 */
	public String toString() {
		return openAsString();
	}
	
	// ################
	// ### PRIVATE ####
	// ################
	
	/**
	 * Utility method, cast the generic object returned from MyFile.open() to String
	 * 
	 * @return String which is the content of the file
	 */
	protected String openAsString() {
		String ret = (String) super.open();
		return ret;
	}
}
