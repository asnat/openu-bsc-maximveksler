import static org.junit.Assert.*;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.Scanner;

import org.junit.Before;
import org.junit.Test;


public class WordNodeTest {
	static Random random = new Random();

	static List<String> wordList = new ArrayList<String>();
	
	@Before
	public void load() {
		FileReader fin;
		try {
			fin = new FileReader("wordlist.txt");
			Scanner src = new Scanner(fin);
			
			while(src.hasNext()){
				wordList.add(src.next());
			}
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
		
	}
	
	
	@Test
	public void testWordNode() {
	}

	@Test
	public void testFindMostContinuessFirstCharOccourencess() {

	}

//	@Test
//	public void testGetWord() {
//		fail("Not yet implemented");
//	}
//
//	@Test
//	public void testGetWordFirstChar() {
//		fail("Not yet implemented");
//	}
//
//	@Test
//	public void testGetNext() {
//		fail("Not yet implemented");
//	}
//
//	@Test
//	public void testGetOccurrences() {
//		fail("Not yet implemented");
//	}
//
//	@Test
//	public void testMergeSort() {
//		fail("Not yet implemented");
//	}

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
		comp("b", "ba");
		
		// b = abc
		comp("b", "abc");
		
		// b = bac
		comp("b", "bac");

		for(int i = 0; i < 1000; i++) {
			;
			String val1 = wordList.get(random.nextInt(wordList.size()));
			String val2 = wordList.get(random.nextInt(wordList.size()));
			comp(val1, val2);
		}
	}

	
	
	private int comp(String a, String b) {
		Method AcompareTo = useReflectionToRetriveCompareToMethod();

		WordNode nodeA = new WordNode(a, null);
		
		int res = 0;
		try {
			res = (Integer) AcompareTo.invoke(nodeA, new WordNode(b, null));
		} catch (Exception e) {
			e.printStackTrace();
		}
//		int res = new WordNode(a, null).compareTo(new WordNode(b, null));
		
		if(a.compareTo(b) < 0) {
			if(! (res < 0)) {
				System.out.println("Failed for " + a + "compareTo( " + b + ") =" + res);
				fail();
			}
		} else if(a.compareTo(b) > 0) {
			if(! (res > 0)) {
				System.out.println("Failed for " + a + "compareTo( " + b + ") =" + res);
				fail();
			}
		} else if(a.compareTo(b) == 0)
			if(! (res == 0)) {
				System.out.println("Failed for " + a + "compareTo( " + b + ") =" + res);
				fail();
			}
		
		return res;
	}
	
	static String getRandomString(int howMuch) {
		StringBuilder stringBuilder = new StringBuilder();
		
		for(int i = 0; i < howMuch; i++) {
			stringBuilder.append(wordList.get(random.nextInt(wordList.size()))).append(" ");
		}
		
		return stringBuilder.toString();
	}
	
	static Method useReflectionToRetriveCompareToMethod() {
		Method requestedMethod;
		
		try {
			requestedMethod = WordNode.class.getDeclaredMethod("compareTo", WordNode.class);
			requestedMethod.setAccessible(true);
			return requestedMethod;
		} catch (SecurityException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IllegalArgumentException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (NoSuchMethodException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		return null;
	}

}
