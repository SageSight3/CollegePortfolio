package solvers;

import java.util.ArrayList;
import java.util.List;

import boardgames.GameBoard;
import boardgames.GameCoordinate;
import boardgames.GamePiece;
import boardgames.Knight;

public class KnightsTourSolver extends PuzzleSolver {
	private int[] fileOffsets = {1, 2, 2, 1, -1, -2, -2, -1};
	private int[] rankOffsets = {2, 1, -1, -2, -2, -1, 1, 2};
	
	public KnightsTourSolver(GameBoard aBoard, GameMove firstMove) {
		super(aBoard);
		doMove(firstMove);
	}
	
	@Override
	public boolean isSolved() {
		return moves.size() == board.getSize() * board.getSize();
	}
	
	@Override
	public List<GameMove> nextLegalMoves(){
		List<GameMove> nextMoves = new ArrayList<GameMove>();
		GameCoordinate currentCoord = moves.get(moves.size()-1).to();
		for(int jumpIndex = 0; jumpIndex < 8; ++jumpIndex) {
			GameCoordinate possibleCoord = currentCoord.offsetBy(
					fileOffsets[jumpIndex], 
					rankOffsets[jumpIndex]);
			if(isOnBoard(possibleCoord) && !hasVisited(possibleCoord)) {
				GameMove aMove = new GameMove(currentCoord, possibleCoord, getKnight());
				nextMoves.add(aMove);
			}
		}
		return nextMoves;
	}
	
	public boolean isOnBoard(GameCoordinate aCoord) {
		return aCoord.fileIndex >=0 && aCoord.fileIndex < board.getSize()
				&& aCoord.rankIndex >=0 && aCoord.rankIndex < board.getSize();
	}
	
	public boolean hasVisited(GameCoordinate aCoord) {
		for(GameMove eachMove : moves) {
			if(eachMove.to().fileIndex == aCoord.fileIndex
					&& eachMove.to().rankIndex == aCoord.rankIndex) {
				return true;
			}	
		}
		return false;
	}
	
	public GamePiece getKnight() {
		return moves.get(0).getPiece();
	}
}
