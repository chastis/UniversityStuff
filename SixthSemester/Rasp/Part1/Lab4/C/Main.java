package base_package;

public class Main {
    public static void main(String[] args) {
        Matrix matrix = new Matrix(5);
        WorkingThread wt1 = new WorkingThread(matrix, 1);
        WorkingThread wt2 = new WorkingThread(matrix, 2);
        WorkingThread wt3 = new WorkingThread(matrix, 3);
        WorkingThread wt4 = new WorkingThread(matrix, 4);

        wt1.setDaemon(true);
        wt2.setDaemon(true);
        wt3.setDaemon(true);
        wt4.setDaemon(true);

        try {
            wt4.start();
            wt1.start();
            Thread.sleep(500);
            wt2.start();
            Thread.sleep(500);
            wt3.start();

            wt1.join();
            wt2.join();
            wt3.join();
            wt4.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
