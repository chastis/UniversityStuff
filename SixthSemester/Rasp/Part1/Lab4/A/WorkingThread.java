package base_package;

public class WorkingThread extends Thread {
    private int task;
    private File file;

    public WorkingThread(File file, int task) {
        this.task = task;
        this.file = file;
    }
    @Override
    public void run() {
        switch (task) {
            case 1: FindPhoneByName(); break;
            case 2: FindNameByPhone(); break;
            case 3: ReadWriteRecords(); break;
            default:
                System.out.println("!!! Unknown task number. !!!");
        }
    }

    private void FindPhoneByName() {
        String name = "Tessa";

        while (true) {
            file.LockRead();
            System.out.println("Search phone by name: Start.");
            for (Record record : file.records) {
                if (record.getName().equals(name))
                    System.out.println("Search phone by name: Found " + record.toString() );
            }

            try {
                Thread.sleep(5000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            System.out.println("Search phone by name: Finish.");
            file.UnlockRead();
        }
    }
    private void FindNameByPhone() {
        String number = "123";

        while (true) {
            file.LockRead();
            System.out.println("Search name by phone: Start.");
            for (Record record : file.records) {
                if (record.getNumber().equals(number))
                    System.out.println("Search name by phone: Found " + record.toString());
            }

            try {
                Thread.sleep(5000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            System.out.println("Search name by phone: Finish.");
            file.UnlockRead();
        }
    }
    private void ReadWriteRecords() {
        Record record1 = new Record("Tessa", "Messa", "papa", "qwe");
        Record record2 = new Record("Angela", "White", "Booom", "123");
        boolean tiktok = false;

        while (true) {
            file.LockWrite();
            System.out.println("Write/delete records: Start.");
            if (tiktok) file.records.add(record1);
            else file.records.remove(record1);

            try {
                Thread.sleep(10000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            System.out.println("Write/delete records: Finish.");
            file.UnlockWrite();

            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            file.LockWrite();
            System.out.println("Write/delete records: Start.");
            if (tiktok) file.records.remove(record2);
            else file.records.add(record2);

            try {
                Thread.sleep(10000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            System.out.println("Write/delete records: Finish.");
            file.UnlockWrite();
        }
    }
}
