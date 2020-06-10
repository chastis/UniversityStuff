import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class Server {
    public static void main(String[] args) throws RemoteException {
        CalculatorImpl calc = new CalculatorImpl();
        Registry registry = LocateRegistry.createRegistry(1234);
        registry.rebind("calc",calc);
    }
}