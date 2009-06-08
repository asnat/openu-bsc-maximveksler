import java.util.Arrays;
import java.util.LinkedList;
import java.util.Random;

import junit.framework.TestCase;


public class TestCell extends TestCase {
	public void testCell() {
		Random random = new Random();
		
		int randRow = random.nextInt(); 
		int randCol = random.nextInt();
		
		Cell tested = new Cell(randRow, randCol);
		
		assertEquals(randRow, tested.getCurrRow());
		assertEquals(randCol, tested.getCurrCol());
	}

	public void testSetRowCol() {
		Cell tested = new Cell(0, 0);
		
		tested.setCurrRow(4);
		tested.setCurrCol(0);
		
		Cell next = tested.nextCell(5, 5);
		
		assertEquals(1, next.getCurrRow());
		assertEquals(4, next.getCurrCol());
	}

	public void testPrevNextCell() {
		// Growing columns
		LinkedList<RowCol> _5x1 = new LinkedList<RowCol>(Arrays.asList(
				null, _(0,0), _(1,0), _(2,0), _(3,0), _(4,0),  null
			));

		LinkedList<RowCol> _5x2 = new LinkedList<RowCol>(Arrays.asList(
				null, _(0,0), _(0,1), _(1,0), _(1,1), _(2,0),  _(2,1),
				_(3,0), _(3,1), _(4,0), _(4,1), null
			));

		LinkedList<RowCol> _5x3 = new LinkedList<RowCol>(Arrays.asList(
				null, _(0,0), _(0,1), _(1,0), _(0,2), _(1,1),  _(2,0),
				_(1,2), _(2,1), _(3,0), _(2,2), _(3,1),  _(4,0),
				_(3,2), _(4,1), _(4,2), null
			));

		LinkedList<RowCol> _5x4 = new LinkedList<RowCol>(Arrays.asList(
				null, _(0,0), _(0,1), _(1,0), _(0,2), _(1,1),  _(2,0),
				_(0,3), _(1,2), _(2,1), _(3,0), _(1,3),  _(2,2),
				_(3,1), _(4,0), _(2,3), _(3,2), _(4,1),  _(3,3),
				_(4,2), _(4,3), null
			));

		
		// Growing rows
		LinkedList<RowCol> _1x5 = new LinkedList<RowCol>(Arrays.asList(
				null, _(0,0), _(0,1), _(0,2), _(0,3), _(0,4),  null
			));

		LinkedList<RowCol> _2x5 = new LinkedList<RowCol>(Arrays.asList(
				null, _(0,0), _(0,1), _(1,0), _(0,2), _(1,1),  _(0,3),
				_(1,2), _(0,4), _(1,3), _(1,4), null
			));

		LinkedList<RowCol> _3x5 = new LinkedList<RowCol>(Arrays.asList(
				null, _(0,0), _(0,1), _(1,0), _(0,2), _(1,1),  _(2,0),
				_(0,3), _(1,2), _(2,1), _(0,4), _(1,3),  _(2,2),
				_(1,4), _(2,3), _(2,4), null
			));

		LinkedList<RowCol> _4x5 = new LinkedList<RowCol>(Arrays.asList(
				null, _(0,0), _(0,1), _(1,0), _(0,2), _(1,1),  _(2,0),
				_(0,3), _(1,2), _(2,1), _(3,0), _(0,4),  _(1,3),
				_(2,2), _(3,1), _(1,4), _(2,3), _(3,2),  _(2,4),
				_(3,3), _(3,4), null
			));

		
		// Growing DRUGS
		LinkedList<RowCol> _1x1 = new LinkedList<RowCol>(Arrays.asList(
				null, _(0,0), null
			));

		LinkedList<RowCol> _2x2 = new LinkedList<RowCol>(Arrays.asList(
				null, _(0,0), _(0,1), _(1,0), _(1,1), null
			));

		LinkedList<RowCol> _3x3 = new LinkedList<RowCol>(Arrays.asList(
				null, _(0,0), _(0,1), _(1,0), _(0,2), _(1,1),  _(2,0),
				_(1,2), _(2,1), _(2,2), null
			));

		LinkedList<RowCol> _4x4 = new LinkedList<RowCol>(Arrays.asList(
				null, _(0,0), _(0,1), _(1,0), _(0,2), _(1,1),  _(2,0),
				_(0,3), _(1,2), _(2,1), _(3,0), _(1,3),  _(2,2),
				_(3,1), _(2,3), _(3,2), _(3,3), null
			));

		LinkedList<RowCol> _5x5 = new LinkedList<RowCol>(Arrays.asList(
				null, _(0,0), _(0,1), _(1,0), _(0,2), _(1,1),  _(2,0),
				_(0,3), _(1,2), _(2,1), _(3,0), _(0,4),  _(1,3),
				_(2,2), _(3,1), _(4,0), _(1,4), _(2,3),  _(3,2),
				_(4,1), _(2,4), _(3,3), _(4,2), _(3,4),  _(4,3),
				_(4,4), null
			));

		testForCellBounders(_5x1);
		testForCellBounders(_5x2);
		testForCellBounders(_5x3);
		testForCellBounders(_5x4);

		testForCellBounders(_1x5);
		testForCellBounders(_2x5);
		testForCellBounders(_3x5);
		testForCellBounders(_4x5);
		
		testForCellBounders(_1x1);
		testForCellBounders(_2x2);
		testForCellBounders(_3x3);
		testForCellBounders(_4x4);
		testForCellBounders(_5x5);

	}

	void testForCellBounders(LinkedList<RowCol> expected) {
		// Get last row and last column for test run by fetching 1 before last object.
		RowCol definition = expected.get(expected.size() -2);
		int rows = definition.getRow() + 1;
		int columns = definition.getCol() + 1;
		
		System.out.println("**************************************************************\n"
				+ "TESTING FOR " + rows + " rows, " + columns + " columns" );

		// Fetch starting null
		RowCol previousRowCol = expected.poll();

		// Fetch 0,0 position.		
		RowCol currentRowCol = expected.poll();
		RowCol nextRowCol;
		do {
			int currRow = currentRowCol.getRow();
			int currCol = currentRowCol.getCol();
			Cell tested = new Cell(currRow, currCol);
			
			nextRowCol = expected.poll();
			System.out.print("Current (" + currRow + "," + currCol + ") ::: ");
			
			
			/////////////////////
			// TEST PREVIOUS ////
			/////////////////////
			System.out.print(" PREVIOUS(<--) [[[  Expected:" + "(" + ((previousRowCol != null) ? previousRowCol.getRow() : null) 
			+ "," + ((previousRowCol != null) ? previousRowCol.getCol() : null) + ")");

			Cell previousCell = tested.prevCell(rows, columns);

			System.out.print(" Actual:" + "(" 
					+ ((previousCell != null) ? previousCell.getCurrRow() : null) + "," 
					+ ((previousCell != null) ? previousCell.getCurrCol() : null) + ") ]]]");

			if(previousRowCol == null) {
				assertTrue(previousCell == null);
			} else {
				assertEquals(previousRowCol.getRow(), previousCell.getCurrRow());
				assertEquals(previousRowCol.getCol(), previousCell.getCurrCol());
			}
			
			/////////////////////
			// TEST NEXT ////////
			/////////////////////
			System.out.print(" NEXT(-->) [[[ Expected:" + "(" + ((nextRowCol != null) ? nextRowCol.getRow() : null) 
							+ "," + ((nextRowCol != null) ? nextRowCol.getCol() : null) + ")");

			Cell nextCell = tested.nextCell(rows, columns);

			System.out.print(" Actual:" + "(" 
					+ ((nextCell != null) ? nextCell.getCurrRow() : null) + "," 
					+ ((nextCell != null) ? nextCell.getCurrCol() : null) + ") ]]]");

			if(nextRowCol == null) {
				assertTrue(nextCell == null);
			} else {
				assertEquals(nextRowCol.getRow(), nextCell.getCurrRow());
				assertEquals(nextRowCol.getCol(), nextCell.getCurrCol());
			}
			
			System.out.println("");
			
			// SETUP for next loop
			previousRowCol = currentRowCol;
			currentRowCol = nextRowCol;
		} while(currentRowCol != null);
	}
	
	static RowCol _(int a, int b) {
		return new RowCol(a, b);
	}

}

