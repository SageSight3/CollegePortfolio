package solvers;

import java.io.StringWriter;

import boardgames.GameBoard;
import boardgames.GameCoordinate;
import boardgames.GamePiece;

public class GameMove {
	private GameCoordinate from;
	private GameCoordinate to;
	private GamePiece piece;
	
	public GameMove(GameCoordinate toCoord, GamePiece aPiece) {
		from = null;
		to = toCoord;
		piece = aPiece;
	}
	
	public GameMove(GameCoordinate fromCoord, GameCoordinate toCoord, GamePiece aPiece) {
		from = fromCoord;
		to = toCoord;
		piece = aPiece;
	}
	
	public GameCoordinate from() {
		return from;
	}
	
	public GameCoordinate to() {
		return to;
	}
	
	public GamePiece getPiece() {
		return piece;
	}
	
	public void doOn(GameBoard board) {
		if(from != null) {
			board.removePiece(from);
		}
		board.placePiece(to, piece);
	}
	
	public void undoOn(GameBoard board) {
		board.removePiece(to);
		if(from != null) {
			board.placePiece(from, piece);
		}
	}
	
	@Override
	public String toString() {
		StringWriter writer = new StringWriter();
		writer.write(piece.toString());
		writer.write(' ');
		if(from != null) {
			writer.write(from.toString());
			writer.write(" -> ");
		}
		writer.write(to.toString());
		return writer.toString();
		// String writers do not require a close()
	}
}
