import java.io.File;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;


public class PrintParsedTestValues {

	/**
	 * @param args
	 */
	public static void main(String[] args) throws Throwable {
		Scanner scanner = new Scanner(new File("mscrap.txt"));
		
		System.out.println("{");
		while(scanner.hasNext()) {
			Scanner valueScanner = new Scanner(scanner.nextLine());
			valueScanner.useDelimiter("\\s+");
			
			List<String> words = new ArrayList<String>();
			while(valueScanner.hasNext()){
				words.add(valueScanner.next());
			}
			
			System.out.print("\t{ ");
			for(int i = words.size(); i >0; i--) {
				System.out.print(words.get(i-1));
				
				if(i>1) {
					System.out.print(", ");
				}
			}
			System.out.print(" },\n");
		}
		
		System.out.println("}");

	}

}
