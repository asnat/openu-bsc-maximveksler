
/**
 * BinaryTree handling utility class methods.
 *
 * @author Maxim Veksler 303856983
 */
public class BinaryTree {
	/**
	 * Sum the values of all nodes in the tree which their values are bigger then
	 * 	supplied parameter.
	 * 
	 * The summing is done using recursive calls, on the right & left subtrees 
	 * 	adding to it the value of current node if it is bigger the supplied n
	 * 
	 * @param node root of binary tree upon we will be calculating our sum
	 * @param n the sum of nodes that their value is bigger then this number will be returned.
	 * 
	 * @return Sum of all nodes in the tree that their value is bigger then given parameter
	 */
	public static int sumOfBiggerThan(Node node, int n) {
		if(node == null)
			return 0;
		
		// At first we assume that the benefit from this node is 0.
		int addedSumFromThisNode = 0;
		if(node.getNumber() > n)
			// Then if we find it to be a profitable node, we simply assign 
			// addedSumFromThisNode his cost, addedSumFromThisNode is used in the final 
			// calculation to return the cost of this node.
			addedSumFromThisNode = node.getNumber();
		
		// Recursive calculation call.
		return sumOfBiggerThan(node.getRightSon(), n) 
				+ sumOfBiggerThan(node.getLeftSon(), n) 
				+ addedSumFromThisNode;
	}

	
	////////////////////////////////////////////
	////////////////////////////////////////////
	///				DEBUG CODE				////
	/// PLEASE IGNORE THE REST OF THE CLASS ////
	////////////////////////////////////////////
	////////////////////////////////////////////

//	Node root;
//	
//	public BinaryTree() {
//		root = new Node(8);
//			root.setLeftSon(new Node(4));
//				root.getLeftSon().setRightSon(new Node(7));
//					root.getLeftSon().getRightSon().setLeftSon(new Node(6));
//						root.getLeftSon().getRightSon().getLeftSon();
//							root.getLeftSon().getRightSon().getLeftSon().setLeftSon(new Node(1));
//				root.getLeftSon().setLeftSon(new Node(5));
//					root.getLeftSon().getLeftSon().setRightSon(new Node(8));
//
//			root.setRightSon(new Node(2));
//				root.getRightSon().setRightSon(new Node(6));
//					root.getRightSon().getRightSon().setLeftSon(new Node(9));
//				root.getRightSon().setLeftSon(new Node(3));
//					root.getRightSon().getLeftSon().setRightSon(new Node(1));
//						root.getRightSon().getLeftSon().getRightSon().setRightSon(new Node(2));
//					root.getRightSon().getLeftSon().setLeftSon(new Node(7));
//						root.getRightSon().getLeftSon().setLeftSon(new Node(7));
//							root.getRightSon().getLeftSon().getLeftSon().setLeftSon(new Node(0));
//
//	}
//	public void binarySortedAdd(int number) {
//		if(root == null)
//			root = new Node(number);
//		else {
//			binarySortedAdd(root, number);
//		}
//	}
//	
//	private void binarySortedAdd(Node addTarget, int number) {
//		if(addTarget.getNumber() > number)
//			// Our number is smaller, need to add to the left.
//			binarySortedAdd(addTarget.getLeftSon(), number);
//		else
//			// Our number is bigger, need to add to the right.
//			binarySortedAdd(addTarget.getRightSon(), number);
//	}
//	
//	public IntList what(int i) {
//		IntList level = new IntList();
//		if(root != null)
//			what(level, i, root);
//		return level;
//	}
//	
//	private void what(IntList level, int i, Node t) {
//		if(t != null) {
//			if(i>0) {
//				what(level, i-1, t.getRightSon());
//				what(level, i-1, t.getLeftSon());
//			} else {
//				level.addHead(t.getNumber());
//			}
//		}
//	}
//	
//	public Node getRoot() {
//		return root;
//	}
}
