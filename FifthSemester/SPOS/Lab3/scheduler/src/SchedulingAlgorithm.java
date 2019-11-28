// Run() is called from Scheduling.main() and is where
// the scheduling algorithm written by the user resides.
// User modification should occur within the Run() function.

import java.util.*;
import java.io.*;

public class SchedulingAlgorithm {

  public static int GetNextReadyProcess(Vector<sProcess> processesVector, int comptime)
  {
    int bestI = -1;
    for (int i = 0; i < processesVector.size(); i++)
    {
      if (processesVector.get(i).state == sProcessState.RUNNING )
      {
        return i;
      }
      if (processesVector.get(i).state == sProcessState.BLOCKED && processesVector.get(i).blockedTimestamp+processesVector.get(i).delayTime > comptime)
      {
        if (bestI == -1 || processesVector.get(i).blockedTimestamp+processesVector.get(i).delayTime > processesVector.get(bestI).blockedTimestamp+processesVector.get(bestI).delayTime ) {
          processesVector.get(i).unBlock(comptime);
          bestI = i;
        }
      }
    }
    return bestI;
  }
  public static Results Run(int runtime, Vector allProcessVector, Results result) {
    int allComptime = 0;
    int currentComptime = 0;
    int currentProcess = 0;
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
    try
    {
      PrintStream out = new PrintStream(new FileOutputStream(resultsFile));
      for (Vector<sProcess> processVector : usersProcesses.values()) {
          //System.out.println( " id = " + processVector.get(0).userID);
          int size = processVector.size();
          currentComptime = 0;
          currentProcess = 0;
          sProcess process = (sProcess) processVector.get(currentProcess);
          out.println("Process: " + currentProcess + " in user " + process.userID + " registered... (" + process.cputime + " " + process.ioblocking + " " + process.cpudone + " " + process.cpudone + ")");

          while (currentComptime < currentRunTime)
          {
            switch (process.state) {
              case BLOCKED:
                if (process.blockedTimestamp + process.delayTime >= currentComptime)
                {
                  process.unBlock(currentComptime);
                  out.println("Process: " + currentProcess + " in user " + process.userID + " registered... (" + process.cputime + " " + process.ioblocking + " " + process.cpudone + " " + process.cpudone + ")");
                }
                else {
                  int newProcess = GetNextReadyProcess(processVector, currentComptime);
                  if (newProcess == -1)
                  {
                    break;
                  }
                  currentProcess = newProcess;
                  process = (sProcess) processVector.get(currentProcess);
                  out.println("Process: " + currentProcess + " in user " + process.userID + " registered... (" + process.cputime + " " + process.ioblocking + " " + process.cpudone + " " + process.cpudone + ")");
                }
              case RUNNING:
                {
                if (process.cpudone == process.cputime)
                {
                  completed++;
                  process.state = sProcessState.DONE;
                  out.println("Process: " + currentProcess + " in user " + process.userID + " completed... (" + process.cputime + " " + process.ioblocking + " " + process.cpudone + " " + process.cpudone + ")");
                  if (completed == allSize)
                  {
                    result.compuTime = allComptime;
                    out.close();
                    return result;
                  }
                  int newProcess = GetNextReadyProcess(processVector, currentComptime);
                  if (newProcess == -1)
                  {
                    break;
                  }
                  currentProcess = newProcess;
                  process = (sProcess) processVector.get(currentProcess);
                  out.println("Process: " + currentProcess + " in user " + process.userID + " registered... (" + process.cputime + " " + process.ioblocking + " " + process.cpudone + " " + process.cpudone + ")");
                }
                else if (process.blockedTimestamp + process.ioblocking == currentComptime) {
                  out.println("Process: " + currentProcess + " in user " + process.userID + " I/O blocked... (" + process.cputime + " " + process.ioblocking + " " + process.cpudone + " " + process.cpudone + ")");
                  process.block(currentComptime);
                  int newProcess = GetNextReadyProcess(processVector, currentComptime);
                  if (newProcess == -1)
                  {
                    break;
                  }
                  currentProcess = newProcess;
                  process = (sProcess) processVector.get(currentProcess);
                  out.println("Process: " + currentProcess + " in user " + process.userID + " registered... (" + process.cputime + " " + process.ioblocking + " " + process.cpudone + " " + process.cpudone + ")");
                }
              }
              case DONE:
              default:
                {
                //System.out.println( "something go wrong...");
                break;
              }
            }
            if (process.state == sProcessState.RUNNING) process.cpudone++;
            allComptime++;
            currentComptime++;
          }
        for (int i = 0; i < processVector.size(); i++)
        {
          if (processVector.get(i).state == sProcessState.RUNNING)
          {
            processVector.get(i).block(currentComptime);
            out.println("Process: " + i + " in user " + processVector.get(i).userID + " I/O blocked... (" + processVector.get(i).cputime + " " + processVector.get(i).ioblocking + " " + processVector.get(i).cpudone + " " + processVector.get(i).cpudone + ")");
          }
        }
      }
      out.close();
    } catch (IOException e) { /* Handle exceptions */ }
    result.compuTime = allComptime;
    return result;
  }
}
