package boardgames;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

class GameSquareTest {

	private GameSquare darkSquare;
	private GameSquare lightSquare;
	private GamePiece piece;
	
	@BeforeEach
	void setUp() throws Exception {
		darkSquare = new GameSquare(Color.BLACK);
		lightSquare = new GameSquare(Color.WHITE);
		piece = new GamePiece();
	}

	@AfterEach
	void tearDown() throws Exception {
		darkSquare = null;
		lightSquare = null;
		piece = null;
	}

	@Test
	void testConstructor() {
		assertTrue(darkSquare.getColor() == Color.BLACK);
		assertTrue(lightSquare.getColor() == Color.WHITE);
		assertNull(darkSquare.getPiece());
		assertNull(lightSquare.getPiece());
		assertTrue(darkSquare.isEmpty());
		assertTrue(lightSquare.isEmpty());
	}
	
	@Test
	void testPiecePlacement() {
		darkSquare.placePiece(piece);
		assertTrue(darkSquare.getPiece() == piece);
		assertFalse(darkSquare.isEmpty());
		darkSquare.removePiece();
		assertNull(darkSquare.getPiece());
		assertTrue(darkSquare.isEmpty());
	}

}
