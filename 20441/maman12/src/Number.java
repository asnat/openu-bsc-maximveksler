import java.util.Scanner;

/**
 * User input and numeric manipulation logic for integers.
 * 
 * @author Maxim Veksler 303856983
 *
 */
public class Number {
	
	public static void main(String[] args) {
		/////// Utilities ///////
		Scanner scanner = new Scanner(System.in);
		
		/////// CONSTS ///////
		final String INFO_0 = "Please enter a 4 digit number:";
		final String INFO_1 = "1.  Reverse sign."  
			+ "\n2.  Reverse number." 
			+ "\n3.  Reverse sign and number." 
			+ "\nPlease choose an option:";
		final String INFO_2 = "The result is";
		final String ERROR_0 = "Illegal number – you must enter a 4 digit number";
		final String ERROR_1 = "Illegal option – you must choose 1, 2 or 3";

		/////// Runtime status ///////
		boolean isInputValid = true;
		
		////////////
		/// MAIN ///
		////////////
		System.out.println(INFO_0);
		
		// We assume user will input only numeric characters.
		int userInput = scanner.nextInt();
		
		// Check validity of input: must be a 4 digit (base10), (positive || negative) number .
		if(! ((userInput >= 1000 && userInput <= 9999) || (userInput >= -9999 && userInput <= -1000))) {
			isInputValid = false;
		}

		if(!isInputValid) {
			System.out.println(ERROR_0);
		} else {

			System.out.println(INFO_1);
			int userSelection = scanner.nextInt();
			
			int calculatedResult = userInput;
			switch (userSelection) {
			case 3:
			case 2:
				int digit0 = (calculatedResult) 		% 10;  // get the ones digit
				int digit1 = (calculatedResult / 10) 	% 10; // get the tens digit
				int digit2 = (calculatedResult / 100)	% 10; // get the hundreds digit
				int digit3 = (calculatedResult / 1000); // get the thousands digit
				
				// Reconstruct the number with the digits reversed (mirror the number).
				calculatedResult = digit0 * 1000 + digit1 * 100 + digit2 * 10 + digit3;
				
				// case 3 means case 2 + case 1
				// We need to skip case 1 only if user has selected option 2. 
				if(userSelection == 2) {
					break;
				}
			case 1:
				calculatedResult = (-1) * calculatedResult;
				break;
			default:
				// Mark input as invalid in case user makes selection other then 1,2,3.
				isInputValid = false;
				
				break;
			}
			
			if(!isInputValid) {
				System.out.println(ERROR_1);
			} else {
				System.out.println(INFO_2);
				System.out.println(calculatedResult);
			}
		}
	}

} // end of class
