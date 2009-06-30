public class ListNode {
	int _value;
	ListNode _tail;
	
	public ListNode(int value, ListNode next) {
		this._value = value;
		this._tail = next;
	}
	
	public int getValue() {
		return _value;
	}
	
	public ListNode getTail() {
		return _tail;
	}
	public ListNode merge(ListNode head) {
		return null;
	}
	
	public String toString() {
		if(_tail != null)
			return _value + ", " + _tail.toString();
		else
			return String.valueOf(_value);
		
	}
	
	public int length() {
		if(_tail != null) {
			return 1 + _tail.length();
		} else 
			return 1;
	}
	
	public ListNode nth(int n) {
		if(n == 0)
			return this;
		else {
			if(_tail == null)
				return null;
			else
				return _tail.nth(n-1);
		}
	}
	
	public void addToEndM(int n) {
		if(_tail != null) 
			_tail.addToEndM(n);
		else {
			// We've reached the last cell, _tail is null for him.
			
			// We want to create a new Node at the end of the list
			_tail = new ListNode(n, null);
		}
	}
	
	
	public ListNode addInorderM(int n) {
		ListNode l = this;
		
		if(n < _value) { // Current value is bigger then n, so we add n before it and return to caller.
			l = new ListNode(n, this);
		} else if(n > _value) {
			if(_tail == null) {
				_tail = new ListNode(n, null);
			} else {
				_tail = _tail.addInorderM(n);
			}
		}
			
		return l;	
	}
}
