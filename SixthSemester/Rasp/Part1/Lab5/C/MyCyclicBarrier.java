import java.util.concurrent.Semaphore;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicInteger;

public class MyCyclicBarrier {
    private int generation;
    private AtomicInteger count;
    private AtomicBoolean first;
    private Semaphore semaphore = new Semaphore(1);
    private int parties;
    private Thread MiddleRunnable;

    MyCyclicBarrier(int count) {
        this.generation = 0;
        this.count = new AtomicInteger(0);
        this.first = new AtomicBoolean(true);
        this.parties = count;
        this.MiddleRunnable = null;
    }
    MyCyclicBarrier(int count, Thread newRannable) {
        this.generation = 0;
        this.count = new AtomicInteger(0);
        this.first = new AtomicBoolean(true);
        this.parties = count;
        this.MiddleRunnable = newRannable;
    }

    public void await() {
        count.set(count.get()+1);

        try {
            semaphore.acquire();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        if (first.get()) {
            first.set(false);
            semaphore.release();
            while (count.get() < parties) {}

            count.set(0);
            generation++;
            if (MiddleRunnable != null) {
                Thread runnable = new Thread(MiddleRunnable);
                runnable.setDaemon(true);
                runnable.start();
            }
        } else {
            semaphore.release();
            while (count.get() < parties) {}
        }
    }
}
