package base_package;

import javafx.application.Application;
import javafx.geometry.Orientation;
import javafx.scene.Scene;
import javafx.scene.control.Slider;
import javafx.scene.input.KeyCode;
import javafx.scene.layout.BorderPane;
import javafx.stage.Stage;

public class Program extends Application {
    public static void main(String[] args) {
        launch(args);
    }

    static final Slider slider = new Slider();

    @Override
    public void start(Stage stage) throws Exception {
        BorderPane main_pane = new BorderPane();

        slider.setValue(0);
        slider.setOrientation(Orientation.VERTICAL);
        main_pane.setCenter(slider);
        slider.setMaxHeight(300);
        slider.setStyle("-fx-control-inner-background: yellow;");
        Scene scene = new Scene(main_pane, 100, 400);
        scene.setOnKeyPressed(e -> {
            if (e.getCode() == KeyCode.A) {
                Action action = new Action();
                action.Go();
            }
        });

        stage.setScene(scene);
        stage.show();
    }
}
