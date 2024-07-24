package solvers;

import java.util.ArrayList;
import java.util.List;

import boardgames.GameBoard;

public abstract class PuzzleSolver {

	protected GameBoard board;
	protected List<GameMove> moves;

	public abstract boolean isSolved();
	public abstract List<GameMove> nextLegalMoves();
	
	public PuzzleSolver(GameBoard aBoard) {
		board = aBoard;
		moves = new ArrayList<GameMove>();
	}
	
	public List<GameMove> getMoves() {
		return moves;
	}

	public void doMove(GameMove aMove) {
		aMove.doOn(board);
		moves.add(aMove);
	}

	public void undoMove(GameMove aMove) {
		moves.remove(moves.size()-1);
		aMove.undoOn(board);
	}

	public boolean solve() {
		if(isSolved()) {
			return true;
		}
		List<GameMove> nextMoves = nextLegalMoves();
		for(GameMove eachMove : nextMoves) {
			doMove(eachMove);
			if(solve()) { return true; }
			undoMove(eachMove);
		}
		return false;
	}

}
