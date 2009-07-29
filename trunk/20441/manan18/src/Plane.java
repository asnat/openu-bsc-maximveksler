
public class Plane {
	class Rise {
		public Rise(double meter) {
			
		}
	}
	
	public static void main(String[] args) {
		Plane plane = new Plane();
		Rise r = plane.new Rise(32.3);
		
		
		// OR:
		(new Plane()).new Rise(32.2);
	}
}
