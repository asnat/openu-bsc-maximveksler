

public class IntNode {
	private int value;
	private IntNode _next;
	
	public IntNode(int value, IntNode next) {
		this.value = value;
		this._next = next;
	}

	public int getValue() {
		return value;
	}

	public void setValue(int value) {
		this.value = value;
	}

	public IntNode getNext() {
		return _next;
	}

	public void setNext(IntNode next) {
		this._next = next;
	}
	
	
}
