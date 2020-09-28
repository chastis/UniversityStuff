package base_package;

class Smoker extends Thread{
    private int needed_item;

    Smoker(int needed_item) {
       this.needed_item = needed_item;
    }

    private void LookAtTheTable() {
        try {
            Action.smoker_is_smoking.acquire();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        switch (needed_item) {
            case 0:
                if (Action.table.tabaco) {
                    Action.table.tabaco = false;
                    System.out.println("Tabaco smoker is smoking");
                    makeCigarAndSmoke();
                    Action.mediator_is_working.release();
                } else Action.smoker_is_smoking.release();
                break;
            case 1:
                if (Action.table.paper) {
                    Action.table.paper = false;
                    System.out.println("Paper smoker is smoking");
                    makeCigarAndSmoke();
                    Action.mediator_is_working.release();
                } else Action.smoker_is_smoking.release();
                break;
            case 2:
                if (Action.table.matches) {
                    Action.table.matches = false;
                    System.out.println("Matches smoker is smoking");
                    makeCigarAndSmoke();
                    Action.mediator_is_working.release();
                } else Action.smoker_is_smoking.release();
                break;
        }
    }

    private void makeCigarAndSmoke() {
        try {
            Thread.sleep(1000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void run() {
        while (true) {
            LookAtTheTable();
        }
    }
}
