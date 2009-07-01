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

	/**
	 * Copy constructor with new next node.
	 * 
	 * @param node copied node
	 * @param next WordNode representing the instance of WordNode that follows the current node in the list order.
	 * 
	 */
	public WordNode(WordNode node, WordNode next) {
		this._word = node._word;
		this._occurrences = node._occurrences;
		
		this._next = next;
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
	
	private WordNode[] split() {
		if(_next == null)
			return new WordNode[] {this, null};
		else {
			WordNode[] nextSplit = _next.split();
			return new WordNode[] {nextSplit[1], nextSplit[0]};
		}
	}
	
	private WordNode merge(WordNode node) {
		if(node == null) // If we are asked to merge a linked list that is null we are finished.
			return this; // Returning only this WordNode instance.
		
		int compareResult = compareTo(node);
		
		if (compareResult == 0) {
			// Note that if both nodes are equal we "lose" one node (delete it) and increment the counter of the second node.
			_occurrences++;
			return merge(node.getNext());
		} else if (compareResult < 0) {
			if (_next == null) {
				// Current node word is smaller then node._word (should come before him).
				// We have no tail so we simply add our self's before this node.
				return new WordNode(this, node);
			} else {
				// We do have tail, so we need to merge the list into our tail
				return new WordNode(this, _next.merge(node));
			}
		} else { // (compareResult > 0)
			// We found a node that is bigger then us, so we return that node as current and call recursive merge to decide what it's
			// tail will be with our value of the tail of the small node.
			return new WordNode(node, merge(node.getNext()));
		}
	}
	
	/**
	 * Compare between 2 words to decide their proper ordering in the list.
	 * 
	 * @return negative if word1 < word2, 0 if they are equal, positive if word1 > word2
	 */
	public int compareTo(WordNode node) {
		// Store the shorter string among the 2 supplied parameters
		int shorterStringLength = (_word.length() > node.getWord().length()) ? node.getWord().length() : _word.length();

		// Compare each char
		// 	Forced Stop condition: Reaching end of shortest string 
		// 	Goal stop condition: Find a char that is not equal.
		int i = 0;
		while(true) {
			if(!(i < shorterStringLength)) {
				// We have reached the end of one of the strings, meaning we now need to return a value.
				if(_word.length() > node.getWord().length())
					return 1;
				else if (_word.length() < node.getWord().length())
					return -1;
				else
					return 0;
			}
			
			if( _word.charAt(i) != node.getWord().charAt(i))
				return _word.charAt(i) - node.getWord().charAt(i);

			// If no failure condition has occured progress to next character.
			i++;
		}
			
	}}
