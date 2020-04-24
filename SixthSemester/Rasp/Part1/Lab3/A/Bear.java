package base_package;

import javafx.application.Platform;

import java.util.concurrent.CyclicBarrier;

import static base_package.Action.BEE_COUNT;

public class Bear extends Thread {
    @Override
    public void run() {
        synchronized (Program.slider) {
            Platform.runLater(() -> Program.slider.setValue(0));
        }
        synchronized (Action.barrier) {
            Action.barrier = new CyclicBarrier(BEE_COUNT, new Bear());
        }
    }
}
