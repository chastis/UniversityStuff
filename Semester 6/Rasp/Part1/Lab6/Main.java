package base_package;

import javafx.application.Application;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.Slider;
import javafx.scene.layout.*;
import javafx.stage.Stage;

public class Main extends Application {
    public static void main(String[] args) {
        launch(args);
    }

    private static final int WINDOW_HEIGHT = 750;
    private static final int WINDOW_WIDTH = 1000;
    public static final int MAX_THREAD_COUNT = Runtime.getRuntime().availableProcessors();
    public static final int MAX_DELAY = 1000;

    private volatile Field field;
    private Computator computator;

    private Slider used_thread_count_slider;
    private Button start_button;
    private Button stop_button;
    private Button reset_button;
    public static Label label_counter;

    @Override
    public void start(Stage primaryStage) {
        field = new Field(50);
        computator = new Computator(field);

        Scene scene = new Scene(MakeMainPane(), WINDOW_WIDTH, WINDOW_HEIGHT);
        primaryStage.setScene(scene);
        primaryStage.setResizable(false);
        primaryStage.show();
    }

    private Pane MakeMainPane() {
        BorderPane res = new BorderPane();
        res.setCenter(MakeCenterPane());
        res.setTop(MakeTopPane());
        res.setBottom(MakeBottomPane());
        res.setLeft(MakeLeftPane());
        return res;
    }
    private Pane MakeCenterPane() {
        GridPane pane = (GridPane) field.getPane();
        pane.setPadding(new Insets(5, 10, 5, 10));
        pane.setAlignment(Pos.CENTER);
        return pane;
    }
    private Pane MakeTopPane() {
        Pane pane = new StackPane();

        VBox box = new VBox();
        box.setAlignment(Pos.CENTER);

        Label title = new Label("! Game \"Life\" !");
        title.setStyle("-fx-font-size: 50px");
        box.getChildren().add(title);

        Label threads_label = new Label("Used threads: ");
        threads_label.setPadding(new Insets(5, 10, 5, 10));
        box.getChildren().add(threads_label);

        used_thread_count_slider = new Slider(1, MAX_THREAD_COUNT, 1);
        used_thread_count_slider.setMaxWidth(500);
        used_thread_count_slider.setShowTickLabels(true);
        used_thread_count_slider.setShowTickMarks(true);
        used_thread_count_slider.setBlockIncrement(1);
        box.getChildren().add(used_thread_count_slider);

        Label current_threads_count_label = new Label("Value = 1");
        box.getChildren().add(current_threads_count_label);
        used_thread_count_slider.valueProperty().addListener((obs, oldval, newVal) -> {
            used_thread_count_slider.setValue(newVal.intValue());
            current_threads_count_label.setText("Value = " + newVal.intValue());
            ChangedThreadCount(newVal.intValue());
        });

        pane.getChildren().add(box);
        return pane;
    }
    private Pane MakeBottomPane() {
        Pane pane = new StackPane();

        VBox box = new VBox();
        box.setAlignment(Pos.CENTER);

        Label delay_label = new Label("Delay: ");
        delay_label.setPadding(new Insets(5, 10, 5, 10));
        box.getChildren().add(delay_label);

        Slider delay_slider = new Slider(50, MAX_DELAY, MAX_DELAY);
        delay_slider.setMaxWidth(500);
        delay_slider.setBlockIncrement(300);
        box.getChildren().add(delay_slider);

        Label current_delay_label = new Label("Value = " + MAX_DELAY);
        box.getChildren().add(current_delay_label);
        delay_slider.valueProperty().addListener((obs, oldval, newVal) -> {
            delay_slider.setValue(newVal.intValue());
            current_delay_label.setText("Value = " + newVal.intValue());
            ChangeDelay(newVal.intValue());
        });

        pane.getChildren().add(box);
        return pane;
    }
    private Pane MakeLeftPane() {
        Pane pane = new StackPane();
        VBox box = new VBox();
        box.setAlignment(Pos.CENTER);

        start_button = new Button("Start");
        start_button.setMinSize(70, 30);
        start_button.setOnAction(e -> Start());
        box.getChildren().add(start_button);

        stop_button = new Button("Stop");
        stop_button.setDisable(true);
        stop_button.setMinSize(70, 30);
        stop_button.setOnAction(e -> Stop());
        box.getChildren().add(stop_button);

        reset_button = new Button("Reset");
        reset_button.setMinSize(70, 30);
        reset_button.setOnAction(e -> Reset());
        box.getChildren().add(reset_button);

        label_counter = new Label("0");
        box.getChildren().add(label_counter);

        pane.getChildren().add(box);
        return pane;
    }

    // Interface events
    private void ChangedThreadCount(int new_val) {
        computator.ChangedThreadCount(new_val);
    }
    private void ChangeDelay(int new_val) {
        computator.ChangeDelay(new_val);
    }

    private void Start() {
        field.EnableControl(false);
        used_thread_count_slider.setDisable(true);
        start_button.setDisable(true);
        stop_button.setDisable(false);
        reset_button.setDisable(true);
        computator.Start();
    }
    private void Stop() {
        computator.Stop();
        used_thread_count_slider.setDisable(false);
        field.EnableControl(true);
        start_button.setDisable(false);
        stop_button.setDisable(true);
        reset_button.setDisable(false);
    }
    private void Reset() {
        computator.Reset();
        label_counter.setText("0");
    }
}
