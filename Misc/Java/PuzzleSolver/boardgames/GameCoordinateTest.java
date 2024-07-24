package boardgames;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

class GameCoordinateTest {

	private GameCoordinate origin;
	private GameCoordinate c2;
	
	@BeforeEach
	void setUp() throws Exception {
		origin = new GameCoordinate(0,0);
		c2 = new GameCoordinate('c', 2);
	}

	@AfterEach
	void tearDown() throws Exception {
		origin = null;
		c2 = null;
	}

	@Test
	void testConstructor() {
		assertTrue(origin.fileIndex == 0);
		assertTrue(origin.rankIndex == 0);
		assertTrue(origin.getFileIndex() == 0);
		assertTrue(origin.getRankIndex() == 0);
		assertTrue(origin.getFile() == 'a');
		assertTrue(origin.getRank() == 1);
		assertTrue(c2.fileIndex == 2);
		assertTrue(c2.rankIndex == 1);
		assertTrue(c2.getFileIndex() == 2);
		assertTrue(c2.getRankIndex() == 1);
		assertTrue(c2.getFile() == 'c');
		assertTrue(c2.getRank() == 2);
	}

	@Test
	void testOffsetBy() {
		GameCoordinate newCoord = c2.offsetBy(3, 3);
		assertTrue(newCoord.fileIndex == 5);
		assertTrue(newCoord.rankIndex == 4);
	}
	
	@Test
	void testToString() {
		assertTrue(c2.toString().equals("c2"));
	}
}
