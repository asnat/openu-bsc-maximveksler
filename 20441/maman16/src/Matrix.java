/**
 * A matrix of integer numbers
 * 
 * @author www.openu.ac.il - Course 20441
 * @author Maxim Veksler 303856983
 */
public class Matrix {
 
    // The elements of the matrix
    private int[][] _elements;

    /**
     * Efficiently decide if value exists within a sorted matrix.
     * 
     * @param x int the searched value
     * 
     * @return true if value was found, false if not.
     */
    public boolean find(int x) {
    	//System.out.println("Seeked value: " + x);
    	int n = getNumberOfRows();
    	
    	// Call boolean recursive search. 
    	return find(x, n, n/2, n);
    }

    /**
     * Boolean search within a sorted (by specifications described order) matrix.
     * 
     * The search algorithm is given as following:
     * 		0. We look at a large square as a collection of 4 smaller square.
     * 		1. A recursive search is possible one if 1 of four smaller squares is selected.
     * 		2. We selected what square interests us by checking against the middle of the 
     * 			current 4 squares (end of 2nd square) to decide what 2 squares are relevant
     * 			for us, then by checking the middle of the 2 squares to zero on our target.
     * 		3. The search is boolean, based on the fact the that whole matrix has been sorted.
     * 
     * The complexity of the method is log2(n), this is because we reduce the problem by half on each iteration.
     * 
     * @param x The value we are searching
     * @param checkpointRow int current cell row to check during boolean search
     * @param checkpointCol int current cell col to check during boolean search
     * @param n The size of reduced problem space
     * 
     * @return true if value was found, false if not.
     */
    private boolean find(int x, 
    		int checkpointRow, int checkpointCol, 
    		int n) {
    	
    	/*
    	 * Compare current position against x target value.
    	 * NOTE: This comparison is between 2 blocked of 2 squares to selected what block interests us.
    	 */
    	int compareResult = compareX(x, checkpointRow-1, checkpointCol-1);
    	
    	//System.out.println("checkpointRow=" + checkpointRow + ", checkpointCol="+ checkpointCol + ")");
    	
    	int recRow = 0;
    	int recCol = 0;
    	
    	if(compareResult == 0)
    		// current position equal x, value was found!
    		return true;
    	else if(n < 2) {
    		// If n is smaller then 2 that means we have consumed all possible checks.
    		// If we didn't return on the previous equality condition we didn't found our value
    		// so we fail by returning false.
    		return false;
    	}    	
    		
		/*
		 * We need to jump to the middle of the selected 2 squares, 
		 * 	this is done by going to the last cell of the upper square.
		 */
		recRow = checkpointRow - n/2;
    	
		/*
		 * Now to decide what 2 squares we are interested in (left or right).
		 */
    	if(compareResult > 0) {
    		// Choose upper half
    		recCol = checkpointCol + n/2;
    	} else { //(compareResult < 0)
    		// Choose lower half
    		recCol = checkpointCol;
    	}

		
    	//System.out.println("recRow=" + recRow + ", recCol="+ recCol + ")");

    	/*
    	 * Compare current position against x target value.
    	 * NOTE: This comparison is between 2 squares to selected what square we will be making our recursive call into.
    	 */
    	compareResult = compareX(x, recRow-1, recCol-1);

    	if(compareResult < 0) {
    		// Choose lower square
    		return find(x, recRow, recCol - n/4, n/2);
    	} else if(compareResult > 0) {
    		// Choose upper square
    		return find(x, recRow + n/2, recCol - n/4, n/2);
		} else { //compareResult == 0
    		// current position equal x, value was found!
			return true;
		}
    }
    
    /**
     * Compares value of given x with a (row,col) position in the matrix.
     * 
     * @param x int value being checked
     * @param rowPos int specifying matrix row
     * @param colPos int specifying matrix column
     * 
     * @return negative if x is smaller then value, positive if x is larger. If values are equal 0 is returned.
     */
    private int compareX(int x, int rowPos, int colPos) {
    	return x - _elements[rowPos][colPos];
    }
    
    /**
     * Search in a matrix of 1's and 0's for a sink position. A sink position is defined as such:
     * 	All values in row k are 0, all values in column k are 1 (except element [k][k]).
     *  
     * @return int representing found k value, -1 if no such position was found.
     */
    public int isSink() {
    	// By default boolean arrays are initialized to false
    	boolean[] rowsWith1 = new boolean[getNumberOfRows()];
    	boolean[] columnsWith0 = new boolean[getNumberOfColumns()];

    	return isSink(0, rowsWith1, columnsWith0);
    	
    }
    
    /**
     * Search recursively in efficiency of O(n) for a sink position. 
     * See documentation of isSink() for a definition of a "sink" position.  
     * 
     * 
     * The seeking algorithm is as following:
     * 	Preparations: Create 2 arrays size n each. These arrays will be used to index what rows & columns remain in valid state
     * 					to be considered as sink candidate.
     * 
     * 		Steps:
     * 			0. Check if current row || current column hasn't been invalidated as k position based on the 2 arrays described above.
     * 			1. For each k check all cells in current row ([k][0..n-1]) and all rows in current cell ([0..n-1][k]) marking,
     * 				we are seeking for both validness of current sink and canceling out future sinks as we continue the run.
     * 			2. If sink found return it, else recurse progressing k by 1.
     * 
     * @param k int the current tested position for a sink. 
     * @param rowsWith1 boolean[] array notifying what rows a 1 was found at, thus invalidating current k as sink.
     * @param columnsWith0 boolean[] array notifying what columns a 0 was found at, thus invalidating current k as sink. 
     * 
     * @return int k value if k is found as a valid sink, if no sink found -1. 
     */
    private int isSink(int k, boolean[] rowsWith1, boolean[] columnsWith0) {
    	int n = getNumberOfRows();
    	
    	boolean rowValid = true;
    	boolean columnValid = true;
    	
    	/*
    	 * Recursion forced stop condition, we checked all possible sink locations.
    	 */
    	if(k >= n)
    		return -1;
    	
    	/* 
    	 * If from previous check we found that some row contains a value
    	 * that conflicts we are requirements we skip to next sink location
    	 * without verifying any logic at all.
    	 */
    	if(rowsWith1[k] == true || columnsWith0[k] == true)
    		return isSink(k+1, rowsWith1, columnsWith0);

    	// Check current row
    	for(int i = 0; i < n; i++) {
    		if (_elements[k][i] == 0) {
    			columnsWith0[i] = true;
    		} else {
    			rowValid = false;
    		}
    	}

    	// Check current column
    	for(int i = 0; i < n; i++) {
    		if (_elements[i][k] == 1) {
    			rowsWith1[i] = true;
    		} else {
    			// sink should contain a value of 0, so if current location is sink it's OK it's not 1.
    			if(i != k)
    				columnValid = false;
    		}
    	}
    	
    	if(rowValid && columnValid) {
    		return k;
    	} else {
    		return isSink(k+1, rowsWith1, columnsWith0);
    	}
    }
    
    
    // ###################################
    // ##     OPEN University Code 		##
    // ###################################
    
    /**
     * Constructs a new matrix from a table of values.
     * @param elements a two dimensional array of integers
     */
    public Matrix(int[][] elements) {
       
        _elements = new int[elements.length][elements[0].length];
        for (int i = 0; i <elements.length; i++){
            for (int j = 0; j < elements[0].length; j++){
                _elements[i][j] = elements[i][j];
            }
        }
    }
    
    /**
     * Constructs a new matrix with a given number of rows and columns.
     * Constructs the matrix if rows and columns are positive numbers.
     * @param rows a positive number
     * @param columns a positive number
     */
    public Matrix(int rows, int columns){
        if (rows>0&&columns>0)
              _elements = new int[rows][columns];
        
    }
    
    /**
     * 
     * Returns the number of rows  the matrix has.
     * @return the number of rows the matrix has
     */
    public int getNumberOfRows() {
        return _elements.length;
    }
   
    

    /**
     **Returns the number of columns the matrix has.   
     * @return the number of columns the matrix has
     */
    public int getNumberOfColumns() {
        return _elements[0].length;
    }

    /**
     * Returns the value of a given index.
     * If row or column not in matrix bounds 12345 is returned.
     * @return the value of a given index or 12345 if indexes not valid
     * @param row the row number
     * @param column the column number
     */
    public int getElement(int row, int column){
        if(isValid(row,column))
              return _elements[row][column];
        return 12345;      
    }
    
    /**
     * Returns the copy of this two dimentional array.
     * @return reference to the copy of this two dimentional array
     */
    public int[][] getAllElements(){
        int[][] copyElements =  new int[_elements.length][_elements[0].length];
        for (int i = 0; i <_elements.length; i++){
            for (int j = 0; j < _elements[0].length; j++){
                copyElements[i][j] = _elements[i][j];
            }
        }
        return copyElements;
    }
    // check if row and column valid
    private boolean isValid(int row , int col)
    {
        return (((row>-1)&&(row<_elements.length)) &&
                         ((col>-1)&&(col<_elements[0].length)));
    }
    /**
     * Sets the value of a given index to a given value.
     * If the row or column are in the matrix bounds the value is changed.
     * @param row the row number
     * @param column the column number
     * @param value the new value
     */
    public void setElement(int row, int column, int value){
        if(isValid(row,column))
             _elements[row][column] = value;
    }
    
    
    /**
     *Creates a string representation of the matrix.
     * @return a String representation of this matrix
     */
    public String toString(){
        String  buffer = "";
        for (int i = 0; i < getNumberOfRows(); i++){
            for (int j = 0; j < getNumberOfColumns(); j++){
                buffer = buffer + getElement(i,j) + "\t";
            }
            buffer += "\n";
        }
        return buffer;          
    }
    
}