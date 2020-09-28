package main_package;

import javafx.application.Application;
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.input.KeyCode;
import javafx.stage.Stage;

import java.util.ArrayList;
import java.util.Random;

public class Program extends Application{
    public static void main(String[] args) {
        launch(args);
    }

    static volatile ArrayList<Fighter> fighters = new ArrayList<>();

    @Override
    public void start(Stage stage) {
        Group fighter_group = new Group();
        Random random = new Random();
        for (int i = 0; i < 8; i++) {
            Fighter fighter = new Fighter(i, random.nextInt()%100);
            fighter.SetPane(fighter_group);
            fighters.add(fighter);
        }
        Scene scene = new Scene(fighter_group, 800, 550);
        scene.setOnKeyPressed(e -> {
            if (e.getCode() == KeyCode.A) {
                Challenge challenge = new Challenge(0, fighters.size());
                fighters.get(challenge.compute()).goForward();
                for (Fighter fighter : fighters)
                    fighter.Update();
            }
        });
        stage.setScene(scene);
        stage.show();
    }
}
