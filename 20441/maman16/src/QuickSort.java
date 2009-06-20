import com.sun.org.apache.bcel.internal.generic.RET;


public class QuickSort {
	int[] a;
	
	public QuickSort(int[] a) {
		this.a = a;
	}

	private void sort(int low, int high) {
		int m;
		
		if(high > low +1) { // [low][ ]...[high] There are at least 3 elements to work with.
			/*
			 * We have something to sort, doing it recursively.
			 */
			
			// Decide on the middle.
			m = partition(low, high);
			
			// Sort the high half (It is guaranteed that all objects are bigger then middle).
			sort(m+1, high);
			
			// Sort the low half, (It is guaranteed that all objects are smaller then middle).
			sort(low, m-1);
		} else {
			// We have 2 values... basic condition. I hope we know how to handle this....
			if(high == low+1 && a[low] > a[high])
				swap(high, low);
			System.out.println("BASE");
		}
	}
	
	private int medianLocation(int low, int middle, int high) {
		if(a[low] <= a[middle]) {
			if(a[middle] <= a[high])
				return middle;
			else if(a[low] <= a[high])
				return high;
			else 
				return low;
		} else { // a[middle] > a[low]
			if(a[low] <= a[high]) 
				return low;
			else if(a[middle] <= a[high])
				return high;
			else
				return middle;
				
		}
	}
	
	private int partition(int low, int high) {
		swap(low, medianLocation(low+1, (low+high)/2, high));
		int m = partition(low+1, high, a[low]);
		swap(low, m);
		
		return m;
	}

	private int partition(int low, int high, int pivot) {
		if(high == low) 
			if(a[low] < pivot)
				return low;
			else 
				return low-1;
		else if(a[low] <= pivot)
			return partition(low+1, high, pivot);
		else { 
			swap(low, high);
			return partition(low, high-1, pivot);
		}
		
		//return m;
	}

	private void swap(int loc1, int loc2) {
		int t = a[loc1];
		a[loc1] = a[loc2];
		a[loc2] = t;
	}
	
	public void sort() { sort(0, a.length-1); };
	public void toStringStdout() {
		for(int i=0; i<a.length; i++) {
			System.out.print(a[i] + ", ");
		}
	}
	public static void main(String[] args) {
		QuickSort sort;
		
		// Worst case:
		sort = new QuickSort(new int[] {20, 3, 5, 7, 9, 11, 13, 15, 17, 19, 4, 10, 2, 12, 6, 14, 1, 16, 8, 18});
		sort.sort();
		sort.toStringStdout();
	}
}

