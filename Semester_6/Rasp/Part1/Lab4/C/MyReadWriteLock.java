package base_package;

public class MyReadWriteLock {
    private Integer readSemaphore;
    private Integer writeSemaphore;

    public MyReadWriteLock() {
        readSemaphore = 1;
        writeSemaphore = 1;
    }

    public void ReadLock() {
        while (readSemaphore == 0) {}
        synchronized (readSemaphore) {
            readSemaphore = 0;
        }
    }
    public void ReadUnlock() {
        readSemaphore = 1;
    }
    public void WriteLock() {
        while (readSemaphore == 0) {}
        synchronized (readSemaphore) {
            readSemaphore = 0;
        }
        while (writeSemaphore == 0) {}
        synchronized (writeSemaphore) {
            writeSemaphore = 0;
        }
    }
    public void WriteUnlock() {
        readSemaphore = 1;
        writeSemaphore = 1;
    }
}