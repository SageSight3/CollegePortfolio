package solvers;

import static org.junit.jupiter.api.Assertions.*;

import java.util.List;

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import boardgames.Color;
import boardgames.GameBoard;
import boardgames.GameCoordinate;
import boardgames.Knight;

class KnightsTourSolverTest {

	private GameBoard board;
	private KnightsTourSolver solver;
	private GameCoordinate startCoord = new GameCoordinate(0,0);
	private GameCoordinate jumpCoord = new GameCoordinate(2,1);
	private Knight aKnight = new Knight();
	private GameMove startMove = new GameMove(startCoord, aKnight);
	private GameMove jumpMove = new GameMove(startCoord, jumpCoord, aKnight);
	
	@BeforeEach
	void setUp() throws Exception {
		board = new GameBoard(6, Color.BLACK, Color.WHITE);
		solver = new KnightsTourSolver(board, startMove);
	}

	@AfterEach
	void tearDown() throws Exception {
		board = null;
		solver = null;
	}

	@Test
	void testConstructor() {
		assertFalse(board.isEmpty(startCoord));
		assertTrue(solver.getMoves().size() == 1);
	}
	
	@Test
	void testDoMove() {
		solver.doMove(jumpMove);
		assertTrue(board.isEmpty(startCoord));
		assertFalse(board.isEmpty(jumpCoord));
		assertTrue(solver.getMoves().size() == 2);
	}
	
	@Test
	void testUndoMove() {
		solver.doMove(jumpMove);
		solver.undoMove(jumpMove);
		assertTrue(board.isEmpty(jumpCoord));
		assertFalse(board.isEmpty(startCoord));
		assertTrue(solver.getMoves().size() == 1);
		solver.undoMove(startMove);
		assertTrue(board.isEmpty(startCoord));
		assertTrue(solver.getMoves().isEmpty());
	}

	@Test
	void testIsSolved() {
		for(int i = 0; i < 35; ++i) {
			assertFalse(solver.isSolved());
			solver.getMoves().add(jumpMove);
		}
		assertTrue(solver.isSolved());
	}
	
	@Test
	void testIsOnBoard() {
		GameCoordinate offLeft = new GameCoordinate(-1, 2);
		GameCoordinate offRight = new GameCoordinate(6, 2);
		GameCoordinate offBottom = new GameCoordinate(2, -1);
		GameCoordinate offTop = new GameCoordinate(2, 6);
		assertFalse(solver.isOnBoard(offLeft));
		assertFalse(solver.isOnBoard(offRight));
		assertFalse(solver.isOnBoard(offBottom));
		assertFalse(solver.isOnBoard(offTop));
		assertTrue(solver.isOnBoard(startCoord));
		assertTrue(solver.isOnBoard(jumpCoord));
	}
	
	@Test
	void testHasVisited() {
		solver.doMove(jumpMove);
		assertTrue(solver.hasVisited(startCoord));
		assertTrue(solver.hasVisited(jumpCoord));
		assertFalse(solver.hasVisited(new GameCoordinate(2,2)));
	}
	
	@Test
	void testNextLegalMoves() {
		solver.doMove(jumpMove);
		List<GameMove> nextMoves = solver.nextLegalMoves();
		assertTrue(nextMoves.size() == 5);
	}
	
	@Test
	void testSolve() {
		assertTrue(solver.solve());
	}
}
