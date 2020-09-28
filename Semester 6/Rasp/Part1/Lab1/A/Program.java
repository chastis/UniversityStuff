package task_a;

import javafx.application.Application;
import javafx.event.Event;
import javafx.event.EventHandler;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.Slider;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

public class Program extends Application implements EventHandler<Event> {
    public static void main(String[] args) {
        launch(args);
    }

    static volatile Slider main_slider;
    private MyThread thread1;
    private MyThread thread2;
    private int thread1_priority;
    private int thread2_priority;

    private Button stop_button;
    private Button start_button;
    private Button thread1_up;
    private Button thread1_down;
    private Button thread2_up;
    private Button thread2_down;
    private Label thread1_value_label;
    private Label thread2_value_label;

    @Override
    public void start(Stage stage) {

        Label title = new Label("* Controlled slider *");
        main_slider = new Slider();
        VBox top_box = new VBox();
        top_box.getChildren().addAll(title, main_slider);
        top_box.setAlignment(Pos.TOP_CENTER);


        Label center_title = new Label("*** Thread control ***");

        Label thread_label1 = new Label("1-st thread: ");
        thread1_up = new Button("+");
        thread1_up.setOnAction(this::handle);
        thread1_down = new Button("-");
        thread1_down.setOnAction(this::handle);
        thread1_value_label = new Label("0");
        HBox thread_box1 = new HBox();
        thread_box1.getChildren().addAll(thread_label1, thread1_up, thread1_down, thread1_value_label);
        thread_box1.setAlignment(Pos.TOP_CENTER);
        thread_box1.setSpacing(10);

        Label thread_label2 = new Label("2-nd thread: ");
        thread2_up = new Button("+");
        thread2_up.setOnAction(this::handle);
        thread2_down = new Button("-");
        thread2_down.setOnAction(this::handle);
        thread2_value_label = new Label("0");
        HBox thread_box2 = new HBox();
        thread_box2.getChildren().addAll(thread_label2, thread2_up, thread2_down, thread2_value_label);
        thread_box2.setAlignment(Pos.TOP_CENTER);
        thread_box2.setSpacing(10);

        start_button = new Button("Start");
        stop_button = new Button("Stop");
        start_button.setOnAction(this::handle);
        stop_button.setOnAction(this::handle);
        HBox button_box = new HBox();
        button_box.getChildren().addAll(start_button, stop_button);
        button_box.setAlignment(Pos.TOP_CENTER);
        button_box.setSpacing(10);

        VBox center_pane = new VBox();
        center_pane.getChildren().addAll(center_title, thread_box1, thread_box2, button_box);
        center_pane.setAlignment(Pos.TOP_CENTER);
        center_pane.setSpacing(10);

        BorderPane main_pane = new BorderPane();
        main_pane.setTop(top_box);
        main_pane.setCenter(center_pane);

        DisableButton();
        Scene scene = new Scene(main_pane, 500, 200);
        stage.setScene(scene);
        stage.show();
    }

    @Override
    public void handle(Event event) {
        if        (event.getSource() == start_button) {
            AbleButtons();
            thread1 = new MyThread(true);
            thread2 = new MyThread(false);
            thread1.setDaemon(true);
            thread2.setDaemon(true);
            thread1.setPriority(thread1_priority);
            thread2.setPriority(thread2_priority);
            thread1.start();
            thread2.start();
        } else if (event.getSource() == stop_button) {
            thread1.interrupt();
            thread2.interrupt();
            DisableButton();
        } else if (event.getSource() == thread1_up) {
            if (thread1_priority < Thread.MAX_PRIORITY) {
                thread1_priority++;
                thread1.setPriority(thread1_priority);
                thread1_value_label.setText(String.valueOf(thread1_priority));
                System.out.println("thread " + thread1.up + " priority = " + thread1.getPriority());
            }
        } else if (event.getSource() == thread1_down) {
            if (thread1_priority > Thread.MIN_PRIORITY) {
                thread1_priority--;
                thread1.setPriority(thread1_priority);
                thread1_value_label.setText(String.valueOf(thread1_priority));
                System.out.println("thread " + thread1.up + " priority = " + thread1.getPriority());
            }
        } else if (event.getSource() == thread2_up) {
            if (thread2_priority < Thread.MAX_PRIORITY) {
                thread2_priority++;
                thread2.setPriority(thread2_priority);
                thread2_value_label.setText(String.valueOf(thread2_priority));
                System.out.println("thread " + thread2.up + " priority = " + thread2.getPriority());
            }
        } else if (event.getSource() == thread2_down) {
            if (thread2_priority > Thread.MIN_PRIORITY) {
                thread2_priority--;
                thread2.setPriority(thread2_priority);
                thread2_value_label.setText(String.valueOf(thread2_priority));
                System.out.println("thread " + thread2.up + " priority = " + thread2.getPriority());
            }
        }
    }

    private void DisableButton() {
        main_slider.setValue(main_slider.getMax()/2);
        start_button.setDisable(false);
        stop_button.setDisable(true);
        thread1_up.setDisable(true);
        thread1_down.setDisable(true);
        thread2_up.setDisable(true);
        thread2_down.setDisable(true);
        thread1_value_label.setText("5");
        thread2_value_label.setText("5");
        thread1_priority = 5;
        thread2_priority = 5;
    }
    private void AbleButtons() {
        start_button.setDisable(true);
        stop_button.setDisable(false);
        thread1_up.setDisable(false);
        thread1_down.setDisable(false);
        thread2_up.setDisable(false);
        thread2_down.setDisable(false);
    }
}
