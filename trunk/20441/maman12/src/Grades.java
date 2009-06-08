import java.util.Scanner;

/**
 * Calculate student final grade based on relative portion of submitted tasks.
 *  
 * @author Maxim Veksler 303856983
 */
public class Grades {

	public static void main(String[] args) {
		// Utility methods 
		Scanner scanner = new Scanner(System.in);

		// Grades input from user.
		double tasksGradeSum = 0;
		double examGrade = 0;

		// Counter implying number of tasks submitted.
		int nofSubmittedGrades = 0;
		
		/*
		 * Data input block. Get all known grades.
		 */
		double userInput;
		
		System.out.print("Please enter exercise number 1 grade: ");
		userInput = scanner.nextDouble();
		if(userInput != -1) {
			tasksGradeSum = tasksGradeSum + userInput;
			nofSubmittedGrades++;
		}

		System.out.print("Please enter exercise number 2 grade: ");
		userInput = scanner.nextDouble();
		if(userInput != -1) {
			tasksGradeSum = tasksGradeSum + userInput;
			nofSubmittedGrades++;
		}

		System.out.print("Please enter exercise number 3 grade: ");
		userInput = scanner.nextDouble();
		if(userInput != -1) {
			tasksGradeSum = tasksGradeSum + userInput;
			nofSubmittedGrades++;
		}

		System.out.print("Please enter exercise number 4 grade: ");
		userInput = scanner.nextDouble();
		if(userInput != -1) {
			tasksGradeSum = tasksGradeSum + userInput;
			nofSubmittedGrades++;
		}

		System.out.print("Please enter exercise number 5 grade: ");
		userInput = scanner.nextDouble();
		if(userInput != -1) {
			tasksGradeSum = tasksGradeSum + userInput;
			nofSubmittedGrades++;
		}

		System.out.print("Please enter final exam’s grade: ");
		examGrade = scanner.nextDouble();
		
		double finalGrade = 0;

		// Verify student has submitted at least 3 exercises + has taken the final exam.
		// If either one of the mentioned conditions is false, student gets grade 0 by default.
		if(nofSubmittedGrades < 3 || examGrade == -1) {
			finalGrade = 0;
		} else {
			// Student passed required criteria and is eligible for grade calculation.

			// Calculation is given by the formula: 5% out of sum of tasks grade. + relative percentage 
			// 	out of exam grade.
			int examPercentage = 100 - (nofSubmittedGrades * 5);
			finalGrade = ((5 * tasksGradeSum) + (examPercentage * examGrade)) / 100;
		}

		System.out.println(finalGrade);
	}
} // end of class
