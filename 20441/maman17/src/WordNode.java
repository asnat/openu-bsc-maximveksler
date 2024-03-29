/**
 * Node class for building lists of words.
 * 
 * @author Maxim Veksler 303856983
 * @author Open University (MegeSort)
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
	
	public String toString() {
		String thisToString = _word + "\t" + _occurrences + "\n";
		
		if(_next == null)
			return thisToString;
		else 
			return thisToString + _next.toString();
	}
	
	/**
	 * Returns the word represented by this node object
	 * 
	 * @return String representing the word
	 */
	public String getWord() {
		return _word;
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
	 * Add new word (optionally) create new WordNode in the list.
	 * 
	 * @param newWord
	 * @return
	 */
	public WordNode insertNewNode(String newWord) {
		/*
		 * We add / increase the counter using linear search.
		 * We seek forward starting from the first node, aiming to find the proper location to insert the new node.
		 */
		
		int compareResult = compareTo(newWord); // Compare newWord with current node _word value.
		
		if(compareResult == 0) {
			// Same word, just increase repeating counter.
			_occurrences++;
			return this;
		} else if (compareResult < 0) {
			// newWord is bigger then current word, need to add it after current node.
			if(_next == null) {
				// We are the biggest word in the known universe.
				_next = new WordNode(newWord, null);
				return this;
			} else {
				_next = _next.insertNewNode(newWord); 
				return this;
			}
		} else { // newWord is smaller then current word, need to add before current node.
			return new WordNode(newWord, this);
		}
	}
	
	/**
	 * Find the char that the biggest number of words in the list starts with.
	 *  
	 * @return char The character that is the most popular as first word among all words in the list.
	 */
	public char findMostContinuessFirstCharOccourencess() {
		if(_next != null) {
			return _next.findMostContinuessFirstCharOccourencess(getOccurrences(), getWordFirstChar(), getOccurrences(), getWordFirstChar());
		} else
			return getWordFirstChar();
	}
	
	/**
	 * Search the list and sum the number of words that start with a specified character
	 * 
	 * @param c The character for which we court the number of occurrences.
	 * @param node Node representing the current relative root search node in the list.
	 * @return int the number words found starting at given char, if no words we're found a 0 value is returned.
	 */
	public int countContinuessCharOccourencess(char c) {
		if(getWordFirstChar() > c)
			// Recursion stop condition, we either reached the end of the list (_next = null) or we've came across
			// 	a node that has first character bigger then our searched - So we stop.
			return 0;
		
		if(getWordFirstChar() < c)
			// If we're at a character that is smaller then our search target we simply continue with next node.
			if(_next != null)
				return _next.countContinuessCharOccourencess(c);
			else 
				return 0;
		else 
			// Current node character is the same as our searched character.
			if(_next != null)
				return getOccurrences() + _next.countContinuessCharOccourencess(c);
			else
				return getOccurrences();
	}
	
	
	// ###################
	// ## PRIVATE     ####
	// ###################

	/**
	 * Retrieve the first character of the stored word.
	 * 
	 * @return char representing the first character of the word.
	 */
	private char getWordFirstChar() {
		return _word.charAt(0);
	}
	
	private char findMostContinuessFirstCharOccourencess(int mostOccur, char mostOccurChar, int currentOccur, char currentOccurChar) {
		/*
		 * Recursive Search algorithm:  Search assumption: When we reach the final node we know the most frequent char and the number of it's 
		 * 	occurrences. We achieve this by assuming in each node that it is the last in the list, then being totally shocks we find out
		 *  we are not the last node in the universe, thus passing what we know to the next node.
		 *  
		 * The search is correct because the list is sorted, thus ensuring that the next word will either start with the same letter as this
		 * 	word or that this current letter will never appear again.
		 * 	
		 * General Note: As method variables are primitives on the stack it OK the we modify them.
		 */
		if(currentOccurChar == getWordFirstChar()) {
			currentOccur += getOccurrences();
		} else {
			currentOccurChar = getWordFirstChar();
			currentOccur = getOccurrences();
		}
		
		if(currentOccur > mostOccur) {
			mostOccur = currentOccur;
			mostOccurChar = currentOccurChar;
		}
		
		if(_next != null) 
			return _next.findMostContinuessFirstCharOccourencess(mostOccur, mostOccurChar, currentOccur, currentOccurChar);
		else
			return mostOccurChar;
	}
	
	/**
	 * See documentation of compareTo(String nodeWord)
	 * 
	 * @return negative if this._word < node._word, 0 if they are equal, positive if this._word > node._word
	 */
	private int compareTo(WordNode node) {
		return compareTo(node.getWord());
	}

	/**
	 * Compare between node word and supplied word to decide their proper ordering in the list.
	 * 
	 * @return negative if this._word < nodeWord, 0 if they are equal, positive if this._word > nodeWord
	 */
	private int compareTo(String nodeWord) {
		// Store the shorter string length among the 2 supplied parameters
		int shorterStringLength;
		if(_word.length() > nodeWord.length()) 
			shorterStringLength = nodeWord.length(); 
		else
			shorterStringLength = _word.length();

		
		// Compare each char
		// 	Forced Stop condition: Reaching end of shortest string 
		// 	Goal stop condition: Find a char that is not equal.
		int i = 0;
		while(true) {
			if(!(i < shorterStringLength)) {
				// We have reached the end of one of the strings, meaning we now need to return a value.
				if(_word.length() > nodeWord.length())
					return 1;
				else if (_word.length() < nodeWord.length())
					return -1;
				else
					return 0;
			}
			
			if( _word.charAt(i) != nodeWord.charAt(i))
				return _word.charAt(i) - nodeWord.charAt(i);

			// If no failure condition has occurred progress to next character.
			i++;
		}
	}

	// ######################
	// ##   MERGESORT    ####
	// ######################
	/**
	 * A MergeSort implementation for WordNode based lists.
	 * 
	 * Complexity O(nlogn)
	 * 
	 * @return WordNode a new sort list of WordNode elements. 
	 */
	public static WordNode mergeSort(WordNode wordNode) {
		if(wordNode == null || wordNode._next == null) {
			// Node has less then 2 values, return the node itself.
			return wordNode;
		} else {
			// Split the list into 2 parts.
			WordNode[] listNodePair = wordNode.split();
			
			// Now merge the 2 splits, in ascending order.
			return mergeSort(listNodePair[0]).merge(mergeSort(listNodePair[1]));
		}
		
	}
	
	/**
	 * Part of the MergeSort implementation, used to split and array into 2 equal parts.
	 * @return WordNode[] array containing exactly 2 elements representing the list split into 2 parts.
	 */
	private WordNode[] split() {
		if(_next == null)
			return new WordNode[] {this, null};
		else {
			WordNode[] nextSplit = _next.split();
			return new WordNode[] {new WordNode(this, nextSplit[1]), nextSplit[0]};
		}
	}
	
	/**
	 * Part of the MergeSort implementation, used to merge 2 sorted arrays in ascending order.
	 * 
	 * @param node WordNode representing the request list to be merged into current node list.
	 * @return WordNode representing the newly created merged list from both lists.
	 */
	private WordNode merge(WordNode node) {
		if(node == null) // If we are asked to merge a linked list that is null we are finished.
			return this; // Returning only this WordNode instance.
		
		int compareResult = compareTo(node);
		
		if (compareResult == 0) {
			// Note that if both nodes are equal we "lose" second node (delete it) and increment the counter of the first node instead.
			// 	We don't just increment by one because in 2nd level merges (not just 2 nodes) there is a possibility that
			//	node has already been repeated more then once, thereof we add to current node occurrences the count
			//	of the twin node occurrences.
			_occurrences += node.getOccurrences();
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
	
}
