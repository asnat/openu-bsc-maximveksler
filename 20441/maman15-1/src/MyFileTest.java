import static org.junit.Assert.*;

import java.util.Random;

import org.junit.Before;
import org.junit.Test;

public class MyFileTest {
	String name;
	byte[] fileContent = new byte[100];
	
	@Before
	public void setUp() throws Exception {
		Random random = new Random();
		
		name = "" + random.nextLong();
		random.nextBytes(fileContent);
	}
	
	@Test
	/**
	 * Test that we can create the file and that it builds with our name.
	 */
	public final void testMyFileString() {
		MyFile myFile = new MyFileClassTest(name);
		assertTrue(myFile.getName().equals(name));
		assertTrue(myFile.open() == null);
		assertTrue(myFile._mode == true);
	}

	@Test
	/**
	 * Test that we can create the file object with our user data.
	 */
	public final void testMyFileStringObject() {
		MyFile myFile = new MyFileClassTest(name, fileContent);
		
		assertTrue(myFile.getName().equals(name));
		assertArrayEquals(fileContent, (byte[])myFile.open());
	}

	@Test
	/**
	 * Test we can create the file object with our user data and boolean flag.
	 */
	public final void testMyFileStringObjectBoolean() {
		MyFile myFile = new MyFileClassTest(name, fileContent, true);
		
		assertTrue(myFile.getName().equals(name));
		assertArrayEquals(fileContent, (byte[])myFile.open());
		assertTrue(myFile._mode == true);

		MyFile myFile2 = new MyFileClassTest(name, fileContent, false);
		
		assertTrue(myFile2.getName().equals(name));
		assertArrayEquals(fileContent, (byte[])myFile2.open());
		assertTrue(myFile2._mode == false);
	}

	/**
	 * Test we can create the file object with our user data and boolean flag.
	 */
	public final void testMyFileMyFile() {
		fail();
	}

	class MyFileClassTest extends MyFile {
		public MyFileClassTest(String name, Object fileObject, boolean mode) {
			super(name, fileObject, mode);
		}

		public MyFileClassTest(String name, Object fileObject) {
			super(name, fileObject);
		}

		public MyFileClassTest(String name) {
			super(name);
		}

		@Override
		public int getSize() {
			return 0;
		}
	}

}
