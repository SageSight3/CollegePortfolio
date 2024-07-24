package boardgames;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

class GameBoardTest {

	private GameBoard chessBoard;
	private final GamePiece aPiece = new GamePiece();
	private final GamePiece bPiece = new GamePiece();
	private final GameCoordinate a1 = new GameCoordinate('a', 1);
	private final GameCoordinate c2 = new GameCoordinate('c', 2);
	
	@BeforeEach
	void setUp() throws Exception {
		chessBoard = new GameBoard(8,Color.BLACK, Color.WHITE) ;
	}

	@AfterEach
	void tearDown() throws Exception {
		chessBoard = null;
	}

	@Test
	void testConstructor() {
		assertTrue(chessBoard.getSquare(a1).getColor() == Color.BLACK);
		assertTrue(chessBoard.getSquare(c2).getColor() == Color.WHITE);
		assertTrue(chessBoard.getSize() == 8);
		for(int rankIndex = 0; rankIndex < chessBoard.getSize(); ++rankIndex) {
			for(int fileIndex = 0; fileIndex < chessBoard.getSize(); ++ fileIndex) {
				GameCoordinate aCoord = new GameCoordinate(
												fileIndex, 
												rankIndex);
				assertTrue(chessBoard.isEmpty(aCoord));
			}
		}
	}

	@Test
	void testPiecePlacement() {
		GameCoordinate b1 = new GameCoordinate('b', 1);
		chessBoard.placePiece(a1, aPiece);
		chessBoard.placePiece(c2, bPiece);
		assertFalse(chessBoard.isEmpty(a1));
		assertTrue(chessBoard.isEmpty(b1));
		assertFalse(chessBoard.isEmpty(c2));
		assertTrue(chessBoard.getPiece(a1) == aPiece);
		assertTrue(chessBoard.getPiece(c2) == bPiece);
		chessBoard.removePiece(a1);
		chessBoard.removePiece(c2);
		assertTrue(chessBoard.isEmpty(a1));
		assertTrue(chessBoard.isEmpty(c2));
	}

}
