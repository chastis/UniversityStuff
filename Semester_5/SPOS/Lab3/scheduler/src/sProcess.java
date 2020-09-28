enum sProcessState {
  BLOCKED,
  RUNNING,
  READY,
  DONE
};

public class sProcess {
  public int cputime;
  public int ioblocking;
  public int userID;
  public int delayTime;
  public int cpudone;
  public int blockedTimestamp;
  public int numblocked;
  sProcessState state;

  public sProcess (int cputime, int ioblocking, int userID, int delayTime) {
    this.cputime = cputime;
    this.ioblocking = ioblocking;
    this.userID = userID;
    this.delayTime = delayTime;
    this.cpudone = 0;
    this.blockedTimestamp = 0;
    this.numblocked = 0;
    this.state = sProcessState.READY;
  }
  public void block(int currentTime)
  {
    this.blockedTimestamp = currentTime;
    this.state = sProcessState.BLOCKED;
    this.numblocked++;
  }
  public void unBlock(int currentTime)
  {
    this.blockedTimestamp = currentTime;
    this.state = sProcessState.READY;
  }
  public void ready(int currentTime)
  {
    this.blockedTimestamp = currentTime;
    this.state = sProcessState.READY;
  }
  public void run(int currentTime)
  {
    this.blockedTimestamp = currentTime;
    this.state = sProcessState.RUNNING;
  }
}
