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
	
	// ####################
	// ### CONSTRUCTOR ####
	// ####################

	/**
	 * Construct a new Directory object having editing permission set to enabled
	 * 
	 * @param name The name of the directory as it is represented in the file system
	 */
	public Directory(String name) {
		super(name, new MyFile[_MAX_DIR_ENTRIES], _MODE_OPEN);
	}

	/**
	 * Construct Directory object from the supplied name, content and editing mode
	 * 
	 * @param name The name of the directory as it is represented in the file system
	 * @param directoryFiles The content of this directory, a list of files
	 * @param mode The editing mode of the directory
	 */
	protected Directory(String name, MyFile[] directoryFiles, boolean mode) {
		super(name, directoryFiles, mode);
	}

	// ###############
	// ### PUBLIC ####
	// ###############

	/**
	 * Count the number of "real" files inside the current directory
	 * 
	 * @return int number of actual files in this directory (not including sub directories)
	 */
	public int getSize() {
		return _nofRegularFiles;
	}

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

		MyFile[] directoryEntries = openAsDirectory();

		// We fail to add file if it's already listed in the directory.
		if(isFileInList(directoryEntries, file))
			return false;
				
		if(isRegularFile(file)) {
			_nofRegularFiles++;
		}
			
		directoryEntries[_nextInsertPointer++] = createCopy(file);
		
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
		
		MyFile[] directoryEntries = openAsDirectory();
		
		for(int i = 0; i < _nextInsertPointer; i++) {
			MyFile file = directoryEntries[i];
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
		
		MyFile file = popFileJustify(openAsDirectory(), name);
		
		if(file != null) {
			if(isRegularFile(file)) {
				_nofRegularFiles--;
			}
			
			_nextInsertPointer--;
		}
		
		// We do not copy the file before returning it because we lose reference to the object, so no double aliasing occurs.
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
	 * Utility method, cast the generic object returned from MyFile.open() to MyFile[]
	 * 
	 * @return MyFile[] which is the content of the directory
	 */
	protected MyFile[] openAsDirectory() {
		MyFile[] ret = (MyFile[]) super.open();
		return ret;
	}

	/**
	 * Utility method, Copy instanced of files objects listed by this directory.
	 * "File Objects" are all files not of type Directory.
	 * Copying is done to prevent aliasing.
	 *  
	 * @return MyFile[] array containing copies of file objects this directory contains. 
	 */
	private MyFile[] getDirectoryFiles() {
		MyFile[] files = openAsDirectory();

		MyFile[] ret = new MyFile[_MAX_DIR_ENTRIES];
		int retPointer = 0;
		
		for(int i = 0; i < _nextInsertPointer; i++) {
			if(isRegularFile(files[i])) {
				ret[retPointer++] = createCopy(files[i]);
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
	private boolean isFileInList(MyFile[] directoryEntries, MyFile file) {
		/*
		 * The search is executed by calling a method that returns a MyFile 
		 * object, which is searched by name. If no object is returned (null)
		 * that means that file was not found, in our context that means file
		 * does not exist in given array.
		 */
		MyFile foundFile = findFileInList(directoryEntries, file.getName());
		
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
	private MyFile findFileInList(MyFile[] directoryEntries, String fileName) {
		for(int i = 0; i < _nextInsertPointer; i++) {
			MyFile checkedFile = directoryEntries[i];
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
	private MyFile popFileJustify(MyFile[] directoryEntries, String fileName) {
		if(fileName == null)
			return null;
		
		int scanIndex = 0;
		MyFile scannedFile = null;
		
		// First we search for the object, and if found store it in scannedFile variable.
		do {
			MyFile currentFile = directoryEntries[scanIndex];
			
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
				directoryEntries[scanIndex] = directoryEntries[scanIndex+1];
				scanIndex++;
			}
			
			directoryEntries[scanIndex] = null;
		}
		
		return scannedFile;
	}
	
	/**
	 * Utility method, return a copied object (recursively) of the supplied source.
	 * 
	 * This utility method will handle copying of Text, Image and Directory Files.
	 * For Image and Text it will simply created new instances of the matching objects
	 * 	then return them, for Directory it will recurse into the directory (and sub 
	 * 	directories if exist) and return the whole copied tree.
	 * 
	 * @param source a ImageFile, TextFile or Directory from which we will be copying
	 * @return a copied ImageFile, TextFile or Directory file which is a perfect replica of the supplied source.
	 */
	private static MyFile createCopy(MyFile source) {
		/*
		 * Note, it's possible that if we were to define "complete" copy of the MyFile object we would 
		 * need each object to implement clone(), this is because access properties of other "types"
		 * of files from the directory file is incorrect. It's possible (for ex.) that someone would  
		 * further extend ImageFile to ColorImageFile where he would save the color of each char. Our  
		 * Directory Class knows how to copy TextFile, ImageFile and Directory - So it would fail to 
		 * correctly copy ColorImageFile leading to information loss. Not mentioning the Directory 
		 * should be loosely connected to other types of MyFile class hierarchy Classes.
		 * 
		 * Thereof, we copy the file objects here knowing that a better solution is possible.
		 */

		MyFile target = null;
		
		if(source instanceof TextFile) {
			target = new TextFile(source.getName(), (String)source.open(), source._mode);
		} else if(source instanceof ImageFile) {
			target = new ImageFile(source.getName(), (char[][])source.open(), source._mode);
		} else {
			// File is a directory
			Directory sourceDirectory = (Directory)source;
			MyFile[] sourceDirectoryFiles = sourceDirectory.openAsDirectory();
			
			MyFile[] targetDirectoryFiles = new MyFile[_MAX_DIR_ENTRIES];
			
			for(int i = 0; i < sourceDirectory._nextInsertPointer; i++) {
				targetDirectoryFiles[i] = createCopy(sourceDirectoryFiles[i]); // Note, call to createCopy is recursive.
			}
			
			target = new Directory(source.getName(), targetDirectoryFiles, source._mode);
			
			Directory targetDirectory = (Directory)target;
			targetDirectory._nextInsertPointer = sourceDirectory._nextInsertPointer;
			targetDirectory._nofRegularFiles = sourceDirectory._nofRegularFiles;
			
		}
		
		return target;
	}
}
