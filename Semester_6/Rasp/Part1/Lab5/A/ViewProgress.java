package base_package;

import java.util.ArrayList;
import java.util.concurrent.atomic.AtomicBoolean;

public class ViewProgress extends Thread {
    private Line line;
    private ArrayList<Boolean> thread_finished;
    private AtomicBoolean finished;

    ViewProgress(Line line, AtomicBoolean finished, ArrayList<Boolean> thread_finished) {
        super();
        this.line = line;
        this.finished = finished;
        this.thread_finished = thread_finished;
    }
    @Override
    public void run() {
        super.run();
        line.PrintLineState();
        boolean the_end = thread_finished.get(0);
        for (Boolean b : thread_finished)
            the_end &= b;
        if (the_end)
            finished.set(true);
    }
}
