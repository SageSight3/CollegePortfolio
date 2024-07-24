import javafx.scene.shape.*;
import javafx.scene.paint.*;
import javafx.scene.text.*;
import javafx.scene.*;

public class Graph extends Group{
	private double xCoord;
	private double y;
	private double yCoord;

	public Graph(double x) { //graphs and stores coordinates
		//scales x coordinate for return value
		xCoord = x / 10;

		//y = function of x, scales x to graph
		y = x / 10; //function y = x
		y = y * -10;

		//scales y coordinate for return value
		yCoord = y / -10;

		//graph coordiantes
		Line coords = new Line(x + 500, y + 300, x + 500, y + 300);
		coords.setStroke(Color.BLUE);
		this.getChildren().add(coords);
	}

	public double getXCoord() {
		return xCoord;
	}

	public double getYCoord() {
		return yCoord;
	}

}