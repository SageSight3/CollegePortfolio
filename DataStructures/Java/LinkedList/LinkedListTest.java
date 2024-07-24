package linkedlist;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

class LinkedListTest {
	private LinkedList aList;

	@BeforeEach
	void setUp() throws Exception {
		aList = new LinkedList();
	}


	@AfterEach
	void tearDown() throws Exception {
		aList = null;
	}

	@Test
	void testConstructor() {
		assertTrue(aList.isEmpty());
		assertTrue(aList.size() == 0);
		assertNull(aList.get(0));
	}
	
	@Test
	void testAddFirst() {
		aList.addFirst("mi");
		assertFalse(aList.isEmpty());
		assertTrue(aList.size() == 1);
		assertTrue(aList.get(0).equals("mi"));
		assertTrue(aList.getFirst().equals("mi"));
		assertTrue(aList.getLast().equals("mi"));
		aList.addFirst("re");
		assertFalse(aList.isEmpty());
		assertTrue(aList.size() == 2);
		assertTrue(aList.get(0).equals("re"));
		assertTrue(aList.get(1).equals("mi"));
		assertTrue(aList.getFirst().equals("re"));
		assertTrue(aList.getLast().equals("mi"));
		aList.addFirst("do");
		assertFalse(aList.isEmpty());
		assertTrue(aList.size() == 3);
		assertTrue(aList.get(0).equals("do"));
		assertTrue(aList.get(1).equals("re"));
		assertTrue(aList.get(2).equals("mi"));
		assertTrue(aList.getFirst().equals("do"));
		assertTrue(aList.getLast().equals("mi"));
	}
	
	@Test
	void testAddLast() {
		aList.addLast("do");
		assertFalse(aList.isEmpty());
		assertTrue(aList.size() == 1);
		assertTrue(aList.get(0).equals("do"));
		assertTrue(aList.getFirst().equals("do"));
		assertTrue(aList.getLast().equals("do"));
		aList.addLast("re");
		assertFalse(aList.isEmpty());
		assertTrue(aList.size() == 2);
		assertTrue(aList.get(0).equals("do"));
		assertTrue(aList.get(1).equals("re"));
		assertTrue(aList.getFirst().equals("do"));
		assertTrue(aList.getLast().equals("re"));
		aList.addLast("mi");
		assertFalse(aList.isEmpty());
		assertTrue(aList.size() == 3);
		assertTrue(aList.get(0).equals("do"));
		assertTrue(aList.get(1).equals("re"));
		assertTrue(aList.get(2).equals("mi"));
		assertTrue(aList.getFirst().equals("do"));
		assertTrue(aList.getLast().equals("mi"));
	}
	
	@Test
	void testRemoveFirst() {
		aList.addLast("do");
		aList.addLast("re");
		aList.addLast("mi");
		String returnString = aList.removeFirst();
		assertTrue(returnString.equals("do"));
		assertTrue(aList.getFirst().equals("re"));
		assertTrue(aList.getLast().equals("mi"));
		assertTrue(aList.size() == 2);
		assertFalse(aList.isEmpty());
		returnString = aList.removeFirst();
		assertTrue(returnString.equals("re"));
		assertTrue(aList.getFirst().equals("mi"));
		assertTrue(aList.getLast().equals("mi"));
		assertTrue(aList.size() == 1);
		assertFalse(aList.isEmpty());
		returnString = aList.removeFirst();
		assertTrue(returnString.equals("mi"));
		assertNull(aList.getFirst());
		assertNull(aList.getLast());
		assertTrue(aList.size() == 0);
		assertTrue(aList.isEmpty());
		assertNull(aList.removeFirst());	
	}
	
	@Test
	void testRemoveLast() {
		aList.addLast("do");
		aList.addLast("re");
		aList.addLast("mi");
		String returnString = aList.removeLast();
		assertTrue(returnString.equals("mi"));
		assertTrue(aList.getFirst().equals("do"));
		assertTrue(aList.getLast().equals("re"));
		assertTrue(aList.size() == 2);
		assertFalse(aList.isEmpty());
		returnString = aList.removeLast();
		assertTrue(returnString.equals("re"));
		assertTrue(aList.getFirst().equals("do"));
		assertTrue(aList.getLast().equals("do"));
		assertTrue(aList.size() == 1);
		assertFalse(aList.isEmpty());
		returnString = aList.removeLast();
		assertTrue(returnString.equals("do"));
		assertNull(aList.getFirst());
		assertNull(aList.getLast());
		assertTrue(aList.size() == 0);
		assertTrue(aList.isEmpty());
		assertNull(aList.removeLast());	
	}
		

}
