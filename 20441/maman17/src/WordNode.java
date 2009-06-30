/**
 * Node class for building lists of words.
 * 
 * @author Maxim Veksler 303856983
 *
 */
public class WordNode {
	/**
	 * A textual word represented by this WordNode.
	 */
	private String _word;

	/**
	 * The next object in the WordNode. 
	 */
	private WordNode _next;
	
	/**
	 * Counter for the number of current word appears in the list.
	 */
	private int _occurrences;
	// TODO: More properties will reside here based on requirements from TestList.
	
	
	// ###################
	// ## CONSTRUCTOR ####
	// ###################
	
	/**
	 * Constructor for WordNode which builds a node with link to the next node.
	 * 
	 * @param word String representing the word of this node.
	 * @param next WordNode representing the instance of WordNode that follows the current node in the list order.
	 * 
	 */
	public WordNode(String word, WordNode next) {
		this._word = word;
		this._next = next;
		_occurrences = 1;
	}

	
	// ###################
	// ## PUBLIC      ####
	// ###################
	
	/**
	 * Returns the word represented by this node object
	 * 
	 * @return String representing the word
	 */
	public String getWord() {
		return _word;
	}
	
	/**
	 * Retrieve the first character of the stored word.
	 * 
	 * @return char representing the first character of the word.
	 */
	public char getWordFirstChar() {
		return _word.charAt(0);
	}
	
	/**
	 * Returns the next node in the list from current node instance
	 * 
	 * @return WordNode reference to the following instance in the list
	 */
	public WordNode getNext() {
		return _next;
	}
	
	/**
	 * Returns the count of occurrences the word represented by this node appears in the list.
	 * @return
	 */
	public int getOccurrences() {
		return _occurrences;
	}
	
	/**
	 * Sort the linked list using merge sort algorithm
	 * @return
	 */
	public WordNode mergeSort() {
		
	}
	
	private WordNode merge(WordNode node) {
		 
		if(node == null) // If we are asked to merge a linked list that is null we are finished.
			return this; // Returning only this WordNode instance.
		
		// We have a _next node.
		char nextChar = _next.getWordFirstChar();
		char currentChar = getWordFirstChar();
		
		
	}
	
	/**
	 * Compare between 2 words to decide they proper ordering in the list.
	 * 
	 * @return negative if word1 < word2, 0 if they are equal, positive if word1 > word2
	 */
	public int compareTo(WordNode node) {
		// Store the shorter string among the 2 supplied parameters
		int shorterStringLength = (_word.length() > node.getWord().length()) ? node.getWord().length() : _word.length();

		// First compare each char, stopping only when reaching end either string or find a char that is not equal.
		int i = 0;
		while(!(i < shorterStringLength) && _word.charAt(i) == node.getWord().charAt(i)) 
			i++;
		
		if(i == shorterStringLength -1) { 
			// We have reached the end of one of the strings, meaning we now need to return a value.
			if(_word.length() > node.getWord().length())
				return 1;
			else if (_word.length() < node.getWord().length())
				return -1;
		}

		// Else either strings are equal in length or we stopped at some unequal character before reaching end of string.
		return _word.charAt(i) - node.getWord().charAt(i);
		
	}
}
