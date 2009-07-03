import static org.junit.Assert.*;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.lang.reflect.Field;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.Scanner;

import org.junit.Before;
import org.junit.Test;


public class TextListTest {
	static Random random = new Random();
	static List<String> wordList = new ArrayList<String>();
	WordNode node = null;

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
	public void testTextList() {
		fail("Not yet implemented");
	}

	@Test
	public void testTextListString() {
		
		new TextList(null);
		new TextList("A");
		new TextList("A B");
		new TextList("A B C");
		
		TextList list = new TextList(getRandomString(1000));

		node = useReflectionToRetriveList(list);
		
		assertTrue(getNumberOfTotalNodes(node) == 1000);
			
		String current = node.getWord();
		while (node.getNext() != null) {
			// All current node must be smaller then next node.
			assertTrue(current.compareTo(node.getNext().getWord()) < 0);
			node = node.getNext();
		}

		list = new TextList("A B A C A D");

//		System.out.println(list);
	}

	@Test
	public void testAddToData() {
		TextList list = null;
		
		// Test incrementing A counter to 2
		list = new TextList("B A");
		list.addToData("A");
		node = useReflectionToRetriveList(list);
		assertTrue(node.getWord().equals("A"));
		assertTrue(node.getOccurrences() == 2);
		assertTrue(node.getNext().getWord().equals("B"));
		assertTrue(node.getNext().getOccurrences() == 1);
		assertTrue(node.getNext().getNext() == null);

	
		// Test incrementing A counter to 3
		list = new TextList("A A");
		list.addToData("A");
		node = useReflectionToRetriveList(list);
		assertTrue(node.getWord().equals("A"));
		assertTrue(node.getOccurrences() == 3);
		assertTrue(node.getNext() == null);

		// Test adding before all
		list = new TextList("B D");
		list.addToData("A");
		node = useReflectionToRetriveList(list);
		assertTrue(node.getWord().equals("A"));
		assertTrue(node.getOccurrences() == 1);
		assertTrue(node.getNext().getWord().equals("B"));
		assertTrue(node.getNext().getOccurrences() == 1);
		assertTrue(node.getNext().getNext().getWord().equals("D"));
		assertTrue(node.getNext().getNext().getOccurrences() == 1);
		assertTrue(node.getNext().getNext().getNext() == null);

		// Test adding to end of list
		list = new TextList("E C");
		list.addToData("ZERO");
		node = useReflectionToRetriveList(list);
		assertTrue(node.getWord().equals("C"));
		assertTrue(node.getOccurrences() == 1);
		assertTrue(node.getNext().getWord().equals("E"));
		assertTrue(node.getNext().getOccurrences() == 1);
		assertTrue(node.getNext().getNext().getWord().equals("ZERO"));
		assertTrue(node.getNext().getNext().getOccurrences() == 1);
		assertTrue(node.getNext().getNext().getNext() == null);

		
		// Test adding to middle of list
		list = new TextList("T D U T");
		list.addToData("F");
		node = useReflectionToRetriveList(list);
		assertTrue(node.getWord().equals("D"));
		assertTrue(node.getOccurrences() == 1);
		
		assertTrue(node.getNext().getWord().equals("F"));
		assertTrue(node.getNext().getOccurrences() == 1);
		
		assertTrue(node.getNext().getNext().getWord().equals("T"));
		assertTrue(node.getNext().getNext().getOccurrences() == 2);
		
		assertTrue(node.getNext().getNext().getNext().getWord().equals("U"));
		assertTrue(node.getNext().getNext().getNext().getOccurrences() == 1);
		
		assertTrue(node.getNext().getNext().getNext().getNext() == null);

		// Test Random Adding
		list = new TextList();
		for(int i = 0; i < 1001; i++) {
			list.addToData(wordList.get(random.nextInt(wordList.size())));
		}

		node = useReflectionToRetriveList(list);
		assertTrue(getNumberOfTotalNodes(node) == 1001);

		String current = node.getWord();
		while (node.getNext() != null) {
			assertTrue(current.compareTo(node.getNext().getWord()) < 0);
			node = node.getNext();
		}

	}

	@Test
	public void testHowManyWords() {
		fail("Not yet implemented");
	}

	@Test
	public void testHowManyDifferentWords() {
		fail("Not yet implemented");
	}

	@Test
	public void testMostFrequentWord() {
		fail("Not yet implemented");
	}

	@Test
	public void testMostFrequentStartingLetter() {
		TextList list = null;
		
		list = new TextList();
		assertTrue(list.mostFrequentStartingLetter() == 0);
		
		list = new TextList("acc addd aaaa bmmm beee cooo ciii clll ckkk dad");
		assertTrue(list.mostFrequentStartingLetter() == 'c');

		list = new TextList("aaaa aaaa aaaa aaaa aaaa cooo ciii clll ckkk dad");
		assertTrue(list.mostFrequentStartingLetter() == 'a');

		for(int iii = 0; iii < 1000; iii++) {
			// Test Random Adding
			int thisCounter = random.nextInt(997);
			
			list = new TextList();
			for(int i = 0; i < thisCounter; i++) {
				list.addToData(wordList.get(random.nextInt(wordList.size())));
			}
			
			node = useReflectionToRetriveList(list);
			
//			System.out.println("=============================================\n" + node.toString());
			
			assertTrue(getNumberOfTotalNodes(node) == thisCounter);
			
			char freq = 0;
			int freqOccur = 0;
			
			char curr = 0;
			int currOccur = 0;
	
			while (node != null) {
				if(node.getWord().charAt(0) == curr) {
					currOccur += node.getOccurrences();
				} else {
					curr = node.getWord().charAt(0);
					currOccur = node.getOccurrences();
				}
				
				if(currOccur > freqOccur) {
					freqOccur = currOccur;
					freq = curr;
				}
				
				node = node.getNext();
			}
			
			assertTrue(list.mostFrequentStartingLetter() == freq);
		}
	}

	@Test
	public void testHowManyStarting() {
		fail("Not yet implemented");
	}

	@Test
	public void testToString() {
		TextList list = null;
		
		for(int iii = 0; iii < 10; iii++) {
			// Test Random Adding
			int thisCounter = 5;//random.nextInt(1500);
			
			list = new TextList(getRandomString(thisCounter));
			
			node = useReflectionToRetriveList(list);
			
//			System.out.println("=============================================\n" + node.toString());
			
			String toStringExpected = "";
			
			while (node != null) {
				toStringExpected += node.getWord() + "\t" + node.getOccurrences() + "\n";
				node = node.getNext();
			}
			
			assertEquals(toStringExpected, list.toString());
		}

	}
	
	static String getRandomString(int howMuch) {
		StringBuilder stringBuilder = new StringBuilder();
		
		stringBuilder.append(wordList.get(random.nextInt(wordList.size())));
		for(int i = 1; i < howMuch; i++) {
			stringBuilder.append(" ").append(wordList.get(random.nextInt(wordList.size())));
		}
		
		return stringBuilder.toString();
	}

	static WordNode useReflectionToRetriveList(TextList list) {
		Field privateStringField;
		try {
			privateStringField = TextList.class.getDeclaredField("_head");
			privateStringField.setAccessible(true);
			WordNode node = (WordNode) privateStringField.get(list);
			return node;
		} catch (SecurityException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (NoSuchFieldException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IllegalArgumentException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IllegalAccessException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		return null;
	}
	
	static int getNumberOfTotalNodes(WordNode node) {
		int counter = 0;
		
		while(node != null) {
			counter += node.getOccurrences();
			node = node.getNext();
		}
		
		return counter;
	}
}
