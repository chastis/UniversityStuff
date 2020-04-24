import java.util.ArrayList;
import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.CyclicBarrier;

public class ArrayThread extends Thread {
    private MyCyclicBarrier barrier;
    private int index;
    private ArrayList<Integer> number_array;
    private ArrayList<Integer> summs;

    ArrayThread(MyCyclicBarrier barrier, ArrayList<Integer> number_array, ArrayList<Integer> summs, int index) {
        super();
        this.barrier = barrier;
        this.number_array = number_array;
        this.summs = summs;
        this.index = index;
    }
    @Override
    public void run() {
        super.run();
        summs.set(index, calculateSum());

        WaitBlyat();

        while (!equals()) {
            int pos = compare();
            if (pos == -1) {
                number_array.set(0, number_array.get(0) + 1);
                summs.set(index, summs.get(index) + 1);
            } else if (pos == 1) {
                number_array.set(0, number_array.get(0) - 1);
                summs.set(index, summs.get(index) - 1);
            }
            WaitBlyat();

            try {
                sleep(100);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    private int calculateSum() {
        int res = 0;
        for (Integer integer : number_array) res += integer;
        return res;
    }
    private boolean equals() {
        int i1 = summs.get(0);
        int i2 = summs.get(1);
        int i3 = summs.get(2);
        return i1 == i2 && i2 == i3;
    }
    private int compare() {
        int current = summs.get(index);
        int another1 = summs.get((index + 1)%summs.size());
        int another2 = summs.get((index + 2)%summs.size());
        if (current < another1 && current < another2) return -1;
        if ((another1 <= current && current < another2) || (another2 <= current && current < another1)) return 0;
        if (another1 < current && another2 < current) return 1;
        return -2;
    }

    private void WaitBlyat() {
        barrier.await();
    }
}
