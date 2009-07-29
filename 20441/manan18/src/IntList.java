

public class IntList {
	private IntNode head;
	
	public IntList() {
		head = null;
	}
	
	public void addHead(int value) {
		head = new IntNode(value, head);
	}
	
	public String toString() {
		String str = "";
		for(IntNode tmp = head; tmp != null; tmp = tmp.getNext()) {
			str += tmp.getValue() + "\t";
		}
		return str;
	}
}
