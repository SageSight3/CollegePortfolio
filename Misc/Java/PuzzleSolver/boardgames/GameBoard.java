package boardgames;

public class GameBoard {
	private GameSquare[][] squares;
	
	public GameBoard(int size, Color darkColor, Color lightColor) {
		squares = new GameSquare[size][size];
		for(int rankIndex = 0; rankIndex < size; ++rankIndex) {
			for(int fileIndex = 0; fileIndex < size; ++fileIndex) {
				Color color = darkColor;
				squares[fileIndex][rankIndex] = new GameSquare(color);
			}
		}
	}
	
	public int getSize() {
		return squares.length;
	}
	
	public GameSquare getSquare(GameCoordinate coord) {
		return squares[coord.fileIndex][coord.rankIndex];
	}
	
	public boolean isEmpty(GameCoordinate coord) {
		return getSquare(coord).isEmpty();
	}
	
	public void placePiece(GameCoordinate coord, GamePiece piece) {
		getSquare(coord).placePiece(piece);
	}
	
	public void removePiece(GameCoordinate coord) {
		getSquare(coord).removePiece();
	}
}
