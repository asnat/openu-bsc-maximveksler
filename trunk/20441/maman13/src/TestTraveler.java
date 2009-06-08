import junit.framework.TestCase;

public class TestTraveler extends TestCase {

	public void testTraveler() {
		fail("Not yet implemented");
	}

	public void testCheckTravel() {
		fail("Not yet implemented");
	}

	public void testIsPayed() {
		fail("Not yet implemented");
	}

	public void testPay() {
		fail("Not yet implemented");
	}

	public void testToString() {
		fail("Not yet implemented");
	}

	public static void main(String[] args) {
		Passport passport1 = new Passport("Moshe Cohen", 306914, new Date(12,
				10, 2003));
		Passport passport2 = new Passport("Lila Cohen ", 306915, new Date(14,
				10, 2003));
		Date travelDate = new Date(13, 10, 2003);
		Traveler t1 = new Traveler(passport1, true);
		Traveler t2 = new Traveler(passport2, true);
		if (t1.checkTravel(travelDate))
			System.out.println(t1);
		if (t2.checkTravel(travelDate))
			System.out.println(t2);
	}
}
