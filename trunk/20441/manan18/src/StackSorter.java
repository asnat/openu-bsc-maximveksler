/**
 * Stack Sorter is a utility class to manipulate on the content of stack elements
 * 
 * @author Maxim Veksler 303856983
 */
public class StackSorter {
	/**
	 * Sorts the content of the supplied stack from lower to highest 
	 * 	when the lowest element is at the head of the stack
	 * 
	 * This is an unstable sort.
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

	/**
	 * Find and remove from supplied origin the smallest node value, 
	 * 	the value is returned as plain int.
	 *  
	 * This operation is undefined if origin is null or does not contain values.
	 * 
	 * @param origin Stack that contains values upon which the search will be executed.
	 * @return int the smallest value that has been found and removed from the stack.
	 */
	private static int removeSmallest(Stack origin) {
		// tmp stack is used during the seeking phase.
		Stack tmp = new Stack();
		
		// We start with the ultimate minimum in java
		int min = Integer.MAX_VALUE;
		
		/*
		 * Our removal algorithm is simple (and not very efficient, due to the nature of 
		 * 	linked list based data structure implementations) :
		 * 
		 * We iterate over all values of origin, copying all values to a tmp stack and 
		 * 	finding the smallest value.
		 * 
		 * Then we iterate again, this time over tmp copying all values into origin but this
		 * 	time we make sure not to copy the smallest value that was found in the previous
		 * 	iteration. 
		 * 
		 * The result of this 2 phase seek & destroy is: The smallest that was 
		 * 	stored in origin is removed from the stack.
		 */

		// We want to continue copying as long as origin has values...
		while(! origin.empty()) {
			int val = origin.pop();
			// Here we seek the smallest node, so update the value of min if it's current 
			// 	value is bigger then val.
			if(min > val)
				min = val;
			
			// After the test is completed, store all checked values into a tmp stack.
			tmp.push(val);
		}
		
		// Marker flag, to suggest if a skip operation has happened for this run.
		// 	We need this flag because we do not want to eliminate min values in a single scan.
		boolean isSkipAllowed = true;

		// We want to continue copying as long as tmp has values...
		while(! tmp.empty()) {
			int val = tmp.pop();
			
			// The actual removal, is we haven't skipped a value yet and current value
			// of node matches our minimum then by all means skip it!
			//
			// In other words, Survival of the fittest... 
			if(isSkipAllowed && val == min)
				isSkipAllowed = false;
			else
				origin.push(val);

		}
		
		// Finally, we returned the minimum we found.
		return min;
	}
}
