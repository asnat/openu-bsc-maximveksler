import static org.junit.Assert.*;

import java.util.Random;

import org.junit.Before;
import org.junit.Test;


public class TextFileTest {
	String name;
	
	String appendedText;
	String text1;
	String text2;
	String text3;

	TextFile testTextFileStringString;
	TextFile testTextFileStringStringBoolean;
	
	@Before
	public void setUp() throws Exception {
		Random random = new Random();
		
		name = random.nextLong() + "";
		appendedText = random.nextLong() + "";
		
		text1 = appendedText;
		text2 = appendedText + appendedText;
		text3 = appendedText + appendedText + appendedText;
		
		testTextFileStringString = new TextFile(name, text1);
		testTextFileStringStringBoolean = new TextFile(name, text2, false);
	}

	@Test
	public final void testGetSize() {
		assertTrue(testTextFileStringString.getSize() == text1.length());
		assertTrue(testTextFileStringStringBoolean.getSize() == text2.length());
	}

	@Test
	public final void testTextFileStringString() {
		assertTrue(name.equals(testTextFileStringString.getName()));
		assertTrue(text1.equals(testTextFileStringString.open()));
//		assertTrue(testTextFileStringString._mode == true);
	}

	@Test
	public final void testTextFileStringStringBoolean() {
		assertTrue(name.equals(testTextFileStringStringBoolean.getName()));
		assertTrue(text2.equals(testTextFileStringStringBoolean.open()));
//		assertTrue(testTextFileStringStringBoolean._mode == false);
	}

	@Test
	public final void testSetMode() {
//		assertTrue(testTextFileStringString._mode == true);
//		
//		testTextFileStringString.setMode(false);
//		assertTrue(testTextFileStringString._mode == false);
//		
//		testTextFileStringString.setMode(true);
//		assertTrue(testTextFileStringString._mode == true);
	}

	@Test
	public final void testAppend() {
		assertTrue(text1.equals(testTextFileStringString.open()));
		
		
		assertTrue(testTextFileStringString.append(appendedText));
		assertTrue(text2.equals(testTextFileStringString.open()));

		assertTrue(testTextFileStringString.append(appendedText));
		assertTrue(text3.equals(testTextFileStringString.open()));

		testTextFileStringString.setMode(false);
		assertFalse(testTextFileStringString.append(appendedText));
		assertTrue(text3.equals(testTextFileStringString.open()));
	}

	@Test
	public final void testToString() {
		String txtStr = testTextFileStringStringBoolean.toString();
		assertTrue(txtStr.equals(text2));
	}

	public final void testTextFileTextFile() {
		fail();
	}

}
