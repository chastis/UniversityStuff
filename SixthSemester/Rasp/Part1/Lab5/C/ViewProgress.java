import java.util.ArrayList;

public class ViewProgress extends Thread {
    private ArrayList<Integer> summs;

    ViewProgress(ArrayList<Integer> summs) {
        super();
        this.summs = summs;
    }
    @Override
    public void run() {
        super.run();
        System.out.println("Summs:\t" + summs.get(0) + " \t" + summs.get(1) + " \t" + summs.get(2));
    }
}
