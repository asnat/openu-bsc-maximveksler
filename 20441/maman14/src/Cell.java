/**
 * 
 * @author Maxim Veksler 303856983
 *
 */
public class Cell {
	/**
	 * Row of cell object in the matrix
	 */
	private int _currRow;
	
	/**
	 * Column of cell in the matrix 
	 */
	private int _currCol;
	
	/**
	 * Holds the distance from start of matrix, representing the
	 * 	number of squares one will need to move (in straight lines on the borders)
	 *  to reach the current (row, col) location.
	 * 	
	 * This is a utility instance variable, it's here to not repeat "_currRow + _currCol" each time this 
	 * 	information is required.
	 */
	private int _distanceFrom0x0 = 0;
	
	/**
	 * Constructor for Cell objects.
	 * 
	 * @param currRow Row position of current cell
	 * @param currCol Column position of current cell
	 */
	public Cell(int currRow, int currCol) {
		this._currRow = currRow;
		this._currCol = currCol;
		
		// Initialize distance variable that will later be used for calculations.
		_distanceFrom0x0 = currRow + currCol;
	}
	
	/**
	 * Set the current row location of Cell object.
	 * 
	 * @param currRow row number 
	 */
	public void setCurrRow(int currRow) {
		// Update distance variable.
		_distanceFrom0x0 = (_distanceFrom0x0 - this._currRow) + currRow; 
		
		this._currRow = currRow;
	}
	
	/**
	 * Retrieve the current row position of cell
	 * 
	 * @return int representing cell row position
	 */
	public int getCurrRow() {
		return _currRow;
	}

	/**
	 * Set the current column location of Cell object.
	 * 
	 * @param currRow column number 
	 */
	public void setCurrCol(int currCol) {
		// Update distance variable.
		_distanceFrom0x0 = (_distanceFrom0x0 - this._currCol) + currCol; 

		this._currCol = currCol;
	}

	/**
	 * Retrieve the current column position of cell
	 * 
	 * @return int representing cell column position
	 */
	public int getCurrCol() {
		return _currCol;
	}
	
	/**
	 * Calculate the next cell according to defined diagonal move pattern
	 * 
	 * @param rows Number of rows in matrix
	 * @param columns Number of columns in matrix
	 * @return new Cell instance representing the next cell, if current cell is the last cell in the matrix a null value is returned.
	 */
	public Cell nextCell(int rows, int columns) {
		// If positioned at last square, return null as there is no possible movement from here. 
		if(_currRow == (rows - 1) && _currCol == (columns - 1))
			return null;
		
		// At first assume we can move in "normal" diagonal direction (down + left).
		int downMovementRow = _currRow + 1;
		int downMovementCol = _currCol - 1;
		if(downMovementRow < rows && downMovementCol >= 0)
			// Row is permitted if it's smaller then array rows size,
			// Column is permitted if it's larger then 0.
			return new Cell(downMovementRow, downMovementCol);
		
		/*
		 * Reaching here means we're in a jump condition.
		 * 
		 * A jump location is calculated as following:
		 * 	a. Calculate traveled distance from location (0,0) 
		 * 	b. Add 1 to it.
		 * 	c. Start movement from cell (0,0) moving right.
		 * 		a. If traveled distance overflows row length, compensate the remaining by moving down remaining delta.
		 */
		if(((columns - 1) - _distanceFrom0x0) > 0) {
			// If we haven't passed distance larger then column that means we jump to row=0, column=X
			return new Cell(0, _distanceFrom0x0 + 1);
		} else {
			// We've passed distance larger then columns, so we jump to last column and down the rows.
			return new Cell(((_distanceFrom0x0 + 1) - (columns - 1)), (columns - 1));
		}
	}
	
	/**
	 * Calculate the previous cell according to defined diagonal move pattern
	 * 
	 * @param rows Number of rows in matrix
	 * @param columns Number of columns in matrix
	 * @return new Cell instance representing the previous cell, if current cell is the first cell in the matrix a null value is returned.
	 */
	public Cell prevCell(int rows, int columns) {
		if(_currRow == 0 && _currCol == 0)
			// If we are in the start of the matrix no move back is possible.
			return null;
		
		// At first assume we can move in "normal" diagonal direction (up + right).
		int upMovementRow = _currRow - 1;
		int upMovementCol = _currCol + 1;
		if(upMovementRow >= 0 && upMovementCol < columns)
			// Row is permitted if it's smaller then array rows size,
			// Column is permitted if it's larger then 0.
			return new Cell(upMovementRow, upMovementCol);

		/*
		 * Reaching here means we're in a jump condition.
		 * 
		 * A jump location is calculated as following:
		 * 	a. Calculate traveled distance from location (0,0) 
		 * 	b. Subtract 1 to it.
		 * 	c. Start movement from cell (0,0) moving down.
		 * 		a. If traveled distance overflows number of rows, compensate the remaining by moving right remaining delta on the last row.
		 */
		if((rows - _distanceFrom0x0) > 0) {
			// If we haven't passed distance larger then number of rows that means we jump to row=X, column=0
			return new Cell(_distanceFrom0x0 - 1, 0);
		} else {
			// We've passed distance larger then number of rows, so we jump to last row and right the columns.
			return new Cell(rows - 1,  ((_distanceFrom0x0 - 1) - (rows - 1)));
		}
	}
}
