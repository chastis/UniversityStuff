package base_package;

import java.util.ArrayList;
import java.util.concurrent.locks.ReadWriteLock;
import java.util.concurrent.locks.ReentrantReadWriteLock;

public class File {
    public ArrayList<Record> records;
    private ReadWriteLock lock;

    public File() {
        records = InitializeStartRecords();
        lock = new ReentrantReadWriteLock();
    }
    private ArrayList<Record> InitializeStartRecords() {
        ArrayList<Record> res = new ArrayList<>();
        res.add(new Record("Anatolii", "Davydko", "Evgen", "123"));
        res.add(new Record("Max", "Veres", "Nikolas", "321"));
        res.add(new Record("Ava", "Addams", "Boobs", "DD"));
        res.add(new Record("Tessa", "Fowler", "Breast", "TessaNumber"));
        return res;
    }

    public void LockRead() {
        lock.readLock().lock();
    }
    public void UnlockRead() {
        lock.readLock().unlock();
    }
    public void LockWrite() {
        lock.writeLock().lock();
    }
    public void UnlockWrite() {
        lock.writeLock().unlock();
    }
}
