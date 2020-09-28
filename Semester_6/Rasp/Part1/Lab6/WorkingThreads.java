package base_package;

import java.util.ArrayList;
import java.util.Random;
import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.CyclicBarrier;

public class WorkingThreads extends Thread {
    private Field field;
    private int x_up;
    private int y_up;
    private int x_down;
    private int y_down;

    private CyclicBarrier barrier_death;
    private CyclicBarrier barrier_birth;

    public WorkingThreads(Field field, CyclicBarrier barrier_death, CyclicBarrier barrier_birth, int x_up, int y_up, int x_down, int y_down) {
        this.field = field;
        this.barrier_death = barrier_death;
        this.barrier_birth = barrier_birth;

        this.x_up = x_up;
        this.x_down = x_down;
        this.y_up = y_up;
        this.y_down = y_down;
    }

    @Override
    public String toString() {
        return "Boundaries : " + x_up + ' ' + y_up + ' ' + x_down + ' ' + y_down;
    }
    @Override
    public void run() {
        while (true) {

            for (int i = x_up; i < x_down; i++) {
                for (int j = y_up; j < y_down; j++) {
                    field.getCell(i, j).setWill_die(CellWillDie(i, j));
                    field.getCell(i, j).setWill_alive(CellWillAlive(i, j));
                }
            }

            try {
                barrier_death.await();
            } catch (InterruptedException | BrokenBarrierException e) {
                return;
            }

            for (int i = x_up; i < x_down; i++) {
                for (int j = y_up; j < y_down; j++) {
                    if (field.getCell(i, j).isWill_die()) {
                        field.getCell(i, j).setDeadAlive(false);
                    }
                    if (field.getCell(i, j).isWill_alive()) {
                        field.getCell(i, j).setDeadAlive(true);
                    }
                }
            }

            try {
                barrier_birth.await();
            } catch (InterruptedException | BrokenBarrierException e) {
                return;
            }

            if (isInterrupted()) break;
            try {
                sleep(Computator.delay.get());
            } catch (InterruptedException e) {
                return;
            }
            if (isInterrupted()) break;
        }
    }

    private boolean CellWillDie(int i, int j) {
        if (!field.getCell(i, j).isAlive()) return false; // То, что мертво, умереть не может)
        int current_color = field.getCell(i, j).getColor();
        int count_of_alive_neighbours = 0;

        if (i > 0) {
            if (j > 0)
                if (field.getCell(i-1, j-1).isAlive() && field.getCell(i-1, j-1).getColor() == current_color)
                    count_of_alive_neighbours++;
            if (field.getCell(i-1, j).isAlive() && field.getCell(i-1, j).getColor() == current_color)
                count_of_alive_neighbours++;
            if (j < field.getN()-1)
                if (field.getCell(i-1, j+1).isAlive() && field.getCell(i-1, j+1).getColor() == current_color)
                    count_of_alive_neighbours++;
        }

        if (j > 0)
            if (field.getCell(i, j-1).isAlive() && field.getCell(i, j-1).getColor() == current_color)
                count_of_alive_neighbours++;
        if (j < field.getN()-1)
            if (field.getCell(i, j+1).isAlive() && field.getCell(i, j+1).getColor() == current_color)
                count_of_alive_neighbours++;

        if (i < field.getN()-1) {
            if (j > 0)
                if (field.getCell(i+1, j-1).isAlive() && field.getCell(i+1, j-1).getColor() == current_color)
                    count_of_alive_neighbours++;
            if (field.getCell(i+1, j).isAlive() && field.getCell(i+1, j).getColor() == current_color)
                count_of_alive_neighbours++;
            if (j < field.getN()-1)
                if (field.getCell(i+1, j+1).isAlive() && field.getCell(i+1, j+1).getColor() == current_color)
                    count_of_alive_neighbours++;
        }

        return  (count_of_alive_neighbours < 2 || 3 < count_of_alive_neighbours);
    }
    private boolean CellWillAlive(int i, int j) {
        if (field.getCell(i, j).isAlive()) return false;
        int[] count_of_alive_neighbours = new int[9];

        if (i > 0) {
            if (j > 0)
                if (field.getCell(i-1, j-1).isAlive())
                    count_of_alive_neighbours[field.getCell(i-1, j-1).getColor()]++;
            if (field.getCell(i-1, j).isAlive())
                count_of_alive_neighbours[field.getCell(i-1, j).getColor()]++;
            if (j < field.getN()-1)
                if (field.getCell(i-1, j+1).isAlive())
                    count_of_alive_neighbours[field.getCell(i-1, j+1).getColor()]++;
        }

        if (j > 0)
            if (field.getCell(i, j-1).isAlive())
                count_of_alive_neighbours[field.getCell(i, j-1).getColor()]++;
        if (j < field.getN()-1)
            if (field.getCell(i, j+1).isAlive())
                count_of_alive_neighbours[field.getCell(i, j+1).getColor()]++;

        if (i < field.getN()-1) {
            if (j > 0)
                if (field.getCell(i+1, j-1).isAlive())
                    count_of_alive_neighbours[field.getCell(i+1, j-1).getColor()]++;
            if (field.getCell(i+1, j).isAlive())
                count_of_alive_neighbours[field.getCell(i+1, j).getColor()]++;
            if (j < field.getN()-1)
                if (field.getCell(i+1, j+1).isAlive())
                    count_of_alive_neighbours[field.getCell(i+1, j+1).getColor()]++;
        }

        ArrayList<Integer> new_cell_colors = new ArrayList<>();
        for (int k = 1; k < 9; k++) {
            if (count_of_alive_neighbours[k] == 3)
                new_cell_colors.add(k);
        }
        if (new_cell_colors.size() == 1) {
            field.getCell(i, j).setColor(new_cell_colors.get(0));
            return true;
        } else if (new_cell_colors.size() == 2) {
            Random random = new Random();
            boolean f = random.nextBoolean();
            field.getCell(i, j).setColor(new_cell_colors.get(f ? 0 : 1));
            return true;
        }
        return false;
    }
}
