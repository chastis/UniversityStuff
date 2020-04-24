package base_package;

import java.util.ArrayList;
import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.CyclicBarrier;
import java.util.concurrent.atomic.AtomicBoolean;

public class OrderThread extends Thread {
    private CyclicBarrier barrier;
    private ArrayList<Soldier> soldiers;
    private int from;
    private int to;

    private AtomicBoolean finished;
    private ArrayList<Boolean> thread_finished;
    private int index;

    OrderThread(AtomicBoolean finished, ArrayList<Boolean> thread_finished, int index, CyclicBarrier barrier, ArrayList<Soldier> soldiers, int from, int to) {
        super();

        this.finished = finished;
        this.thread_finished = thread_finished;
        this.index = index;

        this.barrier = barrier;
        this.soldiers = soldiers;
        this.from = from;
        this.to = to;
    }
    @Override
    public void run() {
        super.run();
        while (!isOK() || !finished.get()) {
            if (isOK()) thread_finished.set(index, true);
            else thread_finished.set(index, false);
            for (int i = from; i < to; i++) {
                if (i == 0) {
                    if (!soldiers.get(i).isLeft() && soldiers.get(i+1).isLeft()) {
                        soldiers.get(i).TurnLeft();
                    }
                } else if (i == soldiers.size()-1){
                    if (soldiers.get(i).isLeft() && !soldiers.get(i-1).isLeft()) {
                        soldiers.get(i).TurnRight();
                    }
                } else {
                    if (soldiers.get(i).isLeft() && !soldiers.get(i-1).isLeft()) {
                        soldiers.get(i).TurnRight();
                    }
                    else if (!soldiers.get(i).isLeft() && soldiers.get(i+1).isLeft()) {
                        soldiers.get(i).TurnLeft();
                    }
                }
            }
            try {
                sleep(100);
                barrier.await();
            } catch (InterruptedException | BrokenBarrierException e) {
                e.printStackTrace();
            }
        }
    }
    private boolean isOK() {
        for (int i = from; i < to; i++) {
            if (i == 0) {
                if (!soldiers.get(i).isLeft() && soldiers.get(i+1).isLeft())
                    return false;
            }
            else if (i == soldiers.size()-1) {
                if (soldiers.get(i).isLeft() && !soldiers.get(i-1).isLeft())
                    return false;
            } else {
                if (soldiers.get(i).isLeft() && !soldiers.get(i-1).isLeft())
                    return false;
                if (!soldiers.get(i).isLeft() && soldiers.get(i+1).isLeft())
                    return false;
            }
        }
        return true;
    }
}
