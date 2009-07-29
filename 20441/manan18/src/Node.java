

public class Node {
	private int number;
	private Node leftSon, rightSon;

	public Node(int number) {
		this.number = number;
	}
	
	public int getNumber() {
		return number;
	}

	public Node getLeftSon() {
		return leftSon;
	}

	public void setLeftSon(Node leftSon) {
		this.leftSon = leftSon;
	}

	public Node getRightSon() {
		return rightSon;
	}

	public void setRightSon(Node rightSon) {
		this.rightSon = rightSon;
	}

	public void setNumber(int number) {
		this.number = number;
	}
	
}
