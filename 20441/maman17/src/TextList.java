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
	 */
	public TextList() {
	}
	
	/**
	 * Constructor, creating a preinitialized TextList based on supplied text.
	 * 
	 * The complexity of the method is n+nlogn.
	 * @param text String representing text to be used for constructing the TextList, the text format should be a-z* words separated by ' '
	 */
	public TextList(String text) {
		/*
		 * If we find some words in the text we:
		 * 	1. Create an unsorted list of the words (which costs us n)
		 *  2. Run merge sort on the list which costs us nlog(n)
		 *  
		 *  This is a better solution then sorting the list as we go by adding each node at the correct location because the ordered addition
		 *  is is done using linear search which has at the words case performance of n. In other words: In the worst case we would have to do
		 *  1+2+3+4+5+..n operations before the list would be sorted. O(n^2)
		 */
		if(text != null) {
			String[] words = text.split(" ");
			for(int i = 0; i < words.length; i++) {
				_head = new WordNode(words[i], _head);
			}
		}
		
		// create the list of nodes, the run merge sort on them.
	}
	
	/**
	 * Add additional word into the sorted list of words.
	 * 
	 * @param word The word that will be added to the list.
	 */
	public void addToData(String word) {
		// complexity of n
	}
	
	/**
	 * Calculate the total number of words in the list.
	 *  
	 * @return int representing the number of words contained in the list.
	 */
	public int howManyWords() {
		
	}

	/**
	 * Calculate the number of different words in the list.
	 * 
	 * @return int representing the count of unique words in the list. 
	 */
	public int howManyDifferentWords() {
		
	}
	
	/**
	 * Find and return the most frequent word in the list 
	 * 
	 * @return String representing the most frequent word contained in this list.
	 */
	public String mostFrequentWord() {
		
	}
	
	/**
	 * Find and return the character that most words start with.
	 * 
	 * @return char representing the most popular starting character among list words.
	 */
	public char mostFrequentStartingLetter() {
		// Needs to be implemented with recursion. 
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
		
	}
}
