package base_package;

import java.util.ArrayList;
import java.util.Random;

public class Matrix {
    private ArrayList<ArrayList<Integer>> values;
    private ArrayList<ArrayList<MyReadWriteLock>> lock;

    public Matrix(int n) {
        lock = new ArrayList<>(n);
        for (int i = 0; i < n; i++) {
            ArrayList<MyReadWriteLock> tmp = new ArrayList<>(n);
            for (int j = 0; j < n; j++)
                tmp.add(new MyReadWriteLock());
            lock.add(tmp);
        }

        Random random = new Random();
        values = new ArrayList<>(n);
        for (int i = 0; i < n; i++) {
            ArrayList<Integer> tmp = new ArrayList<>(n);
            for (int j = 0; j < n; j++)
                tmp.add(Math.abs(random.nextInt()) % 100);
            values.add(tmp);
        }
    }

    public int getN() {
        return values.size();
    }
    public int getValue(int i, int j) throws Exception {
        if (i < 0 || j < 0)
            throw new Exception();
        return values.get(i).get(j);
    }
    public int setValue(int i, int j, int value) throws Exception {
        if (i < 0 || j < 0)
            throw new Exception();
        return values.get(i).set(j, value);
    }

    public void LockRead(int i, int j) {
        lock.get(i).get(j).ReadLock();
    }
    public void UnlockRead(int i, int j) {
        lock.get(i).get(j).ReadUnlock();
    }
    public void LockWrite(int i, int j) {
        lock.get(i).get(j).WriteLock();
    }
    public void UnlockWrite(int i, int j) {
        lock.get(i).get(j).WriteUnlock();
    }

    public void LockRead() {
        for (int i = 0; i < lock.size(); i++)
            for (int j = 0; j< lock.get(0).size(); j++)
                LockRead(i ,j);
    }
    public void UnlockRead() {
        for (int i = 0; i < lock.size(); i++)
            for (int j = 0; j< lock.get(0).size(); j++)
                UnlockRead(i ,j);
    }

    public void PrintMatrix() {
        try {
            for (int i = 0; i < getN(); i++){
                for (int j = 0; j < getN(); j++) {
                    System.out.print(getValue(i, j) + " ");
                }
                System.out.println();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
