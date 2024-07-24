package searchandsort;

import java.util.List;

public class SearchAndSort {
	
	public static void bubbleSort(double[] data) {
		for(int pass = 0; pass < data.length - 1; ++pass) {
			for(int index = 0; index < data.length - 1; ++index) {
				if(data[index] > data[index+1]) {
					double temp = data[index];
					data[index] = data[index+1];
					data[index+1] = temp;
				}
			}
		}
	}
	
	public static void bubbleSort(List<Double> data) {
		for(int pass = 0; pass < data.size() - 1; ++pass) {
			for(int index = 0; index < data.size() - 1; ++index) {
				if(data.get(index) > data.get(index+1)) {
					double temp = data.get(index);
					data.set(index, data.get(index+1));
					data.set(index + 1, temp);
				}
			}
		}
	}
	
	public static void selectionSort(double[] data) {
		for(int indexOfFirstUnsorted = 0; indexOfFirstUnsorted < data.length - 1; ++indexOfFirstUnsorted) {
			int indexOfSmallest = indexOfFirstUnsorted;
			for(int nextIndex = 1; nextIndex < data.length - indexOfFirstUnsorted; ++nextIndex) {
				if(data[indexOfSmallest] > data[indexOfFirstUnsorted + nextIndex]) {
					indexOfSmallest = indexOfFirstUnsorted + nextIndex;
				}
			}
			double temp = data[indexOfFirstUnsorted];
			data[indexOfFirstUnsorted] = data[indexOfSmallest];
			data[indexOfSmallest] = temp;
		}
	}
	
	public static void selectionSort(List<Double> data) {
		for(int indexOfFirstUnsorted = 0; indexOfFirstUnsorted < data.size() - 1; ++indexOfFirstUnsorted) {
			int indexOfSmallest = indexOfFirstUnsorted;
			for(int nextIndex = 1; nextIndex < data.size() - indexOfFirstUnsorted; ++nextIndex) {
				if(data.get(indexOfSmallest) > data.get(indexOfFirstUnsorted + nextIndex)) {
					indexOfSmallest = indexOfFirstUnsorted + nextIndex;
				}
			}
			double temp = data.get(indexOfFirstUnsorted);
			data.set(indexOfFirstUnsorted, data.get(indexOfSmallest));
			data.set(indexOfSmallest, temp);
		}
		
	}
	
	public static int binarySearch(double[] data, double value) {
		int high = data.length-1;
		int low = 0;
		int mid = high/2;
		while(mid != low) {
			if(value > data[mid]) {
				low = mid;
			} else {
				high = mid;
			}
			mid = (low + high)/2;
		}
		if(data[low] == value) {
			return low;
		}
		if(data[high] == value) {
			return high;
		}
		return -1;
	}
	
	public static int binarySearch(List<Double> data, double value) {
		int high = data.size()-1;
		int low = 0;
		int mid = high/2;
		while(mid != low) {
			if(value > data.get(mid)) {
				low = mid;
			} else {
				high = mid;
			}
			mid = (low + high)/2;
		}
		if(data.get(low) == value) {
			return low;
		}
		if(data.get(high) == value) {
			return high;
		}
		return -1;
	}

}
