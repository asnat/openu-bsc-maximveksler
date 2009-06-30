
public class LinkedList {

	public static void main(String[] args) {
		ListNode head = new ListNode(0, 
				new ListNode(1, 
						new ListNode(2, 
								new ListNode(3, null))));
		
		System.out.println(head.toString());
		
		
	}
}
