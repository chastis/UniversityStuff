package base_package;

import javafx.application.Platform;

public class GenerationCounter implements Runnable {

    @Override
    public void run() {
        Platform.runLater(() ->
                Main.label_counter.setText(String.valueOf(Integer.parseInt(Main.label_counter.getText())+1))
                );
    }
}
