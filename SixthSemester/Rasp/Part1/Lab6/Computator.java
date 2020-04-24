package base_package;

import java.util.ArrayList;
import java.util.concurrent.CyclicBarrier;
import java.util.concurrent.atomic.AtomicInteger;

public class Computator {
    private volatile Field field;
    private volatile int thread_count;
    public static volatile AtomicInteger delay;

    private volatile CyclicBarrier barrier_for_death;
    private volatile CyclicBarrier barrier_for_birth;
    private ArrayList<WorkingThreads> threads_list;

    public Computator(Field field) {
        this.field = field;
        this.thread_count = 1;
        this.delay = new AtomicInteger(Main.MAX_DELAY);

        this.barrier_for_death = new CyclicBarrier(thread_count);
        this.barrier_for_birth = new CyclicBarrier(thread_count, new GenerationCounter());
        this.threads_list = new ArrayList<>();
    }

    public void ChangedThreadCount(int new_val) {
        this.thread_count = new_val;
        this.barrier_for_death = new CyclicBarrier(thread_count);
        this.barrier_for_birth = new CyclicBarrier(thread_count, new GenerationCounter());
    }
    public void ChangeDelay(int new_val) {
        delay.set(new_val);
    }

    public void Start() {
        prepareThreads(thread_count, true, 0, 0, field.getN(), field.getN());
        for (WorkingThreads wt : threads_list)
            wt.start();
    }
    public void Stop() {
        try {
            for (WorkingThreads wt : threads_list) {
                wt.interrupt();
            }
            for (WorkingThreads wt : threads_list) {
                wt.join();
            }
            threads_list.clear();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        barrier_for_death.reset();
        barrier_for_birth.reset();
    }
    public void Reset() {
        KillAllCells();
    }

    //private int prepareThreadsColor = 0;
    private void prepareThreads(int threads, boolean vertical, int x_up, int y_up, int x_down, int y_down) {
        if (threads == 1) {
            WorkingThreads wt = new WorkingThreads(field, barrier_for_death, barrier_for_birth, x_up, y_up, x_down, y_down );
            wt.setDaemon(true);
            threads_list.add(wt);
            /*
            prepareThreadsColor++;
            for (int i = x_up; i < x_down; i++) {
                for (int j = y_up; j < y_down; j++) {
                    field.getCell(i, j).changeDeadAlive();
                    for (int k = 0; k < prepareThreadsColor; k++) {
                        field.getCell(i, j).ChangeColor();
                    }
                }
            }
            */
        } else {
            int first_threads = threads / 2;
            int second_threads = threads - first_threads;
            if (vertical) {

                prepareThreads(first_threads, false, x_up, y_up, (x_up + x_down)/2, y_down );
                prepareThreads(second_threads, false, (x_up + x_down)/2, y_up, x_down, y_down);

            } else {

                prepareThreads(first_threads, true, x_up, y_up, x_down, (y_up + y_down)/2 );
                prepareThreads(second_threads, true, x_up, (y_up + y_down)/2, x_down, y_down);
            }
        }
    }
    private void KillAllCells() {
        for (int i = 0; i < field.getN(); i++)
            for (int j = 0; j < field.getN(); j++)
                field.getCell(i, j).setDeadAlive(false);
    }
}
