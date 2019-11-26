public class sProcess {
  public int cputime;
  public int ioblocking;
  public int userID;
  public int delayTime;
  public int cpudone;
  public int ionext;
  public int numblocked;

  public sProcess (int cputime, int ioblocking, int userID, int delayTime, int cpudone, int ionext, int numblocked) {
    this.cputime = cputime;
    this.ioblocking = ioblocking;
    this.userID = userID;
    this.delayTime = delayTime;
    this.cpudone = cpudone;
    this.ionext = ionext;
    this.numblocked = numblocked;
  } 	
}
