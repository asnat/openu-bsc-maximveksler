
public class shekef_17 {
	public static void insertionSortIter(int[] a) {
		int temp;
		
		for(int i = 1; i < a.length; i++) {
			if(a[i] > a[i-1]) {
				temp = a[i];
				int j = i;
				
				do {
					a[j] = a[j-1];
					j--;
				} while (j > 0 && a[j-1] < temp);
				
				a[j] = temp;
			}
		}
	}
	
	public static void insertionSortRecu(int[] a, int currLoc) {
		if (currLoc < a.length) {
			insertRecu(a, currLoc, a[currLoc]);
			insertionSortRecu(a, currLoc+1);
		}
	}
	
	public static int insertRecu(int a[], int loc, int value) {
		int temp = a[loc];
		
		if(loc < 1 || a[loc-1] > value) {
			a[loc] = value;
		} else {
			a[loc] = insertRecu(a, loc-1, value);
		}

		return temp;
	}
	
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		int[] a = {1, 3, 9, 4, 10, 60, 12, 3};

		//insertionSortIter(a);
		insertionSortRecu(a, 1);
		
		for(int i=0; i < a.length; i++) {
			System.out.print(a[i] + ", ");
		}

		
	}

}
