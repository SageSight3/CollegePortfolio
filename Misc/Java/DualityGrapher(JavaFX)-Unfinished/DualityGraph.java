//Name: Sage
//Time invested: 3 ours 37 minutes
//References:

//TODO:
	//Create visual graph trace object in scene graph
	//get coordinates to graph in a line in functions other than y = 1
	//figure out to create a continuous graph
	//figure out how to graph negative x
	//figure out how to change the length of the index
	//figure out how to make it so the graph can be moved around
	//figure out how to have user input for the function
	//add duality graphing

import javafx.stage.*;
import javafx.scene.*;
import javafx.application.*;
import javafx.scene.shape.*;
import javafx.scene.paint.*;
import javafx.scene.text.*;
import javafx.scene.input.*;
import javafx.event.*;

public class DualityGraph extends Application {

	//index for graph trace
	int graphIndex = 0;

	public void start(Stage stage) {
		Group root = new Group();
		Scene scene = new Scene(root, 1000, 600);
		stage.setScene(scene);
		stage.setTitle("Duality Graph");

	//create graph
	XLine[] xGrid = new XLine[100]; //adds x grid

	for (int i = 0; i < 100; i++) {
		xGrid[i] = new XLine(i - 50, i * 10);
		root.getChildren().add(xGrid[i]);
	}

	YLine[] yGrid = new YLine[100]; //adds y grid

	for (int i = 0; i < 100; i++) {
		yGrid[i] = new YLine(i - 50, i * 10);
		root.getChildren().add(yGrid[i]);
	}

	Line xAxis = new Line(0, 300, 1000, 300); //adds x axis
	root.getChildren().add(xAxis);

	Line yAxis = new Line(500, 0, 500, 600); //adds y axis
	root.getChildren().add(yAxis);

	//Text for graph trace
	Text trace = new Text(50, 50, "(0.0, 0.0)");
	trace.setFont(Font.font("Calibri", 24));
	root.getChildren().add(trace);

	//controls text
	Text controls = new Text(50, 80, "Press left and right arrow keys\nto trace graph coordinates");
	controls.setFont(Font.font("Calibri", 24));
	root.getChildren().add(controls);

	//graph function, print coordinates to console also
	Graph[] function = new Graph[1000]; //array for graph coordinates

	for (int i = 0; i < 1000; i++) {
		function[i] = new Graph((double)i);
		root.getChildren().add(function[i]);
	}

	//event handlers for graph trace
	EventHandler<KeyEvent> keyEventHandler = new EventHandler<KeyEvent>() {
		public void handle(KeyEvent event) {

			if (event.getCode() == KeyCode.RIGHT) { //traces graph coordinates to the right
				graphIndex = graphIndex + 10;
				System.out.println("(" + function[graphIndex].getXCoord() + ", " + function[graphIndex].getYCoord() + ")");
				trace.setText("(" + function[graphIndex].getXCoord() + ", " + function[graphIndex].getYCoord() + ")");
			}

			if (event.getCode() == KeyCode.LEFT) { //traces graph coordinates to the left
				graphIndex = graphIndex - 10;
				System.out.println("(" + function[graphIndex].getXCoord() + ", " + function[graphIndex].getYCoord() + ")");
				trace.setText("(" + function[graphIndex].getXCoord() + ", " + function[graphIndex].getYCoord() + ")");
			}
		}
	};
	scene.setOnKeyPressed(keyEventHandler);

	stage.show();
	}
}