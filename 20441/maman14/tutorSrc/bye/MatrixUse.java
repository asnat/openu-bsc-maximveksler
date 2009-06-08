package bye;
import bye.MatrixTutor;

public class MatrixUse

{

        public static void main(String[] args)

        {

            double[][] aElements = {

                { 1.0, 2.0},

                { -2.0, 1.0}

             };

             double[][] bElements = {

                 { 3.0,-1.0},

                 {-1.0, 2.0}

             };

 

             MatrixTutor a,b;

        

             a = new MatrixTutor(aElements);

             b = new MatrixTutor(bElements);

        

             a.printMatrix();

             b.printMatrix();

        }

}

