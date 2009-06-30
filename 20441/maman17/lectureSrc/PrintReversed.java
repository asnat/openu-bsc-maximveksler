import java.util.Scanner;


public class PrintReversed {

	public static ListNode readReversedList() {
		ListNode head = null;
		
		Scanner scanner = new Scanner(System.in);
		int readValue = scanner.nextInt();
		while(readValue != 0) {
			head = new ListNode(readValue, head);
			readValue = scanner.nextInt();
		}
		
		return head;
	}
	
	public static void printReverseList(ListNode head) {
		while(head != null) {
			System.out.print(head._value + ", ");
			head = head._tail;
		}
		
		System.out.println();
	}
	
	public static void main(String[] args) {
//		ListNode head = readReversedList();
////		printReverseList(head);
//
//		System.out.println("List length: " + head.length());
//		head.addToEndM(800);
//		System.out.println("List length: " + head.length());
//		System.out.println(head.toString());
//
//		ListNode head2 = head.addInorderM(3);
//		System.out.println(head2);
//		
		Scanner scanner = new Scanner(System.in);
		ListNode head = new ListNode(0, null);

		int v;
		do {		
			System.out.print("Enter value: ");
			v = scanner.nextInt();
			head = head.addInorderM(v);
			
			System.out.println("List looks like: " + head.toString());

		} while(v != 0);
	}

}
