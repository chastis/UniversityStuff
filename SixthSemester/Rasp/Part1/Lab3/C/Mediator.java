package base_package;

import java.util.Random;

class Mediator extends Thread {

    Mediator() {

    }

    @Override
    public void run() {
        while (true) {
            PutItems();
        }
    }

    private void PutItems() {
        try {
            Action.mediator_is_working.acquire();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        System.out.println("Mediator is putting item on table...");
        try {
            Thread.sleep(1000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        Random random = new Random();
        int i = Math.abs(random.nextInt()) % 3;
        switch (i) {
            case 0: Action.table.tabaco  = true;
                System.out.println("Tabaco is put"); break;
            case 1: Action.table.paper   = true;
                System.out.println("Paper is put"); break;
            case 2: Action.table.matches = true;
                System.out.println("Matches is put"); break;
        }

        Action.smoker_is_smoking.release();
    }
}
