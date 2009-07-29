/**
 * Stack implementation based on linked list
 * 
 * @author Maxim Veksler 303856983
 */
public class Stack {
	// Pointer to the head of the linked list that represents the stack.
	private IntNode _head;
	
	/**
	 * Empty constructor, creates empty linked list.
	 */
	public Stack() {
		_head = null;
	}
	
	/**
	 * adds new int to the head of the stack
	 * 
	 * @param x the parameter to be added to the head of the stack
	 */
	public void push(int x) {
		_head = new IntNode(x, _head); 
	}
	
	/**
	 * Retrieve the element that is at the head of the stack.
	 * 
	 * @return The element that is at the head of the stack, if the stack is empty this operation
	 * 			is undefined.
	 */
	public int pop() {
		if(!empty()) {
			int retValue = _head.getValue();
			// Update the reference to the next element in the list because this one is being poped.
			_head = _head.getNext();
			return retValue;
		} else {
			// Undefined operation, by specifications...
			
			// throw new RuntimeException()...
			return Integer.MIN_VALUE;
		}
	}
	
	/**
	 * Peek at the element that is at the top of the stack without removing it from the stack.
	 * 
	 * @return The element that is at the top of the stack, if the stack is empty this operation
	 * 			is undefined.
	 */
	public int top() {
		if(!empty()) {
			return _head.getValue();
		} else {
			// Undefined operation, by specifications...
	
			// throw new RuntimeException()...
			return Integer.MIN_VALUE;
		}
	}
	
	/**
	 * Check if the stack is empty
	 * @return true if the stack is empty, false if not.
	 */
	public boolean empty() {
		return _head == null;
	}

}
