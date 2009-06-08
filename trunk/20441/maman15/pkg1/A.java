package pkg1;

public class A {
	//private int privateInt;
	protected int protectedInt;
	public int publicInt;
	int packagePrivateInt;
	
	//protected private int protectedPrivateInt;
	
	public static void main(String[] args) {
		
		A a = new A();
		
		if(a instanceof A) 
			System.out.println("TRUE");
		else
			System.out.println("FALSE");
	}
}
