import command.Command;
import command.factory.CommandFactory;
import command.factory.CommandFactoryImpl;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

@WebServlet("/client")
public class ClientServlet extends HttpServlet{
    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        CommandFactory factory= CommandFactoryImpl.getFactory();
        Command command=factory.getCommand(req.getParameter("command"),req,resp);
        command.execute();
    }

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String commandName=req.getParameter("command");
        if (commandName==null){
            req.setAttribute("Error","Wrong command!");
            req.getRequestDispatcher("/dataError.jsp").forward(req,resp);
            return;
        }
        CommandFactory factory= CommandFactoryImpl.getFactory();
        Command command=factory.getCommand(commandName,req,resp);
        command.execute();


    }
}
