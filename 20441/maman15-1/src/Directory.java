/**
 * Directory is a file that represents a collection of other files
 * 
 * Directories are used to organize in an hierarchy structure 
 * containing 1 root 
 * 
 * @author Maxim Veksler 303856983
 */
public class Directory extends MyFile {
	// _MAX_DIR_ENTRIES is the maximum number of files possible inside a directory
	private static final int _MAX_DIR_ENTRIES = 20;
	
	// Index to the MyFile array showing next empty spot. 
	private int _nextInsertPointer = 0;
	
	// Helper counter that counts the number of regular files inside this directory.
	private int _nofRegularFiles = 0;
	
	/**
	 * The content of this file, which is a text String
	 */
	private MyFile[] _fileObject;

	/**
	 * _mode represents the editing permission of the file
	 * true - has permission, false - does not have permission
	 */
	private boolean _mode;

	// ####################
	// ### CONSTRUCTOR ####
	// ####################

	/**
	 * Construct a new Directory object having editing permission set to enabled
	 * 
	 * @param name The name of the directory as it is represented in the file system
	 */
	public Directory(String name) {
		super(name);
		this._fileObject = new MyFile[_MAX_DIR_ENTRIES];
		this._mode = _MODE_OPEN;
	}

	
	// ###############
	// ### PUBLIC ####
	// ###############

	/**
	 * Get the content of the directory, which is the list of files contained not including sub directories
	 * Only files are returned, not including Directory objects
	 * 
	 * @return Object which can be casted to MyFile[]
	 */
	public Object open() {
		return getDirectoryFiles();
	}

	/**
	 * Count the number of "real" files inside the current directory
	 * 
	 * @return int number of actual files in this directory (not including sub directories)
	 */
	public int getSize() {
		return _nofRegularFiles;
	}


	/**
	 * Add new file to the directory listing
	 * Note: This method consider the current editing mode of this directory
	 * 
	 * @param file The file to be listed under this directory
	 * @return true if addition was successful, false if not
	 */
	public boolean addFile(MyFile file) {
		if(_mode != _MODE_OPEN)
			return false;
		
		// We do not allow adding more entries then defined maximum.
		if((_nextInsertPointer+1) > _MAX_DIR_ENTRIES)
			return false;

		// We fail to add file if it's already listed in the directory.
		if(isFileInList(file))
			return false;
				
		if(isRegularFile(file)) {
			_nofRegularFiles++;
		}
		
		// ALIASING because directory contains references to files.
		_fileObject[_nextInsertPointer++] = file;
		
		return true;
	}
	
	/**
	 * Print the content of this directory (ignoring sub directories), each file in his own row.
	 * Note that only regular files will be printed, Directory entries are ignored.
	 * 
	 * @return String representing the subset of regular files in this directory
	 */
	public String toString() {
		String ret = "";
		
		for(int i = 0; i < _nextInsertPointer; i++) {
			MyFile file = _fileObject[i];
			if(isRegularFile(file))
				ret += file.getName() + "\n"; 
		}
		
		return ret;
	}
	
	/**
	 * Remove a file from this directory list
	 * 
	 * This method will remove the file and return it to the caller
	 * Note this method will not remove the file if directory can't be edited
	 * 
	 * @param name String the name of the requested file to be removed from the directory
	 * @return MyFile object if file was found and removed successfully, null if file wasn't found or couldn't be removed
	 */
	public MyFile removeFile(String name) {
		if(_mode != _MODE_OPEN)
			return null;
		
		// Get the searched file, if such exists.
		MyFile file = popFileJustify(name);
		
		if(file != null) { // If we have found a file by such name.
			if(isRegularFile(file)) {
				// If it's a regular file decrement the regular files counter.
				_nofRegularFiles--;
			}
			
			// Always decrement the insert pointer because a file has left our listing (May he rest in peace).
			_nextInsertPointer--;
		}
		
		// We do not copy the file before returning it because we lose reference 
		// 	to the object, so no double aliasing occurs.
		return file;
	}
	
	/**
	 * Sets the editing mode of the directory.
	 * 
	 * Using this method it's possible to make a directory not changeable
	 * @param mode boolean true means directory can be edited, false means directory can't be edited
	 */
	public void setMode(boolean mode) {
		_mode = mode;
	}
	
	// ################
	// ### PRIVATE ####
	// ################
	
	/**
	 * Utility method, Copy instanced of files objects listed by this directory.
	 * "File Objects" are all files not of type Directory.
	 * Copying is done to prevent aliasing.
	 *  
	 * @return MyFile[] array containing copies of file objects this directory contains. 
	 */
	private MyFile[] getDirectoryFiles() {
		MyFile[] ret = new MyFile[_MAX_DIR_ENTRIES];
		int retPointer = 0;
		
		for(int i = 0; i < _nextInsertPointer; i++) {
			if(isRegularFile(_fileObject[i])) {
				// Aliasing because we return files to client that asks to work with 
				// these files.
				ret[retPointer++] = _fileObject[i];
			}
		}
		
		return ret;
	}

	/**
	 * Check if file already exists in given array of files based on file name.
	 * 
	 * @param directoryEntries Array representing directory files.
	 * @param file The file for which the check will be performed.
	 * 
	 * @return true if file is found in given list of files, fale if not.
	 */
	private boolean isFileInList(MyFile file) {
		/*
		 * The search is executed by calling a method that returns a MyFile 
		 * object, which is searched by name. If no object is returned (null)
		 * that means that file was not found, in our context that means file
		 * does not exist in given array.
		 */
		MyFile foundFile = findFileInList(file.getName());
		
		if(foundFile != null)
			// File found, return true.
			return true;
		else
			// File not found, return false.
			return false;
	}
	
	/**
	 * Search a MyFile object based on it's file name.
	 *  
	 * @param directoryEntries Array representing directory files.
	 * @param fileName The name of file being searched.
	 * 
	 * @return MyFile object if file was found, null if not.
	 */
	private MyFile findFileInList(String fileName) {
		for(int i = 0; i < _nextInsertPointer; i++) {
			MyFile checkedFile = _fileObject[i];
			if(checkedFile.getName().equals(fileName))
				// If file is found (Name matched) quit the loop by returned 
				// the found object.
				return checkedFile;
		}
		
		// Reaching here means no file was found - return null.
		return null;
	}
	
	/**
	 * Utility method, test if this is regular file.
	 * A regular file is any type that extends MyFile which is not a directory.
	 *  
	 * @param file The tested object
	 * @return true if file is not of type Directory, false if it is.
	 */
	private static boolean isRegularFile(MyFile file) {
		return !(file instanceof Directory);
	}
	
	/**
	 * Utility method, pull out an object identifiable by name from a MyFile[] array, then justify remaining objects
	 * 	by shifting left.
	 * 
	 * @param directoryEntries MyFile[] array contains all file entries this directory contains.
	 * @param fileName String the name of the looked up object
	 * @return MyFile object is the object was found and was popped successfully, null if object was not found.
	 */
	private MyFile popFileJustify(String fileName) {
		if(fileName == null)
			return null;
		
		int scanIndex = 0;
		MyFile scannedFile = null;
		
		// First we search for the object, and if found store it in scannedFile variable.
		do {
			MyFile currentFile = _fileObject[scanIndex];
			
			if (currentFile != null && fileName.equals(currentFile.getName())) {
				scannedFile = currentFile;
			} else {
				scanIndex++;	
			}
		} while(scanIndex < _nextInsertPointer && scannedFile == null);
		
		// Next we justify remaining objects to the left.
		if(scannedFile != null) {
			// If match was found we shift all objects left 1 cell from the spot where the object was found at
			while((scanIndex+1) < _nextInsertPointer) { 
				_fileObject[scanIndex] = _fileObject[scanIndex+1];
				scanIndex++;
			}
			
			_fileObject[scanIndex] = null;
		}
		
		return scannedFile;
	}
}
