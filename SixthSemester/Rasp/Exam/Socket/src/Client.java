import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.ArrayList;
import java.util.Scanner;

public class Client {

    private static int port = 9876;

    public static void main(String[] args) throws UnknownHostException, IOException, ClassNotFoundException, InterruptedException{
        //get the localhost IP address, if server is running on some other IP, you need to use that
        InetAddress host = InetAddress.getLocalHost();
        Socket socket = null;
        ObjectOutputStream oos = null;
        ObjectInputStream ois = null;


        Scanner scan = new Scanner(System.in);


        while (true)
        {
            System.out.println("Input a num of operation");
            System.out.println("[0] - a*sin(X)");
            System.out.println("[1] - a+cos(x)");
            System.out.println("[2] - tan(x)-a");
            System.out.println("[3] - ax+b");
            System.out.println("[4] - exit");
            int commandIndex = scan.nextInt();
            if (commandIndex == 4)
            {
                socket = new Socket(host.getHostName(), port);
                oos = new ObjectOutputStream(socket.getOutputStream());
                System.out.println("Sending close Request");
                oos.writeInt(commandIndex); oos.flush();
                break;
            }
            System.out.println("Enter coefs and borders in [a, b (optional), left_border, right_border, step");
            float a, b = 0, left, right, step;
            a = scan.nextFloat();
            if (commandIndex == 3) b = scan.nextFloat();
            left = scan.nextFloat();
            right = scan.nextFloat();
            step = scan.nextFloat();

            //establish socket connection to server
            socket = new Socket(host.getHostName(), port);
            //write to socket using ObjectOutputStream
            oos = new ObjectOutputStream(socket.getOutputStream());
            System.out.println("Sending request to Socket Server");

            oos.writeInt(commandIndex); oos.flush();
            oos.writeFloat(a); oos.flush();
            if (commandIndex == 3) oos.writeFloat(b); oos.flush();
            oos.writeFloat(left); oos.flush();
            oos.writeFloat(right); oos.flush();
            oos.writeFloat(step); oos.flush();

            System.out.println("Receiving answers");
            ois = new ObjectInputStream(socket.getInputStream());
            ArrayList<Float> answer = new ArrayList<>();
            answer = (ArrayList<Float>) ois.readObject();

            for (int i = 0; i < answer.size(); ++i)
            {
                System.out.println("" + (left + i * step) + " | " + answer.get(i)) ;
            }

            //close resources
            ois.close();
            oos.close();
            Thread.sleep(100);
        }
        oos.writeInt(4);
        System.out.println("Shutting down client!!");
    }
}
