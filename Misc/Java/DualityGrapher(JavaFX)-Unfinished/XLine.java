import javafx.scene.shape.*;
import javafx.scene.paint.*;
import javafx.scene.text.*;
import javafx.scene.*;

public class XLine extends Group{
	private int xCoord;

	//constructor for x axis lines
	public XLine(int xCoord, int x) {
		this.xCoord = xCoord;

		Line xLine = new Line(x, 0, x, 600);
		xLine.setStroke(Color.LIGHTGREY);
		this.getChildren().add(xLine);
	}
}