package boardgames;

import java.io.StringWriter;

public class GameCoordinate {
	public int fileIndex;
	public int rankIndex;
	
	public GameCoordinate(int aFileIndex, int aRankIndex) {
		fileIndex = aFileIndex;
		rankIndex = aRankIndex;
	}
	
	public GameCoordinate(char file, int rank) {
		fileIndex = (int)file - (int)'a';
		rankIndex = rank - 1;
	}
	
	public int getFileIndex() {
		return fileIndex;
	}
	
	public int getRankIndex() {
		return rankIndex;
	}
	
	public char getFile() {
		return (char)(fileIndex + (int)'a');
	}
	
	public int getRank() {
		return rankIndex + 1;
	}
	
	public GameCoordinate offsetBy(int fileOffset, int rankOffset) {
		return new GameCoordinate(fileIndex + fileOffset, rankIndex + rankOffset);
	}
	
	@Override
	public String toString() {
		StringWriter writer = new StringWriter();
		writer.write(getFile());
		writer.write(Integer.toString(getRank()));
		return writer.toString();
		// NOTE: StringWriter does not require a close() message.
	}
}
