package base_package;

import javafx.application.Platform;

import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.CyclicBarrier;

public class Bee extends Thread {
    private CyclicBarrier barrier;

    Bee(CyclicBarrier barrier) {
        this.barrier = barrier;
    }
    @Override
    public void run() {
        while (true) {
            try {
                Thread.sleep(800);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            synchronized (Program.slider) {
                Platform.runLater(() -> Program.slider.setValue(Program.slider.getValue() + 10));
            }
            try {
                barrier.await();
            } catch (InterruptedException | BrokenBarrierException e) {
                e.printStackTrace();
            }
        }
    }
}
