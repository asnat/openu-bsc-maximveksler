import static org.junit.Assert.*;

import java.lang.reflect.Field;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Random;

import org.junit.Test;


public class TestMatrix {
	@Test
	public final void testMatrix() {
		Random random = new Random();
		int[][] tested = new int[40][1];
		int[][] tested2 = new int[1][40];
		int[][] tested3 = new int[40][40];
		
		for(int i = 1; i < 40; i++) {
			for(int j = 0; j < 1; j++) {
				tested[i][j] = random.nextInt();
			}
		}
		new Matrix(tested);

		
		for(int i = 1; i < 1; i++) {
			for(int j = 0; j < 40; j++) {
				tested2[i][j] = random.nextInt();
			}
		}
		new Matrix(tested2);

		
		for(int i = 1; i < 40; i++) {
			for(int j = 0; j < 40; j++) {
				tested3[i][j] = random.nextInt();
			}
		}
		new Matrix(tested3);
	}

	@Test
	public final void testToString() {
		{
			String expected = "5\t4\t0\t4\n"
				+ "40\t30\t0\t0\n"
				+ "-1\t3\t-1\t0\n";
			
			int[][] expectedArray = {
					{5,4,0,4},
					{40,30,0,0},
					{-1,3,-1,0}
			};
			
			Matrix matrix = new Matrix(expectedArray);
			
			//assertEquals(expected, actual)
			assertEquals(expected, (matrix.toString()));
		}
		
		{
			String expected = "5\t4\t0\t4\n";
			
			int[][] expectedArray = {
					{5,4,0,4}
			};
			
			Matrix matrix = new Matrix(expectedArray);
			
			//assertEquals(expected, actual)
			assertEquals(expected, (matrix.toString()));
			
		}

		{
			String expected = "5\n4\n0\n4\n";
			
			int[][] expectedArray = {
					{5},
					{4},
					{0},
					{4}
			};
			
			Matrix matrix = new Matrix(expectedArray);
			
			//assertEquals(expected, actual)
			assertEquals(expected, (matrix.toString()));
			
		}

	}

	@Test
	public final void testIsSorted() {
		int[][] _1x1 = { {1} };
		sortedChecker(_1x1, true);
		
		int[][] _2x2__1 = { 
				{0, 0},
				{0, 0}};

		int[][] _2x2__2 = { 
				{-0, -0},
				{-0, -0}};

		int[][] _2x2__3 = { 
				{-1, -1},
				{-1, -1}};

		int[][] _2x2__4 = { 
				{1, 1},
				{1, 1}};

		sortedChecker(_2x2__1, true);
		sortedChecker(_2x2__2, true);
		sortedChecker(_2x2__3, true);
		sortedChecker(_2x2__4, true);
		
		int[][] _4_5__1 = {
				{-18, -10, -2, 1, 7},
				{-9, -1, 2, 7, 14},
				{0, 6, 7, 16, 19},
				{6, 12, 18, 29, 37}
		};
		
		sortedChecker(_4_5__1, true);

		int[][] _4_5__2 = {
				{-18, -10, -2, 5, 7},
				{-9, -1, 2, 7, 14},
				{0, 6, 7, 16, 19},
				{6, 12, 18, 29, 37}
		};
		
		sortedChecker(_4_5__1, true);
		sortedChecker(_4_5__2, false);
	}

	void sortedChecker(int[][] matrixArray, boolean expected) {
		Matrix matrix = new Matrix(matrixArray);
		assertTrue(matrix.isSorted() == expected);
	}
	
	@Test
	public final void testArrangeBySign() throws IllegalArgumentException, IllegalAccessException {
		// Test all negatives
		// Test all positives
		// Test all 0
		// Test dimensions 1x1 1x2 2x1 3x3
		
		// But not today ;)
		
		for(int loopI = 0; loopI < 100000; loopI++) {
			LinkedList<RowCol> _5x7 = new LinkedList<RowCol>(Arrays.asList(
					_(0,0), _(0,1), _(1,0), _(0,2), _(1,1), _(2,0),
					_(0,3), _(1,2), _(2,1), _(3,0), _(0,4), _(1,3),
					_(2,2), _(3,1), _(4,0), _(0,5), _(1,4), _(2,3),
					_(3,2), _(4,1), _(0,6), _(1,5), _(2,4), _(3,3), 
					_(4,2), _(1,6), _(2,5), _(3,4), _(4,3), _(2,6), 
					_(3,5), _(4,4), _(3,6), _(4,5), _(4,6)
				));
			
			Random random = new Random();
	
			int[][] tested = new int[5][7];
	
			int nofNegatives = 0;
			for(int i = 0; i< tested.length; i++) {
				for(int j=0; j<tested[0].length; j++) {
					int value = random.nextInt() % 30;
					tested[i][j] = value;
					
					if(value < 0)
						nofNegatives++;
				}
			}
					
			Matrix matrix = new Matrix(tested);
			System.out.println("MATRIX BEFORE SORT:");
			System.out.println(matrix);
			System.out.println("MATRIX AFTER SORT:");
			matrix.arrangeBySign();
			System.out.println(matrix);
			
		    Field fields[] = Matrix.class.getDeclaredFields();
		    int[][] testedSorted = null;
		    
		    for(int i =0; i< fields.length; i++) {
		    	Field field = fields[i];
		    	field.setAccessible(true);
		    	
		    	if(field.getName().equals("_mat")) {
		    		testedSorted = (int[][])field.get(matrix);
		    	}
		    }
	
			for(int i = 0; i < nofNegatives; i++) {
				RowCol rowCol = _5x7.get(i);
				assertFalse(testedSorted[rowCol.getRow()][rowCol.getCol()] >= 0);
			}
	
			for(int i = nofNegatives; i < _5x7.size(); i++) {
				RowCol rowCol = _5x7.get(i);
				assertTrue(testedSorted[rowCol.getRow()][rowCol.getCol()] >= 0);
			}
		}
	}

	static RowCol _(int a, int b) {
		return new RowCol(a, b);
	}

}
