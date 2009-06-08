package bye;
import bye.MatrixTutor;

// A matrix of real numbers

public class MatrixTutor

{

	// The elements of the matrix

	private double[][] elements;

	// Construct new matrix from table of values

	public MatrixTutor(double[][] elements)

	{

		int height = elements.length;

		int width = elements[0].length;

		this.elements = new double[height][width];

		for (int i = 0; i < height; ++i)

			for (int j = 0; j < width; ++j)

				this.elements[i][j] = elements[i][j];

	}

	// Returns the number of rows of the matrix

	public int numberOfRows() {

		return elements.length;

	}

	// Returns the number of columns of the matrix

	public int numberOfColumns() {

		return elements[0].length;

	}

	// Returns element (i,j) of the matrix

	public double getElement(int i, int j) {

		return elements[i][j];

	}

	// Prints the matrix

	public void printMatrix() {

		for (int i = 0; i < this.numberOfRows(); i++) {

			for (int j = 0; j < this.numberOfColumns(); j++) {

				System.out.print(this.getElement(i, j) + " ");

			}

			System.out.println();

		}

		System.out.println();

	}

	public MatrixTutor matrixMultiply(MatrixTutor a) {
		double[][] result = new double[elements.length][a.numberOfColumns()]; 
		
		for(int mArow = 0; mArow < elements.length; mArow++) {
			for(int mBcol = 0; mBcol < a.numberOfColumns(); mBcol++) {
				if(elements[mArow].length != a.numberOfRows()) {
					System.out.println("Number of rows in matrix b must match number of " +
							" column in matrix a");
					return null;
				}

				
				double scalarCalculation = 0;
				for(int index = 0; index < elements[mArow].length; index++) {
					scalarCalculation += (elements[mArow][index] * a.getElement(index, mBcol)); 
				}
				
				result[mArow][mBcol] = scalarCalculation; 
			}
		}
		
		
		return new MatrixTutor(result);
	}

	public boolean isSymetrical() {
		int n = numberOfRows();
		int m = numberOfColumns();
		
		if(n != m )
			System.out.println("Huston...");

		for(int i = 0; i < n; i++) {
			for(int j = i; j >= 0; j--) {
				if(elements[i][j] != elements[j][i] || elements[(n-1)-i][(n-1)-j] != elements[(n-1)-j][(n-1)-i])
					return false;
			}
		}

		return true;
	}
	
	public MatrixTutor transposed() {
		int n = numberOfRows();
		int m = numberOfColumns();
		double[][] transposed = new double[m][n];
		
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {
				transposed[j][i] =  elements[i][j];
			}
		}
		
		return new MatrixTutor(transposed);
	}
}