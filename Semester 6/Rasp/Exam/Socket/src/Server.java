import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.lang.ClassNotFoundException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;

class Callback
{
    public boolean bShouldEnded = false;
}

class Calculator implements Runnable
{
    Calculator(Socket inSocket, Callback inC)
    {
        c = inC;
        socket = inSocket;
    }
    @Override
    public void run() {
        try {
            ObjectInputStream ois = new ObjectInputStream(socket.getInputStream());
            System.out.println("Receiving input");
            //convert ObjectInputStream object to String
            int commandIndex = ois.readInt();
            System.out.println("Command " + commandIndex);
            //terminate the server if client sends exit request
            if (commandIndex == 4)
            {
                System.out.println("Close command");
                c.bShouldEnded = true;
                return;
            }

            float a, b = 0, left, right, step;
            a = ois.readFloat();
            if (commandIndex == 3) b = ois.readFloat();
            left = ois.readFloat();
            right = ois.readFloat();
            step = ois.readFloat();
            System.out.println("Message Received: " + a + " " + b + " " + left + " " + right + " " + step);

            ArrayList<Float> answer = new ArrayList<>();
            float curX = left;
            while (curX <= right) {
                float curY = 0;
                switch (commandIndex) {
                    case 0:
                        curY = (float) (a * Math.sin(curX));
                        break;
                    case 1:
                        curY = (float) (a + Math.cos(curX));
                        break;
                    case 2:
                        curY = (float) (-a * Math.tan(curX));
                        break;
                    case 3:
                        curY = (float) (a * curX + b);
                        break;
                }
                answer.add(curY);
                curX += step;
            }
            //create ObjectOutputStream object
            ObjectOutputStream oos = new ObjectOutputStream(socket.getOutputStream());
            //write object to Socket
            oos.writeObject(answer);
            //close resources
            ois.close();
            oos.close();
            socket.close();
        }
        catch (IOException e)
        {

        }
    }

    Socket socket;
    Callback c;
}

public class Server {

    //static ServerSocket variable
    private static ServerSocket server;
    //socket server port on which it will listen
    private static int port = 9876;

    public static void main(String args[]) throws IOException, ClassNotFoundException{
        //create the socket server object
        server = new ServerSocket(port);
        //keep listens indefinitely until receives 'exit' call or program terminates
        while(!c.bShouldEnded){
            System.out.println("Waiting for the client request");
            //creating socket and waiting for client connection
            Socket socket = server.accept();
            //read from socket to ObjectInputStream object

            Calculator calc = new Calculator(socket, c);
            calc.run();

        }
        System.out.println("Shutting down Socket server!!");
        //close the ServerSocket object
        server.close();
    }
    public static Callback c = new Callback();
}
