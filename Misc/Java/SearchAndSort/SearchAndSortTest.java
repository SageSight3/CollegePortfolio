package searchandsort;

import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.util.List;
import java.util.ArrayList;
import java.util.LinkedList;

class SearchAndSortTest {

	double[] unsortedData = {100.2, 75.0, 13.13, -12.0, 3.14159, -42.0};
	double[] sortedData = {-42.0, -12.0, 3.14159, 13.13, 75.0, 100.2};
	double[] arrayData;
	List<Double> arrayListData;
	List<Double> linkedListData;
	
	@BeforeEach
	void setUp() throws Exception {
		arrayData = unsortedData.clone();
		arrayListData = new ArrayList<Double>();
		linkedListData = new LinkedList<Double>();
		for(double eachDouble : unsortedData) {
			arrayListData.add(eachDouble);
			linkedListData.add(eachDouble);
		}
	}

	@AfterEach
	void tearDown() throws Exception {
		arrayData = null;
		arrayListData = null;
		linkedListData = null;
	}

	@Test
	void testBubbleSortArray() {
		SearchAndSort.bubbleSort(arrayData);
		for(int index = 0; index < sortedData.length; ++index) {
			assertTrue(arrayData[index] == sortedData[index]);
		}
	}
	
	@Test
	void testBubbleSortList() {
		SearchAndSort.bubbleSort(arrayListData);
		SearchAndSort.bubbleSort(linkedListData);
		for(int index = 0; index < sortedData.length; ++index) {
			assertTrue(arrayListData.get(index) == sortedData[index]);
			assertTrue(linkedListData.get(index) == sortedData[index]);
		}
	}
	
	@Test
	void testSelectionSortArray() {
		SearchAndSort.selectionSort(arrayData);
		for(int index = 0; index < sortedData.length; ++index) {
			assertTrue(arrayData[index] == sortedData[index]);
		}
	}
	
	@Test
	void testSelectionSortList() {
		SearchAndSort.selectionSort(arrayListData);
		SearchAndSort.selectionSort(linkedListData);
		for(int index = 0; index < sortedData.length; ++index) {
			assertTrue(arrayListData.get(index) == sortedData[index]);
			assertTrue(linkedListData.get(index) == sortedData[index]);
		}
	}
	
	@Test
	void testBinarySearchArray() {
		int answer = SearchAndSort.binarySearch(sortedData, -42.0);
		assertTrue(answer == 0);
		answer = SearchAndSort.binarySearch(sortedData, 13.13);
		assertTrue(answer == 3);
		answer = SearchAndSort.binarySearch(sortedData, 100.2);
		assertTrue(answer == 5);
		answer = SearchAndSort.binarySearch(sortedData, -50.0);
		assertTrue(answer == -1);
		answer = SearchAndSort.binarySearch(sortedData, 10.0);
		assertTrue(answer == -1);
		answer = SearchAndSort.binarySearch(sortedData, 1000.8);
		assertTrue(answer == -1);
	}

	@Test
	void testBinarySearchList() {
		SearchAndSort.bubbleSort(linkedListData);
		int answer = SearchAndSort.binarySearch(linkedListData, -42.0);
		assertTrue(answer == 0);
		answer = SearchAndSort.binarySearch(linkedListData, 13.13);
		assertTrue(answer == 3);
		answer = SearchAndSort.binarySearch(linkedListData, 100.2);
		assertTrue(answer == 5);
		answer = SearchAndSort.binarySearch(linkedListData, -50.0);
		assertTrue(answer == -1);
		answer = SearchAndSort.binarySearch(linkedListData, 10.0);
		assertTrue(answer == -1);
		answer = SearchAndSort.binarySearch(linkedListData, 1000.8);
		assertTrue(answer == -1);	
	}
}
