/**
 * A matrix of integer numbers
 */
public class Matrix {
 
    // The elements of the matrix
    private int[][] _elements;

    public boolean find(int x) {
    	int n = getNumberOfRows();
    	return find(x, n, n/2, n);
    }

    private boolean find(int x, 
    		int checkpointRow, int checkpointCol, 
    		int n) {
    	
    	int compareResult = compareX(x, checkpointRow-1, checkpointCol-1);
    	
    	System.out.println("checkpointRow=" + checkpointRow + ", checkpointCol="+ checkpointCol + ")");
    	
    	if(compareResult == 0)
    		return true;
    	else if(n < 2) {
    		System.out.println("REACHED FINAL CHECK");
    	} else if(compareResult > 0) {
    		// Choose upper half
    		int recRow = checkpointRow - n/2;
    		int recCol = checkpointCol + n/2;
    		
        	System.out.println("recRow=" + recRow + ", recCol="+ recCol + ")");

    		if(x < _elements[recRow-1][recCol-1]) {
        		find(x, recRow, recCol - n/4, n/2);
    		} else {
        		find(x, recRow + n/2, recCol - n/4, n/2);
    		}
    	} else { //(compareResult < 0)
    		// Choose lower half
    		
//    		find(x, 
//    				checkpointCol, checkpointRow/2,
//    				rowOffset, colOffset,
//    				n/2, ++depth);
    	}
    	
    	return false;
    }
    
    /**
     * Compares value of given x with a (row,col) position in the matrix.
     * 
     * @param x int value being checked
     * @param rowPos int specifying matrix row
     * @param colPos int specifying column
     * 
     * @return negative if x is smaller then value, positive if x is larger. If values are equal 0 is returned.
     */
    private int compareX(int x, int rowPos, int colPos) {
    	return x - _elements[rowPos][colPos];
    }
    
    
    /**
     * Constructs a new matrix from a table of values.
     * @param elements a two dimentional array of integers
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