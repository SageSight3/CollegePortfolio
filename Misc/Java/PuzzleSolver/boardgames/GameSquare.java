package boardgames;

public class GameSquare {
	private Color color;
	private GamePiece piece;
	
	public GameSquare(Color aColor) {
		color = aColor;
	}
	
	public boolean isEmpty() {
		return piece == null;
	}
	
	public Color getColor() {
		return color;
	}
	
	public GamePiece getPiece() {
		return piece;
	}
	
	public void placePiece(GamePiece aPiece) {
		piece = aPiece;
	}
	
	public void removePiece() {
		piece = null;
	}
}
