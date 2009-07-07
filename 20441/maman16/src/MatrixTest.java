
import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import static org.junit.Assert.*;



public class MatrixTest {
	Matrix miniMatrix = new Matrix(new int[][] {
			{1, 3},
			{2, 4}
			});

	Matrix smallMatrix = new Matrix(new int[][] {
			{-4, 2, 13, 22},
			{-2, 5, 20, 24},
			{5, 12, 25, 49},
			{9, 13, 25, 57}});
	
	Matrix hugeMatrix = new Matrix(new int[][] {
			{ 1, 3, 9, 11, 33, 35, 41, 43, 129, 131, 137, 139, 161, 163, 169, 171 },
			{ 2, 4, 10, 12, 34, 36, 42, 44, 130, 132, 138, 140, 162, 164, 170, 172 },
			{ 5, 7, 13, 15, 37, 39, 45, 47, 133, 135, 141, 143, 165, 167, 173, 175 },
			{ 6, 8, 14, 16, 38, 40, 46, 48, 134, 136, 142, 144, 166, 168, 174, 176 },
			{ 17, 19, 25, 27, 49, 51, 57, 59, 145, 147, 153, 155, 177, 179, 185, 187 },
			{ 18, 20, 26, 28, 50, 52, 58, 60, 146, 148, 154, 156, 178, 180, 186, 188 },
			{ 21, 23, 29, 31, 53, 55, 61, 63, 149, 151, 157, 159, 181, 183, 189, 191 },
			{ 22, 24, 30, 32, 54, 56, 62, 64, 150, 152, 158, 160, 182, 184, 190, 192 },
			{ 65, 67, 73, 75, 97, 99, 105, 107, 193, 195, 201, 203, 225, 227, 233, 235 },
			{ 66, 68, 74, 76, 98, 100, 106, 108, 194, 196, 202, 204, 226, 228, 234, 236 },
			{ 69, 71, 77, 79, 101, 103, 109, 111, 197, 199, 205, 207, 229, 231, 237, 239 },
			{ 70, 72, 78, 80, 102, 104, 110, 112, 198, 200, 206, 208, 230, 232, 238, 240 },
			{ 81, 83, 89, 91, 113, 115, 121, 123, 209, 211, 217, 219, 241, 243, 249, 251 },
			{ 82, 84, 90, 92, 114, 116, 122, 124, 210, 212, 218, 220, 242, 244, 250, 252 },
			{ 85, 86, 93, 95, 117, 119, 125, 127, 213, 215, 221, 223, 245, 247, 253, 255 },
			{ 86, 88, 94, 96, 118, 120, 126, 128, 214, 216, 222, 224, 246, 248, 254, 256 },
		}
	);
	
	Matrix pitAt0Matrix = new Matrix(new int[][] {
			{ 0, 0, 0, 0, 0, 0},
			{ 1, 0, 1, 1, 0, 0},
			{ 1, 0, 0, 1, 0, 1},
			{ 1, 0, 0, 0, 0, 0},
			{ 1, 0, 1, 1, 0, 0},
			{ 1, 1, 0, 1, 1, 1},
		}
	);

	Matrix pitAt3Matrix = new Matrix(new int[][] {
			{ 0, 1, 0, 1, 1, 0},
			{ 1, 0, 1, 1, 0, 0},
			{ 0, 0, 0, 1, 0, 1},
			{ 0, 0, 0, 0, 0, 0},
			{ 1, 0, 1, 1, 0, 0},
			{ 0, 1, 0, 1, 1, 1},
		}
	);

	Matrix pitAt5Matrix = new Matrix(new int[][] {
			{ 0, 1, 0, 1, 1, 1},
			{ 1, 0, 1, 1, 0, 1},
			{ 0, 0, 0, 1, 0, 1},
			{ 0, 0, 1, 0, 0, 1},
			{ 1, 0, 1, 1, 0, 1},
			{ 0, 0, 0, 0, 0, 0},
		}
	);

	Matrix matrix1Pit = new Matrix(new int[][] {
			{ 0 }
		}
	);

	Matrix matrix1NoPit = new Matrix(new int[][] {
			{ 1 }
		}
	);

	Matrix noPitMatrix = new Matrix(new int[][] {
			{ 0, 1, 0, 1, 1, 0},
			{ 1, 0, 1, 1, 0, 0},
			{ 0, 0, 0, 1, 0, 1},
			{ 0, 0, 1, 1, 1, 0},
			{ 1, 0, 1, 1, 0, 0},
			{ 0, 1, 0, 1, 1, 1},
		}
	);

	@Before
	public void setUp() throws Exception {
	}

	@After
	public void tearDown() throws Exception {
	}

	@Test
	public void testFind() {
		for(int x = -1000; x <= 1000; x++) {
			if(x==87)
				continue;
			if (x >= 1 && x <= 256) 
				assertTrue(hugeMatrix.find(x));
			else 
				assertFalse(hugeMatrix.find(x));
		}

		for(int x = -1000; x <= 1000; x++) {
			if (x >= 1 && x <= 4) 
				assertTrue(miniMatrix.find(x));
			else 
				assertFalse(miniMatrix.find(x));
		}	
	}
	
	@Test
	public void testIsSink() {
		assertTrue(pitAt0Matrix.isSink() == 0);
		assertTrue(pitAt3Matrix.isSink() == 3);
		assertTrue(pitAt5Matrix.isSink() == 5);
		assertTrue(noPitMatrix.isSink() == -1);
		
		assertTrue(matrix1Pit.isSink() == 0);
		assertTrue(matrix1NoPit.isSink() == -1);
	}
}
