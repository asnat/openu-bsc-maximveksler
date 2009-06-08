
public class Matrix {
	private int rows;
	private int columns;
	private int[][] _mat; // _mat holds the actual values of the cells.
	
	
	// ##########################
	// ##### Constructors #######
	// ##########################

	/**
	 * Construct a new Matrix object by coping all supplied elements to an 
	 * 	instance local array.
	 * 
	 * @param mat Two dimensional array representing the elements and their
	 * 		values consisting the Matrix.
	 */
	public Matrix(int[][] mat) {
		rows = mat.length;
		columns = mat[0].length;
		
		_mat = new int[rows][columns];
		
		// Copy all elements from matrix to an instance local array.
		for(int row = 0; row < rows; row++) {
			for(int column = 0; column < columns; column++) {
				_mat[row][column] = mat[row][column];
			}
		}
	}
	
	
	// ############################
	// ##### Public Methods #######
	// ############################

	/**
	 * Build and return a string representation of the array.
	 * 
	 * @return String where each array row is terminated by a \n,
	 * 	each element inside the row is separated by a \t character.
	 */
	public String toString() {
		String ret = "";
		
		for(int row = 0; row < rows; row++) {
			// Append to the result values between 1 to n-1 row cells.
			for(int column = 0; column < (columns-1); column++) {
				ret = ret + getCellValue(row, column) + "\t"; // values are separated by tab character.
			}
			
			// Append to result the n'th value terminated by a \n (instead of \t).
			ret = ret + getCellValue(row, columns-1) + "\n";
		}
		
		return ret;
	}
	
	/**
	 * Check if matrix is sorted in ascending order, considering diagonal movement pattern as was defined by 
	 * requirements.
	 * 
	 * @return true if matrix is found to be sorted, false if not.
	 */
	public boolean isSorted() {
		// Loop initialization: Set scanner to location 0,0 and load previous value from that location.
		Cell scanPointer = new Cell(0, 0);
		int previousValue = getCellValue(scanPointer);
		
		/*
		 * We check the matrix to be sorted by iterating all cells inside the array, comparing cell values
		 * to the previous cell expecting it to be larger or equal.
		 */
		while((scanPointer = scanPointer.nextCell(rows, columns)) != null) {
			int currentValue = getCellValue(scanPointer);
			if(currentValue < previousValue) {
				// Matrix values should have been sorted from lowest to highest, if a value was found that is 
				// smaller then previous value that means array is not sorted, so we can stop the search here.
				// We do this by returning false.
				return false;
			}
			
			previousValue = currentValue;
		};

		return true;
	}
	
	/**
	 * Sort the matrix in such a way the starting from cell 0,0 moving in diagonal 
	 * pattern the values of the cell will be continues in: First being negative
	 * then being positive (0 is considered positive in the mentioned sort).
	 */
	public void arrangeBySign() {
		Cell lowPointer = new Cell(0, 0);
		Cell scanPointer = new Cell(0, 0);

		/*
		 * The arrangement algorithm is as following:
		 * We scan the array from start to finish (moving in diagonal pattern) seeking for negative values & 
		 * pushing them to the start of the array.
		 * 
		 * This is done using 2 pointer:
		 * We have a pointer to the place where the last negative value was stored (starting at 0,0)
		 * We have a pointer to the current scanned cell.
		 * 
		 * If we identify that the current scanned cell has negative value, we swap the values of the cell pointed by "low"
		 * pointer and the values of the current cell. This ensures that cells from the start of the array will have only
		 * negative values, thus fulfilling task requirements.
		 */
		do {
			if(getCellValue(scanPointer) < 0) { 
				// Found negative value, push it to top of array.
				swapCellValues(scanPointer, lowPointer);
				
				// Progress low pointer to next cell because current cell is "inhabited" by a prober (negative & pessimistic) citizen.
				lowPointer = lowPointer.nextCell(rows, columns);
			}
		} while((scanPointer = scanPointer.nextCell(rows, columns)) != null); // Loop stop condition is scanner pointing beyond array bounds.
	}

	
	// ##################################
	// ####### Private Methods ##########
	// ##################################
	
	/**
	 * Get int value from the Matrix by using Cell instance to represent row, column location.
	 * 
	 * @param cell representing row, column position inside the matrix
	 * 
	 * @return int value of the array pointed by the cell object.
	 */
	private int getCellValue(Cell cell) {
		return getCellValue(cell.getCurrRow(), cell.getCurrCol());
	}

	/**
	 * Get int value from the Matrix by using row, column point location in the array.
	 * 
	 * @param row int specifying row position in the matrix
	 * @param column int specifying column position in the matrix
	 * 
	 * @return int value of the array pointed by the row, column variables.
	 */
	private int getCellValue(int row, int column) {
		return _mat[row][column];
	}
	
	/**
	 * Store in location pointed by cell the supplied value
	 * 
	 * @param cell pointer to array location
	 * @param value int to be stored
	 */
	private void setCellValue(Cell cell, int value) {
		_mat[cell.getCurrRow()][cell.getCurrCol()] = value;
	}
	
	/**
	 * Substitute the values to locations pointed by cell1 and cell2
	 * 
	 * @param cell1 pointer to location 1 in the array
	 * @param cell2 pointer to location 2 in the array
	 */
	private void swapCellValues(Cell cell1, Cell cell2) {
		int cell1Value = getCellValue(cell1);
		
		setCellValue(cell1, getCellValue(cell2));
		setCellValue(cell2, cell1Value);
	}
}
