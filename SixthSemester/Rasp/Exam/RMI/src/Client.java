import java.net.MalformedURLException;
import java.rmi.Naming;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;
import java.util.List;
import java.rmi.Remote;
import java.util.Scanner;

interface Calculator extends Remote {
    List<Double> calculate(double a, double xFrom, double xTo, double step) throws RemoteException;
}

class CalculatorImpl extends UnicastRemoteObject implements Calculator {
    public CalculatorImpl() throws RemoteException {
        super();
    }

    private double function(double a,double x){
        return Math.tan(x) - a;
    }

    @Override
    public synchronized List<Double> calculate(double a, double xFrom, double xTo, double step) throws RemoteException {
        ArrayList<Double> results = new ArrayList<>();
        for(double t = xFrom; t <=xTo; t+=step){
            results.add(function(a,t));
        }
        return results;
    }
}

public class Client {
    private final Calculator calculator;

    public Client() throws RemoteException, NotBoundException, MalformedURLException {
        String remoteURL = "//127.0.0.1:1234/calc";
        calculator = (Calculator) Naming.lookup(remoteURL);
        System.out.println("RMI object found");
    }

    public List<Double> calculate(double a, double xFrom, double xTo, double step) throws RemoteException {
        return calculator.calculate(a,xFrom,xTo,step);
    }
    public static void main(String[] args) {
        System.out.println("This program can calculate function: tan(x) - a with the help of RMI.");
        double a, xFrom, xTo, step;
        Scanner in = new Scanner(System.in);
        System.out.print("Enter a value: ");
        a = in.nextFloat();
        System.out.print("Enter start x value: ");
        xFrom = in.nextFloat();
        System.out.print("Enter last x value: ");
        xTo = in.nextFloat();
        System.out.print("Enter step: ");
        step = in.nextFloat();

        try {
            Client rmiClient = new Client();
            List<Double> results = rmiClient.calculate(a,xFrom,xTo,step);
            int i = 0;
            for (double t = xFrom; t<=xTo; t+=step){
                System.out.println("|" + t + "|" + results.get(i) + "|");
                i++;
            }
        } catch (RemoteException | NotBoundException | MalformedURLException e) {
            e.printStackTrace();
        }
    }
}