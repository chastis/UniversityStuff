import java.util.ArrayList;
import java.util.Random;
import java.util.concurrent.CyclicBarrier;

public class ThreadController {
    private static final int ARR_SIZE = 10;
    private MyCyclicBarrier barrier;
    private ArrayList<ArrayList<Integer>> number_arrays;
    private ArrayList<Integer> summs;
    private ArrayThread thread1;
    private ArrayThread thread2;
    private ArrayThread thread3;

    ThreadController() {
        this.number_arrays = new ArrayList<>(3);
        this.number_arrays.add(initRandomArray(ARR_SIZE));
        this.number_arrays.add(initRandomArray(ARR_SIZE));
        this.number_arrays.add(initRandomArray(ARR_SIZE));

        this.summs = new ArrayList<>(3);
        this.summs.add(0);
        this.summs.add(0);
        this.summs.add(0);

        this.barrier = new MyCyclicBarrier(3, new ViewProgress(summs));

        this.thread1 = new ArrayThread(barrier, number_arrays.get(0), summs, 0);
        this.thread2 = new ArrayThread(barrier, number_arrays.get(1), summs, 1);
        this.thread3 = new ArrayThread(barrier, number_arrays.get(2), summs, 2);
        this.thread1.setDaemon(true);
        this.thread2.setDaemon(true);
        this.thread3.setDaemon(true);
    }
    private ArrayList<Integer> initRandomArray(int size) {
        ArrayList<Integer> list = new ArrayList<>(size);
        Random random = new Random();
        for (int i = 0; i < size; i++) {
            list.add(random.nextInt() % 10);
        }
        return list;
    }
    public void BeginParty() {
        System.out.println("Begin party!");

        ViewProgress progress = new ViewProgress(summs);
        progress.start();

        try {
            Thread.sleep(100);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        this.thread1.start();
        this.thread2.start();
        this.thread3.start();

        try {
            thread1.join();
            thread2.join();
            thread3.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
