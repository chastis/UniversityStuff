package base_package;

import javafx.event.Event;
import javafx.event.EventHandler;
import javafx.scene.input.MouseButton;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.Pane;
import java.util.ArrayList;

public class Field implements EventHandler<Event> {
    private static final int FIELD_SIZE = 500;

    private GridPane field_pane;
    private ArrayList<ArrayList<Cell>> cells;
    private int N;

    public Field(int n) {
        this.field_pane = new GridPane();
        this.field_pane.setGridLinesVisible(true);

        this.N = n;

        this.cells = new ArrayList<>();
        for (int i = 0; i < N; i++) {
            ArrayList<Cell> tmp = new ArrayList<>();
            for (int j = 0; j < N; j++) {
                Cell cell = new Cell(this, FIELD_SIZE/N, i, j);
                this.field_pane.add(cell, i, j);
                tmp.add(cell);
            }
            cells.add(tmp);
        }
    }

    public Pane getPane() {
        return field_pane;
    }
    public int getN() {
        return this.N;
    }
    public int getCellCount() {
        return N*N;
    }
    public Cell getCell(int i, int j) {
        return cells.get(i).get(j);
    }

    public void EnableControl(boolean value) {
        for (ArrayList<Cell> list : cells)
            for (Cell cell : list)
                cell.setButEnable(value);
    }

    @Override
    public void handle(Event event) {
        if (event.getSource() instanceof Cell) {
            Cell current_cell = (Cell) event.getSource();

            if (((MouseEvent) event).getButton() == MouseButton.PRIMARY) {
                current_cell.changeDeadAlive();
            } else if (((MouseEvent) event).getButton() == MouseButton.SECONDARY) {
                current_cell.ChangeColor();
            }
        }
    }
}
