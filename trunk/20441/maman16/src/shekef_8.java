
public class shekef_8 {
	public static void selectionSortRec(int[] a, int i) {
		
		if(i >= a.length-1)
			// We exit when reaching last object. 
			return;
		
		int largestLoc = getLargetLocation(a, i);
		
		if(largestLoc != i) {
			int temp = a[largestLoc];
			a[largestLoc] = a[i];
			a[i] = temp;
		}
		
		selectionSortRec(a, i+1);
	}
	
	public static int getLargetLocation(int[] a, int from) {
		if(from >= a.length-1)
			return from;
		
		int subLargestLoc = getLargetLocation(a, from+1);
		
		if(a[subLargestLoc] < a[from])
			return from;
		else 
			return subLargestLoc;
	}
	
	public static void selectionSortIter(int[] a) {
		for(int i = 0; i < a.length-1; i++) {

			// Select largest value from the remaining sub array.
			int largestLoc = i;
			for(int j = i+1; j < a.length; j++) {
				if(a[largestLoc] < a[j])
					largestLoc = j;
			}
			
			if(largestLoc != i) {
				int temp = a[largestLoc];
				a[largestLoc] = a[i];
				a[i] = temp;
			}
		}
	}
	
	public static void main(String[] args) {
		int[] a = {1, 3, 9, 4, 10, 60, 12, 3};
		
		System.out.println(getLargetLocation(a, 0));
		selectionSortIter(a);
		
		for(int i=0; i < a.length; i++) {
			System.out.print(a[i] + ", ");
		}
	}
}
