package linkedlist;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

class LinkTest {
	private Link linkOne;
	private Link linkTwo;

	@BeforeEach
	void setUp() throws Exception {
		linkOne = new Link("do");
		linkTwo = new Link("re");
	}

	@AfterEach
	void tearDown() throws Exception {
		linkOne = null;
		linkTwo = null;
	}

	@Test
	void testConstructor() {
		assertTrue(linkOne.getItem().equals("do"));
		assertNull(linkOne.getNext());
		assertNull(linkOne.getPrev());
	}

	@Test
	void testlinkOperations() {
		linkOne.setNext(linkTwo);
		assertTrue(linkOne.getNext() == linkTwo);
		linkTwo.setPrev(linkOne);
		assertTrue(linkTwo.getPrev() == linkOne);
	}

}
