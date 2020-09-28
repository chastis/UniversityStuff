package base_package;

public class Main {
    public static void main(String[] args) {
        File file = new File();
        WorkingThread wt1 = new WorkingThread(file, 1);
        WorkingThread wt2 = new WorkingThread(file, 2);
        WorkingThread wt3 = new WorkingThread(file, 3);

        wt1.setDaemon(true);
        wt2.setDaemon(true);
        wt3.setDaemon(true);

        try {
            wt1.start();
            Thread.sleep(500);
            wt2.start();
            Thread.sleep(500);
            wt3.start();

            wt1.join();
            wt2.join();
            wt3.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

    }
}
