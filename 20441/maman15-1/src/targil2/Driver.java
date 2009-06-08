package targil2;

public class Driver { 
	   public static void main (String [] args) { 
	      C c = new C(); 
	      D d = new D(); 
	      E e = new E(); 
	      F f = new F(); 
	      G g = new G(); 


	      System.out.println (((G)f).b());
	   } 
	}