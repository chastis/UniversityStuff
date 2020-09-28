package base_package;

import javafx.scene.control.Button;
import javafx.scene.layout.HBox;
import javafx.scene.layout.StackPane;
import javafx.scene.layout.VBox;
import javafx.application.Application;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.util.ArrayList;
import java.util.Random;

public class Program extends Application {
    public static void main(String[] args) {
        launch(args);
    }

    private static final int HEIGHT = 300;
    private static final int WIDTH = 400;
    public static final int GRID_HEIGHT = 10;
    public static final int GRID_WIDTH  = 20;
    public static final int COUNT_OF_THREADS  = 2;

    public static volatile ArrayList<ArrayList<Button>> field;
    public static int winni_x;
    public static int winni_y;

    @Override
    public void start(Stage stage) {
        Random random = new Random();
        winni_x = Math.abs(random.nextInt()) % GRID_WIDTH;
        winni_y = Math.abs(random.nextInt()) % GRID_HEIGHT;
        field = new ArrayList<>();

        HBox hBox = new HBox();
        for (int i = 0; i < GRID_WIDTH; i++) {
            field.add(new ArrayList<>());
            VBox vBox = new VBox();
            for (int j = 0; j < GRID_HEIGHT; j++) {
                Button  b = new Button("");
                if (i == winni_x && j == winni_y)
                    b.setStyle("-fx-background-color: #ff1a1c");
                else
                    b.setStyle("-fx-background-color: #31ff2b");
                b.setMinWidth(10);
                b.setMinHeight(10);
                field.get(i).add(b);
                vBox.getChildren().add(b);
            }
            hBox.getChildren().add(vBox);
        }

        StackPane pane = new StackPane();
        pane.getChildren().add(hBox);
        Scene scene = new Scene(pane, WIDTH, HEIGHT);
        stage.setScene(scene);
        stage.show();

        startConcurrency();
    }

    private void startConcurrency() {
        int s = 3;
        for (int i = 0; i < COUNT_OF_THREADS; i++) {
            BeeTeam t = new BeeTeam(s*i, s*(i+1));
            t.start();
        }
    }

}
