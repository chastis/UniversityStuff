package base_package;

import java.util.ArrayList;
import java.util.concurrent.CyclicBarrier;
import java.util.concurrent.atomic.AtomicBoolean;

public class Line {
    private CyclicBarrier barrier;
    private ArrayList<Soldier> soldiers;
    private ArrayList<OrderThread> orderThreads;

    private ArrayList<Boolean> thread_finished;
    private AtomicBoolean finished;

    Line(int soldier_count, int thread_count) {
        super();

        thread_finished = new ArrayList<>(thread_count);
        for (int i = 0; i < thread_count; i++) thread_finished.add(false);
        this.finished = new AtomicBoolean(false);

        this.barrier = new CyclicBarrier(thread_count, new ViewProgress(this, finished, thread_finished));
        this.soldiers = new ArrayList<>(soldier_count);
        for (int i = 0; i < soldier_count; i++)
            this.soldiers.add(new Soldier());
        this.orderThreads = new ArrayList<>();
        for (int i = 0; i < thread_count; i++) {
            int interval = soldier_count/thread_count;
            OrderThread thread = new OrderThread(finished, thread_finished, i, barrier, soldiers, i*interval, (i+1)*interval);
            thread.setDaemon(true);
            orderThreads.add(thread);
        }
    }
    public void PrintLineState() {
        StringBuilder res = new StringBuilder();
        int i = 0;
        for (Soldier soldier : soldiers) {
            if (i > soldiers.size()/orderThreads.size()) {
                res.append(" ");
                i = 0;
            }
            res.append(soldier);
            i++;
        }
        System.out.println(res);
    }
    public void StartOrdering() {
        PrintLineState();
        for (OrderThread thread : orderThreads) {
            thread.start();
        }
        for (OrderThread thread : orderThreads) {
            try {
                thread.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
