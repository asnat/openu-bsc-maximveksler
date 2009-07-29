import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;


public class StackSorterTest {
	Stack testedStack = new Stack();
	
	@Before
	public void setUp() throws Exception {
		testedStack.push(7);
		testedStack.push(7);
		testedStack.push(7);
		testedStack.push(7);
		testedStack.push(7);
		testedStack.push(7);
		testedStack.push(2);
		testedStack.push(2);
		testedStack.push(4);
	}

	@Test
	public void testSortStack() {
		StackSorter.sortStack(testedStack);
		
		while(! testedStack.empty())
			System.out.println(testedStack.pop());
	}

}
