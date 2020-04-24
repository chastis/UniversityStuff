package task_a;

import javafx.application.Platform;

public class MyThread extends Thread {
    boolean up;
    private boolean shutdown = false;

    MyThread(boolean up) {
        this.up = up;
    }

    @Override
    public void run() {
        while (!Thread.interrupted()) {
            synchronized (Program.main_slider) {
                try {
                    Platform.runLater(() -> {
                        if (up) {
                            if (Program.main_slider.getValue() < Program.main_slider.getMax())
                                Program.main_slider.setValue(Program.main_slider.getValue() + 5);
                        } else {
                            if (Program.main_slider.getValue() > Program.main_slider.getMin())
                                Program.main_slider.setValue(Program.main_slider.getValue() - 5);
                        }
                    });
                    Thread.sleep(10);
                } catch (InterruptedException ignored) { }
            }
        }
        System.out.println("Thread " + up + " is interrupted");
    }

    public void MyInterrupt() {
        shutdown = true;
    }
}