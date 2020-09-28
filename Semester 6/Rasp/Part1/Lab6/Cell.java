package base_package;

import javafx.application.Platform;
import javafx.scene.control.Button;

public class Cell extends Button {
    private int x, y;
    private boolean alive;
    private int color;
    private boolean enable;

    private boolean will_die;
    private boolean will_alive;

    public Cell(Field parent, int size, int x, int y) {
        super("");
        setMaxSize(size, size);
        setMinSize(size, size);
        setOnMouseClicked(parent);

        this.x = x;
        this.y = y;

        this.alive = false;
        this.color = 0;
        drawButton();

        this.enable = true;

        this.will_die = false;
        this.will_alive = false;
    }
    public int getX() {
        return this.x;
    }
    public int getY() {
        return this.y;
    }

    // For mouse
    public void ChangeColor() {
        if (!this.enable) return;
        color++;
        drawButton();
    }
    public void changeDeadAlive() {
        if (!this.enable) return;
        alive = !alive;
        drawButton();
    }

    public synchronized void setDeadAlive(boolean val) {
        alive = val;
        drawButton();
    }
    public synchronized void setButEnable(boolean val) {
        this.enable = val;
    }
    public synchronized void setColor(int val) {
        this.color = val;
    }

    private void drawButton() {
        Platform.runLater(() -> {
                    if (alive) {
                        switch (color) {
                            case 1: setStyle("-fx-background-color: #108029"); break;
                            case 2: setStyle("-fx-background-color: #f60b0b"); break;
                            case 3: setStyle("-fx-background-color: #081ad6"); break;
                            case 4: setStyle("-fx-background-color: #d4d600"); break;
                            case 5: setStyle("-fx-background-color: #d60096"); break;
                            case 6: setStyle("-fx-background-color: #d69600"); break;
                            case 7: setStyle("-fx-background-color: #00d1d6"); break;
                            case 8: setStyle("-fx-background-color: #c6d6bb"); break;
                            default:
                                color = 1;
                                setStyle("-fx-background-color: #108029");
                        }
                    } else {
                        color = 0;
                        setStyle("-fx-background-color: #000000");
                    }
            }
        );
    }

    public int getColor() {
        return this.color;
    }
    public boolean isAlive() {
        return this.alive;
    }
    public boolean isWill_die() {
        return will_die;
    }
    public boolean isWill_alive() {
        return will_alive;
    }
    public synchronized void setWill_die(boolean will_die) {
        this.will_die = will_die;
    }
    public synchronized void setWill_alive(boolean will_alive) {
        this.will_alive = will_alive;
    }
}
