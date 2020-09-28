package base_package;

import java.util.concurrent.Semaphore;

class Action {
    static final Table table = new Table();

    private Smoker smoker_tabaco;
    private Smoker smoker_paper;
    private Smoker smoker_matches;
    private Mediator mediator;

    static final Semaphore mediator_is_working = new Semaphore(1);
    static final Semaphore smoker_is_smoking   = new Semaphore(1);

    Action() {
        this.smoker_tabaco  = new Smoker(0);
        this.smoker_paper   = new Smoker(1);
        this.smoker_matches = new Smoker(2);
        this.mediator = new Mediator();
    }

    void LetsSmoke() {
        try {
            smoker_is_smoking.acquire();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        mediator.start();

        smoker_tabaco.start();
        smoker_paper.start();
        smoker_matches.start();

        try {
            mediator.join();
            smoker_tabaco.join();
            smoker_paper.join();
            smoker_matches.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
