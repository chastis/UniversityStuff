package main_package;

import java.util.concurrent.RecursiveTask;

public class Challenge extends RecursiveTask<Integer> {
    private final int left;
    private final int right;

    Challenge(final int left, final int right) {
      this.left  = left;
      this.right = right;
    }

    @Override
    protected Integer compute() {
        if (right - left < 3) {
            return letsBattle(left, left+1);
        } else {
            int middle = (left + right)/2;
            Challenge ch1 = new Challenge(left, middle);
            Challenge ch2 = new Challenge(middle, right);
            ch1.fork();
            ch2.fork();
            int f1 = ch1.join();
            int f2 = ch2.join();
            return letsBattle(f1, f2);
        }
    }
    private int letsBattle(int ind1, int ind2) {
        Fighter f1 = Program.fighters.get(ind1);
        Fighter f2 = Program.fighters.get(ind2);
        int res;
        if (f1.energyTsy < f2.energyTsy) {
            f2.goForward();
            res = ind2;
        } else {
            f1.goForward();
            res = ind1;
        }
        return res;
    }
}
