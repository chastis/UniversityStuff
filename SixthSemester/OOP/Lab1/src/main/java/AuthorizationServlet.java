import beans.Card;
import command.Command;
import command.factory.CommandFactory;
import command.factory.CommandFactoryImpl;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/auth")
public class AuthorizationServlet extends HttpServlet {

    protected void doPost(HttpServletRequest req, HttpServletResponse resp)
            throws ServletException, IOException {

        if (req.getParameter("login").trim().length()==0||
                req.getParameter("pass").trim().length()==0){
            req.setAttribute("Error","Wrong login , or password");
            req.getRequestDispatcher("/dataError.jsp").forward(req,resp);
        }
        else {
            String sign = req.getParameter("sign");
            CommandFactory factory= CommandFactoryImpl.getFactory();
            Command command;
            if(sign == null){
                req.setAttribute("Error","Error with auth");
                req.getRequestDispatcher("/dataError.jsp").forward(req,resp);
                return;
            }
            else if(sign.equals("in")){
                command = factory.getCommand("Authorization",req,resp);
            }
            else{
                command = factory.getCommand("Registration",req,resp);
            }

            command.execute();
        }
        /*List<Card> list = new ArrayList<>();
        Card card1 = new Card();
        card1.setCardNumber("228");
        list.add(card1);
        Card card2 = new Card();
        card2.setCardNumber("2283");

        list.add(card2);

        request.setAttribute("cards", list);
        List<String> list2 = new ArrayList<>();
        list2.add("sd");
        list2.add("sd1");
        request.setAttribute("names", list2);*/
       // req.getRequestDispatcher("client.jsp").forward(req, resp);
    }
}