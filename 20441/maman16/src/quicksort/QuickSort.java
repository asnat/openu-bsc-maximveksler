package quicksort;

public class QuickSort {
	public static void quicksort(double[] a) {
		quicksort(a, 0, a.length-1);
	}
	
	private static void quicksort(double[] a, int lo, int hi) {
		int m; // m is calculated middle (pivot)
		
		if(hi > lo+1) { // There are at least 3 elements, so sort recursively.
			m = partition(a, lo, hi);
			quicksort(a, lo, m-1);
			quicksort(a, m+1, hi);
		} else {
			// base case...
			// 0, 1, or 2 elements so sort directly.
			if(hi == lo+1 && a[lo] > a[hi])
				swap(a, lo, hi);
		}
	}
	
	private static int partition(double[] a, int lo, int hi) {
		/*
		 * choose middle element among a[lo]...a[hi],
		 * and move other elements so that a[lo]...a[m-1]
		 * are all less than a[m] and a[m+1]...a[hi]
		 * all greater than a[m]
		 * 
		 * m is returned to the caller
		 */
		
		// Swap value of median from lo+1, hi, middle in lo.
		swap(a, lo, medianLocation(a, lo+1, hi, (lo+hi)/2));
		int m = partition(a, lo+1, hi, a[lo]);
		swap(a, lo, m);
		return m;
	}
	
	private static int medianLocation(double[] a, int i, int j, int k) {
		if(a[i] <= a[j])
			if(a[j] <= a[k])
				return j;
			else if(a[i] <= a[k])
				return k;
			else
				return i;
		else // a[j] < a[i]
			if(a[i] <= a[k])
				return i;
			else if (a[j] <= a[k])
				return k;
			else
				return j;
	}
	
	private static int partition(double[] a, int lo, int hi, double pivot) {
		if(hi == lo)
			if(a[lo] < pivot)
				return lo;
			else
				return lo-1;
		else if(a[lo] <= pivot) // a[lo] in correct half
			return partition(a, lo+1, hi, pivot);
		else {
			swap(a, lo, hi);
			return partition(a, lo, hi-1, pivot);
		}
	}
	
	private static void swap(double[] a, int i, int j) {
		double t = a[i];
		a[i] = a[j];
		a[j] = t;
	}
	
	
	// ##############
	// ### DEBUG
	// ##############
	public static void display(double[] a) {
		for(int i = 0; i < a.length; i++) {
			System.out.print(a[i] + ", ");
		}
		System.out.println();
	}

}
