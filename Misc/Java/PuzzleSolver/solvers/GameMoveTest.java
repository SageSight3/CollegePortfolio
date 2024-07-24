package solvers;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import boardgames.Color;
import boardgames.GameBoard;
import boardgames.GameCoordinate;
import boardgames.GamePiece;

class GameMoveTest {

	private GameCoordinate origin = new GameCoordinate(0, 0);
	private GameCoordinate jump = new GameCoordinate(1, 2);
	private GamePiece piece = new GamePiece();
	private GameBoard board;
	private GameMove placeMove = new GameMove(origin, piece);
	private GameMove jumpMove = new GameMove(origin, jump, piece);

	@BeforeEach
	void setUp() throws Exception {
		board = new GameBoard(8, Color.BLACK, Color.WHITE);
	}

	@AfterEach
	void tearDown() throws Exception {
		board = null;
	}

	@Test
	void testConstructor() {
		assertTrue(jumpMove.from().equals(origin));
		assertTrue(jumpMove.to().equals(jump));
		assertTrue(jumpMove.getPiece() == piece);
		assertNull(placeMove.from());
		assertTrue(placeMove.to().equals(origin));
		assertTrue(placeMove.getPiece() == piece);
	}
	
	@Test
	void testDoMove() {
		placeMove.doOn(board);
		assertFalse(board.isEmpty(origin));
		jumpMove.doOn(board);
		assertTrue(board.isEmpty(origin));
		assertFalse(board.isEmpty(jump));
	}

	@Test
	void testUndoMove() {
		placeMove.doOn(board);
		jumpMove.doOn(board);
		jumpMove.undoOn(board);
		assertTrue(board.isEmpty(jump));
		assertFalse(board.isEmpty(origin));
		placeMove.undoOn(board);
		assertTrue(board.isEmpty(origin));
	}
	
	@Test
	void testToString() {
		assertTrue( "Kn a1".equals(placeMove.toString()));
		assertTrue( "Kn a1 -> b3");
	}
}
