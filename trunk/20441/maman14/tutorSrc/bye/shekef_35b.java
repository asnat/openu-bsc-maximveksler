package bye;
import java.util.Scanner;


public class shekef_35b {
	static Scanner scanner = new Scanner(System.in);
	
	public static void main(String[] args) {

		int[] histogram = new int[10];
		
		// read input
		do {
			System.out.print("put int:");
			if(!scanner.hasNextInt())
				break;
			int i = scanner.nextInt();
			
			histogram[(i-1)/10] = histogram[(i-1)/10] + 1;
		} while(true);

		// print output
		for(int i = 0; i < histogram.length; i++) {
			System.out.print(i + "\t");
			for(int j = 0; j < histogram[i]; j++) {
				System.out.print('*');
			}
			System.out.println();
		}
	}
}
