package solvers;

import java.util.ArrayList;
import java.util.List;

import boardgames.GameBoard;
import boardgames.GameCoordinate;
import boardgames.Queen;

public class NQueensSolver extends PuzzleSolver {

	private Queen queen;

	public NQueensSolver(GameBoard aBoard) {
		super(aBoard);
	}

	@Override
	public boolean isSolved() {
		return moves.size() == board.getSize();
	}

	@Override
	public List<GameMove> nextLegalMoves() {
		List<GameMove> nextMoves = new ArrayList<GameMove>();
		GameCoordinate nextCoord;
		for (int fileIndex = 0; fileIndex < board.getSize(); ++fileIndex) {
			nextCoord = new GameCoordinate(fileIndex, currentRankIndex());
			if (isSafe(nextCoord) && board.isEmpty(nextCoord)) {
				GameMove aMove = new GameMove(nextCoord, queen);
				nextMoves.add(aMove);
			}
		}
		return nextMoves;
	}

	public int currentRankIndex() {
		return moves.size();
	}

	public boolean isThreatenedBy(GameCoordinate coord, GameCoordinate QCoord) {
		return (coord.rankIndex == QCoord.rankIndex || coord.fileIndex == QCoord.fileIndex
				|| Math.abs(coord.rankIndex - QCoord.rankIndex) == Math.abs(coord.fileIndex - QCoord.fileIndex));

	}

	public boolean isSafe(GameCoordinate coord) {
		for (GameMove eachMove : moves) {
			if (isThreatenedBy(eachMove.to(), coord)) {
				return false;
			}
		}
		return true;
	}
}
