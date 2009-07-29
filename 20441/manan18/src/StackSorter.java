/**
 * Stack Sorter is a utility class to manipulate on the content of stack elements
 * 
 * @author Maxim Veksler 303856983
 */
public class StackSorter {
	/**
	 * Sorts the content of the supplied stack from lower to highest when the lowest element is at the head of the stack
	 * 
	 * @param s The Stack element upon which the sorting will be taking place.
	 */
	public static void sortStack(Stack s) {
		// If the supplied stack is null we have nothing to sort, so we return. 
		if(s == null)
			return;
		
		/*
		 * The sorting algorithm is given as following by the following pseudo code
		 * 
		 * Stack sorted = new Stack();
		 * While (s has elements)
		 * 		copy all elements of s to a tmp stack
		 * 		copy all elements from tmp stack to s omitting the smallest item
		 * 		push smallest item into sorted
		 * 
		 * push all elements from sorted to s
		 * 
		 * The space complexity of this algorithm is O(n)
		 * The time complexity of this sorting algorithm is O(n^2)  
		 */
		
		
		Stack sorted = new Stack();
		while(! s.empty()) {
			// While s is not empty we remove from it the smallest value and push it into the sorted stack.
			sorted.push(removeSmallest(s));
		}
		
		// Now, because sorted is ordered from bigger to smallest we simply reverse this
		// by pushing everything into the original stack.
		while(! sorted.empty()) {
			s.push(sorted.pop());
		}
	}
	
	private static int removeSmallest(Stack origin) {
		Stack tmp = new Stack();
		int min = Integer.MAX_VALUE;
		
		while(! origin.empty()) {
			int val = origin.pop();
			if(min > val)
				min = val;
			tmp.push(val);
		}
		
		boolean isSkipAllowed = true;
		while(! tmp.empty()) {
			int val = tmp.pop();
			if(isSkipAllowed && val == min)
				isSkipAllowed = false;
			else
				origin.push(val);

		}
		
		return min;
	}
}
