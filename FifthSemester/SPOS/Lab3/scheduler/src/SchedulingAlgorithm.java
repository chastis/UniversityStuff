// Run() is called from Scheduling.main() and is where
// the scheduling algorithm written by the user resides.
// User modification should occur within the Run() function.

import java.util.*;
import java.io.*;

public class SchedulingAlgorithm {

  public static Results Run(int runtime, Vector allProcessVector, Results result) {
    int i = 0;
    int allComptime = 0;
    int currentComptime = 0;
    int currentProcess = 0;
    int previousProcess = 0;
    int allSize = allProcessVector.size();
    int completed = 0;
    String resultsFile = "Summary-Processes";

    // { myChanging

    Map<Integer,Vector<sProcess>> usersProcesses = new HashMap<>();
    for (int j = 0; j < allSize; j++)
    {
      sProcess process = (sProcess) allProcessVector.elementAt(j);

      if (!usersProcesses.containsKey(process.userID))
      {
        usersProcesses.put(process.userID, new Vector<sProcess>());
      }
      usersProcesses.get(process.userID).add(process);

    }

    int currentRunTime = runtime / usersProcesses.size();
    // myChanging }

    result.schedulingType = "Batch (Nonpreemptive)";
    result.schedulingName = "First-Come First-Served";

    for (Vector<sProcess> processVector : usersProcesses.values()) {
      System.out.println( " id = " + processVector.get(0).userID);
      try {
        int size = processVector.size();
        currentComptime = 0;
        PrintStream out = new PrintStream(new FileOutputStream(resultsFile));
        sProcess process = (sProcess) processVector.elementAt(currentProcess);
        out.println("Process: " + currentProcess + " in user " + process.userID + " registered... (" + process.cputime + " " + process.ioblocking + " " + process.cpudone + " " + process.cpudone + ")");
        while (currentComptime < currentRunTime) {
          if (process.cpudone == process.cputime) {
            completed++;
            out.println("Process: " + currentProcess + " in user " + process.userID + " completed... (" + process.cputime + " " + process.ioblocking + " " + process.cpudone + " " + process.cpudone + ")");
            if (completed == allSize) {
              result.compuTime = allComptime;
              out.close();
              return result;
            }
            for (i = size - 1; i >= 0; i--) {
              process = (sProcess) processVector.elementAt(i);
              if (process.cpudone < process.cputime) {
                currentProcess = i;
              }
            }
            process = (sProcess) processVector.elementAt(currentProcess);
            out.println("Process: " + currentProcess + " in user " + process.userID + " registered... (" + process.cputime + " " + process.ioblocking + " " + process.cpudone + " " + process.cpudone + ")");
          }
          if (process.ioblocking == process.ionext) {
            out.println("Process: " + currentProcess + " in user " + process.userID + " I/O blocked... (" + process.cputime + " " + process.ioblocking + " " + process.cpudone + " " + process.cpudone + ")");
            process.numblocked++;
            process.ionext = -process.delayTime;
            previousProcess = currentProcess;
            for (i = size - 1; i >= 0; i--) {
              process = (sProcess) processVector.elementAt(i);
              if (process.cpudone < process.cputime && previousProcess != i) {
                currentProcess = i;
              }
            }
            process = (sProcess) processVector.elementAt(currentProcess);
            out.println("Process: " + currentProcess + " in user " + process.userID + " registered... (" + process.cputime + " " + process.ioblocking + " " + process.cpudone + " " + process.cpudone + ")");
          }
          process.cpudone++;
          if (process.ioblocking > 0) {
            process.ionext++;
          }
          allComptime++;
          currentComptime++;
        }

        out.close();
      } catch (IOException e) { /* Handle exceptions */ }
    }
    result.compuTime = allComptime;
    return result;
  }
}
