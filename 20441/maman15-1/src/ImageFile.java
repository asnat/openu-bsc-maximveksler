/**
 * ImageFile contains image content represented by characters, thus forming and image in ASCII art
 * 
 * ImageFile instance once created is immutable
 * 
 * @author Maxim Veksler 303856983
 */
public class ImageFile extends MyFile {
	/**
	 * The content of this file, which is a text String
	 */
	private char[][] _fileObject;

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
		super(name);
		
		this._fileObject = copyCharMatrix(image);
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
		return _fileObject.length * _fileObject[0].length;
	}

	/**
	 * Get the content of the file, the image object
	 * 
	 * @return Object which can be casted to char[][], this 2 dimensional array is the content of the file which is an ASCII art image
	 */
	public Object open() {
		// We copy the char matrix before returning it. To prevent aliasing and avoid client changing the content of the file.
		return copyCharMatrix(_fileObject);
	}
	
	/**
	 * String representation of the image file
	 *
	 * @return String contains rows terminated by '\n', rows overlap the rows of the ASCII image
	 */
	public String toString() {
		String ret = "";
		
		for(int i = 0; i < _fileObject.length; i++) {
			String lineRet = "";
			for(int j = 0; j < _fileObject[i].length; j++) {
				lineRet += _fileObject[i][j];
			}
			
			ret += lineRet + "\n";
		}
		
		return ret;
	}
	
	
	// ################
	// ### PRIVATE ####
	// ################
	
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
