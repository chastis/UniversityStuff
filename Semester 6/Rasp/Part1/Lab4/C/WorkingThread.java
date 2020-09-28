package base_package;

import java.util.Random;

public class WorkingThread extends Thread {
    private Matrix matrix;
    private int task;

    public WorkingThread(Matrix matrix, int task) {
        this.matrix = matrix;
        this.task = task;
    }
    @Override
    public void run() {
        switch (task) {
            case 1: ChangePrice(); break;
            case 2: AddDeleteWay(); break;
            case 3: ShowPrice(); break;
            case 4: ShowMatrix(); break;
            default:
                System.out.println("Unknown task!");
        }
    }

    public void ChangePrice() {
        Random random = new Random();
        while (true) {
            int i = Math.abs(random.nextInt()) % matrix.getN();
            int j = Math.abs(random.nextInt()) % matrix.getN();
            int new_price = Math.abs(random.nextInt()) % 100;

            try {
                while (matrix.getValue(i, j) == -1) {
                    i = Math.abs(random.nextInt()) % matrix.getN();
                    j = Math.abs(random.nextInt()) % matrix.getN();
                    new_price = Math.abs(random.nextInt()) % 100;
                }
            } catch (Exception e) {
                e.printStackTrace();
            }

            matrix.LockWrite(i, j);
            System.out.println("Changing price: Start");
            try {
                matrix.setValue(i, j, new_price);
                System.out.println("Changing price: from " + i + " to " + j + " is " + new_price);
            } catch (Exception e) {
                e.printStackTrace();
            }
            System.out.println("Changing price: Finish");
            matrix.UnlockWrite(i, j);

            try {
                Thread.sleep(8000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
    public void AddDeleteWay() {
        Random random = new Random();
        while (true) {
            int i = Math.abs(random.nextInt()) % matrix.getN();
            int j = Math.abs(random.nextInt()) % matrix.getN();
            boolean add = random.nextBoolean();

            if (add) {
                try {
                    while (matrix.getValue(i, j) == -1) {
                        i = Math.abs(random.nextInt()) % matrix.getN();
                        j = Math.abs(random.nextInt()) % matrix.getN();
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                }
            } else {
                try {
                    while (matrix.getValue(i, j) != -1) {
                        i = Math.abs(random.nextInt()) % matrix.getN();
                        j = Math.abs(random.nextInt()) % matrix.getN();
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }

            matrix.LockWrite(i, j);
            System.out.println("Add/Delete way: Start");
            try {
                if (add) {
                    int new_price = Math.abs(random.nextInt()) % 100;
                    try {
                        matrix.setValue(i, j, new_price);
                        System.out.println("Changing price: Added from " + i + " to " + j + " is " + new_price);
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                } else {
                    try {
                        matrix.setValue(i, j, -1);
                        System.out.println("Changing price: Deleted from " + i + " to " + j);
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }
                matrix.setValue(i, j, -1);
            } catch (Exception e) {
                e.printStackTrace();
            }
            System.out.println("Add/Delete way: Finish");
            matrix.UnlockWrite(i, j);

            try {
                Thread.sleep(6000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
    public void ShowPrice() {
        Random random = new Random();
        while (true) {
            int i = Math.abs(random.nextInt()) % matrix.getN();
            int j = Math.abs(random.nextInt()) % matrix.getN();
            try {
                while (matrix.getValue(i, j) < 0)
                    j = Math.abs(random.nextInt()) % matrix.getN();
            } catch (Exception e) {
                e.printStackTrace();
            }

            matrix.LockRead(i, j);
            System.out.println("Price: Start");
            try {
                System.out.println("Price: from " + i + " to " + j + " costs = " + matrix.getValue(i, j));
            } catch (Exception e) {
                e.printStackTrace();
            }
            System.out.println("Price: End");
            matrix.UnlockRead(i, j);

            try {
                Thread.sleep(4000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    public void ShowMatrix() {
        while (true) {
            matrix.LockRead();
            matrix.PrintMatrix();
            matrix.UnlockRead();
            try {
                Thread.sleep(2000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}