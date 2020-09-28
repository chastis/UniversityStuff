package base_package;

import java.util.concurrent.CyclicBarrier;

public class Action {
    public static final int BEE_COUNT = 10;
    public static CyclicBarrier barrier = new CyclicBarrier(BEE_COUNT, new Bear());

    public void Go() {
        for (int i = 0; i < 10; i++) {
            new Bee(barrier).start();
            try {
                Thread.sleep(100);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
