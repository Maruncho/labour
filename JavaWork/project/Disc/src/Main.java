//import java.util.Arrays;
import java.util.Comparator;

public class Main {

	static class SortByNameDescending implements Comparator<Disc> {
		public int compare(Disc d1, Disc d2) {
			return d2.name().compareTo(d1.name());
		}
	}
	
	static class SortBySizeAscending implements Comparator<Disc> {
		public int compare(Disc d1, Disc d2) {
			return d1.size()-d2.size();
		}
	}
	
	static <T> void bubbleSort(T[] arr, Comparator<T> comparator) {  
        int n = arr.length;  
        T temp;  
        for(int i=0; i < n; i++){  
        	for(int j=1; j < (n-i); j++){  
        		if(comparator.compare(arr[j-1], arr[j])>0){  
        			//swap elements  
                    temp = arr[j-1];  
                    arr[j-1] = arr[j];  
                    arr[j] = temp;  
        		}          
            }  
        }  
    }
	
	public static void main(String[] args) {
		try {
			Disc[] discs = {
				new Disc("Toy Story", 3072),
				new Disc("DooM", 512),
				new Disc("Obscura", 4096),
				new Disc("Misc", 2566)
			};
			
			//Arrays.sort(discs, new SortByNameDescending());
			bubbleSort(discs, new SortByNameDescending());
			for(Disc d : discs)
				System.out.println(d.toString());
			
			System.out.println("--------------------------------");
			
			//Arrays.sort(discs, new SortBySizeAscending());
			bubbleSort(discs, new SortBySizeAscending());
			for(Disc d : discs)
				System.out.println(d.toString());	
		}
		catch(Exception e) {
			System.out.println(e.getMessage());
		}
	}

}
