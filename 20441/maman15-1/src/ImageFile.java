/**
 * ImageFile contains image content represented by characters, thus forming and image in ASCII art
 * 
 * ImageFile instance once created is immutable
 * 
 * @author Maxim Veksler 303856983
 */
public class ImageFile extends MyFile {

	// ####################
	// ### CONSTRUCTOR ####
	// ####################

	/**
	 * Construct ImageFile object from the supplied char array
	 * 
	 * @param name String representing the name of the file as it is stored in the file system
	 * @param image 2 dimensional char matrix representing the content of the file (the actual ASCII art image)
	 */
	public ImageFile(String name, char[][] image) {
		this(name, copyCharMatrix(image), _MODE_CLOSED);
	}

	/**
	 * Construct ImageFile object from the supplied char array
	 * 
	 * @param name String representing the name of the file as it is stored in the file system
	 * @param image 2 dimensional char matrix representing the content of the file (the actual ASCII art image)
	 * @param mode File editing mode, for images this should always be false
	 */
	protected ImageFile(String name, char[][] image, boolean mode) {
		// Note we do not copy the char matrix here because this is internal API and we trust the caller to do the copying
		// for us correctly.
		super(name, image, mode);
	}
	
	// ###############
	// ### PUBLIC ####
	// ###############

	/**
	 * Calculate the size of the image.
	 * 
	 * @return int for the size of the ascii image, the size is the number of bytes.
	 */
	public int getSize() {
		char[][] fObject = openAsCharMatrix();
		return fObject.length * fObject[0].length;
	}

	/**
	 * Get the content of the file, the image object
	 * 
	 * @return Object which can be casted to char[][], this 2 dimensional array is the content of the file which is an ASCII art image
	 */
	public Object open() {
		// We copy the char matrix before returning it. To prevent aliasing.
		return copyCharMatrix((char[][])super.open());
	}
	
	/**
	 * String representation of the image file
	 *
	 * @return String contains rows terminated by '\n', rows overlap the rows of the ASCII image
	 */
	public String toString() {
		String ret = "";
		char[][] iter = openAsCharMatrix();
		
		for(int i = 0; i < iter.length; i++) {
			String lineRet = "";
			for(int j = 0; j < iter[i].length; j++) {
				lineRet += iter[i][j];
			}
			
			ret += lineRet + "\n";
		}
		
		return ret;
	}
	// ################
	// ### PRIVATE ####
	// ################
	
	/**
	 * Utility method to cast the Object of the file to char[][]
	 * 
	 * @return char[][] which is the content of the file
	 */
	protected char[][] openAsCharMatrix() {
		char[][] ret = (char[][]) super.open();
		return ret;
	}

	/**
	 * Utility method to copy a 2 dimensional char matrix
	 * 
	 * @param matrix The source char[][] array
	 * @return char[][] which is the copied instance of the original char[][]
	 */
	private static char[][] copyCharMatrix(char[][] matrix) {
		char[][] fileObject = new char[matrix.length][matrix[0].length];
		for(int i = 0; i < matrix.length; i++) {
			for(int j = 0; j < matrix[i].length; j++) {
				fileObject[i][j] = matrix[i][j];
			}
		}
		
		return fileObject;
	}
}
