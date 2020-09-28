package task_b;

import javafx.application.Platform;

public class MyThread extends Thread {
    private boolean up;
    private boolean shutdown = false;

    MyThread(boolean up) {
        this.up = up;
    }

    @Override
    public void run() {
        if (Program.semafore != 0) SetStateText("Critical section is used!");
        while (Program.semafore != 0) {}
        Program.semafore = 1;
        SetStateText("Critical section is just taken");
        while (!shutdown) {
            synchronized (this) {
                if (up) {
                    if (Program.main_slider.getValue() < Program.main_slider.getMax())
                        Program.main_slider.setValue(Program.main_slider.getValue() + 5);
                } else {
                    if (Program.main_slider.getValue() > Program.main_slider.getMin())
                        Program.main_slider.setValue(Program.main_slider.getValue() - 5);
                }
                try {
                    Thread.sleep(1);
                } catch (InterruptedException ignored) { }
            }
        }
        Program.semafore = 0;
        SetStateText("Critical section is free");
        System.out.println("Thread " + up + " is interrupted");
    }

    private void SetStateText(String text) {
        Platform.runLater(() -> Program.semafore_state.setText(text));
    }
    public void MyInterrupt() {
        shutdown = true;
    }
}