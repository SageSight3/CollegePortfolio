import javafx.scene.shape.*;
import javafx.scene.paint.*;
import javafx.scene.text.*;
import javafx.scene.*;

public class YLine extends Group{
	private int yCoord;

	//constructor for y axis lines
	public YLine(int yCoord, int y) {
		this.yCoord = yCoord;

		Line yLine = new Line(0,y, 1000, y);
		yLine.setStroke(Color.LIGHTGREY);
		this.getChildren().add(yLine);
	}
}