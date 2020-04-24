package main_package;

import javafx.geometry.Point2D;
import javafx.scene.Group;
import javafx.scene.shape.Circle;

class Fighter {
    private static final Point2D start_pos = new Point2D(50, 50);
    private static final int circle_radius = 20;
    private static final int vertical_dist = 50;
    private static final int horizontal_dist = 100;

    int energyTsy;
    private Circle circle;
    private int count_of_victories = 0;

    Fighter(int i, int energyTsy) {
        this.energyTsy = energyTsy;
        circle = new Circle();
        circle.setRadius(circle_radius);
        circle.setCenterX(start_pos.getX());
        circle.setCenterY(start_pos.getY() + vertical_dist * i);
    }
    void SetPane(Group group) {
        group.getChildren().add(circle);
    }
    void goForward() {
        count_of_victories++;
    }
    void Update() {
        for (int i = 0; i < count_of_victories; i++)
            circle.setCenterX(circle.getCenterX() + horizontal_dist);
    }
}
