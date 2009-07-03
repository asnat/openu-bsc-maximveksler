//////
///// GENERAL NOTICE, pay attention to situation where more then one possible has been found, 
////// both in code and in documentation.
//////
////// ALSO NOTE THE YOU NEED TO WRITE TIME AND SPACE Complexity of each method !
/////
/**
 * List class acting as a wrapper to linked node composing a ordered word list.
 * 
 * @author Maxim Veksler 303856983
 *
 */
public class TextList {
	/**
	 * Reference to the start of the linked list.
	 */
	private WordNode _head;
	
	/**
	 * Constructor, creating empty TextList. 
	 * 
	 * We have no operations, so we are not dependent on the input size -> O(1)
	 */
	public TextList() {
		_head = null;
	}
	
	/**
	 * Constructor, creating a preinitialized TextList based on supplied text.
	 * 
	 * The time complexity of the method is n+n+nlogn -> O(nlogn)
	 * The space complexity of the method is n+n -> O(n).
	 * 
	 * @param text String representing text to be used for constructing the TextList, the text format should be a-z* words separated by ' '
	 */
	public TextList(String text) {
		/*
		 * If we find some words in the text we:
		 * 	1. Create an unsorted list of the words (which costs us n for the split, n for the create)
		 *  2. Run merge sort on the list which costs us nlog(n)
		 *  
		 *  This is a better solution then sorting the list as we go by adding each node at the correct location because the ordered addition
		 *  is done using linear search which has at the words case performance of n. In other words: In the worst case we would have to do
		 *  1+2+3+4+5+..n operations before the list would be sorted. O(n^2)
		 */
		if(text != null) {
			String[] words = text.split(" ");
			for(int i = 0; i < words.length; i++) {
				_head = new WordNode(words[i], _head);
			}
			
			// Sort the list in ascending order O(nlogn)
			_head = WordNode.mergeSort(_head);
		}
	}
	
	/**
	 * Add additional word into the sorted list of words.
	 * 
	 * We scan the list seeking the proper insertion order, worst case we insert at the end = n -> O(n)
	 * The space complexity is fixed because the input is always same size. -> O(1)
	 * 
	 * @param word The word that will be added to the list.
	 */
	public void addToData(String word) {
		WordNode newList = null;
		if(_head == null) {
			newList = new WordNode(word, null);
		} else {
			newList = _head.insertNewNode(word);
		}
		
		// We need to replace the reference to _head because if added item is at the start of the list the whole list head is replaced.
		_head = newList;
	}
	
	/**
	 * Calculate the total number of words in the list.
	 *  
	 * @return int representing the number of words contained in the list. If list has no words 0 is returned.
	 */
	public int howManyWords() {
		/*
		 * To calculate the total number of words (with duplicated) we simply sum the occurrences of each node.
		 */
		int counter = 0;
		WordNode node = _head;
		
		while(node != null) {
			counter += node.getOccurrences();
			node = node.getNext();
		}
		
		return counter;
	}

	/**
	 * Calculate the number of different words in the list.
	 * 
	 * @return int representing the count of unique words in the list. If list has no words 0 is returned. 
	 */
	public int howManyDifferentWords() {
		/*
		 * To calculate the unique number of words we simply sum the number of nodes, as each node represents a different word.
		 */
		int counter = 0;
		WordNode node = _head;
		
		while(node != null) {
			counter ++;
			node = node.getNext();
		}
		
		return counter;
	}
	
	/**
	 * Find and return the most frequent word in the list 
	 * 
	 * @return String representing the most frequent word contained in this list. If list has not words a null value will be returned.
	 */
	public String mostFrequentWord() {
		/*
		 * To find the most frequent word we run on the whole list, searching the word that has most occurncess.
		 */
		if(_head != null) {
			// We start assuming the first word is the most frequent.
			WordNode frequentNode = _head;
			
			// Start scanning from second node...
			WordNode node = _head.getNext();
			
			while(node != null) {
				if(frequentNode.getOccurrences() < node.getOccurrences())
					frequentNode = node; 
			}
			
			return frequentNode.getWord();
		} else {
			// We have no words.
			return null;
		}
	}
	
	/**
	 * Find and return the character that most words start with.
	 * 
	 * @return char representing the most popular starting character among list words. If list has no words, char=0 will be returned.
	 */
	public char mostFrequentStartingLetter() {
		if(_head == null)
			return 0;
		else 
			return (char) _head.findMostContinuessFirstCharOccourencess();
	}
	
	/**
	 * Calculate how many words start with given char and return it.
	 * 
	 * @param letter char representing the requested first char of the words.
	 * 
	 * @return int representing how many words have been found that start with the given char.
	 * 				If no words have been found a value of 0 will be returned.
	 */
	public int howManyStarting(char letter) {
		
	}
	
	/**
	 * Converts the list of words into a single string given in the format:
	 * <<WORD>>\t<<NumberOfOccurencessOfThisWord>>\n
	 * 
	 * @return String representing the list of words in one string by the format described above.
	 */
	public String toString() {
		if(_head != null)
			return _head.toString();
		else 
			return null;
	}
}
