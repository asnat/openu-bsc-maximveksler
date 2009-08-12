package bye;
import bye.MatrixTutor;
import junit.framework.TestCase;


public class TestMatrix extends TestCase {

	public void testMatrix() {
		System.out.println(1/2);
	}

	public void testNumberOfRows() {
		fail("Not yet implemented"); 
	}

	public void testNumberOfColumns() {
		fail("Not yet implemented");
	}

	public void testGetElement() {
		fail("Not yet implemented");
	}

	public void testPrintMatrix() {
		fail("Not yet implemented"); 
	}

	public void testMatrixMultiply() {
		double[][] matrixAdata = {
				{3,2},
				{4,1},
				{-1,5},
				{0,2}
				};
		MatrixTutor matrixA = new MatrixTutor(matrixAdata);

		double[][] matrixBdata = {
				{1,-1,4},
				{3,2,0}
				};
		MatrixTutor matrixB = new MatrixTutor(matrixBdata);

		MatrixTutor matrixC = matrixA.matrixMultiply(matrixB);
		
		matrixC.printMatrix();
	}

}
