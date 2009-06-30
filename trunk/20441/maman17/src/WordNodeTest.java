import static org.junit.Assert.*;

import org.junit.Test;


public class WordNodeTest {

	@Test
	public void testWordNode() {
		fail("Not yet implemented");
	}

	@Test
	public void testGetWord() {
		fail("Not yet implemented");
	}

	@Test
	public void testGetWordFirstChar() {
		fail("Not yet implemented");
	}

	@Test
	public void testGetNext() {
		fail("Not yet implemented");
	}

	@Test
	public void testGetOccurrences() {
		fail("Not yet implemented");
	}

	@Test
	public void testMergeSort() {
		fail("Not yet implemented");
	}

	@Test
	public void testCompareTo() {
		// a == a 
		assertEquals("a".compareTo("a"), comp("a", "a"));
		// a == ab
		assertEquals("a".compareTo("ab"), comp("a", "ab"));
		
		// a == ba
		assertEquals("a".compareTo("ba"), comp("a", "ba"));
		
		// b == a
		assertEquals("b".compareTo("a"), comp("b", "a"));
		
		// b = ab
		assertEquals("b".compareTo("ab"), comp("b", "ab"));
		
		// b = ba
		assertEquals("b".compareTo("ba"), comp("b", "ba"));
		
		// b = abc
		assertEquals("b".compareTo("abc"), comp("b", "abc"));
		
		// b = bac
		assertEquals("b".compareTo("bac"), comp("b", "bac"));

	}

	
	
	private static int comp(String a, String b) {
		return new WordNode(a, null).compareTo(new WordNode(b, null));
	}
}
