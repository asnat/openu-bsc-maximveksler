public class maman16_test {
	public static boolean quiz(int a, int b, int n) {
		if (a == 1)
			return (b == 1);
		if (n == b)
			return true;
		if (n > b)
			return false;
		return quiz(a, b, n * a);
	}

	public static void prettyPrintQuiz(int a, int b, int n) {
		System.out.println("For claim quiz(a="+a+",b="+b+",n="+n+") result is: " + quiz(a, b, n));
	}
	public static void main(String[] args) {
		System.out.println("1");
		prettyPrintQuiz(2, 14, 1);
		prettyPrintQuiz(2, 15, 1);
		
		System.out.println("2");
		prettyPrintQuiz(2, 16, 1);
		prettyPrintQuiz(2, 15, 1);

		
		System.out.println("3");
		prettyPrintQuiz(5, 125, 1);
		prettyPrintQuiz(3, 243, 1);
		
		System.out.println("4");
		prettyPrintQuiz(5, 125, 1);
		prettyPrintQuiz(4, 32, 1);
		
		
	}
}
