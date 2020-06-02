package command;

import beans.User;

import javax.servlet.ServletException;
import java.io.IOException;

public class RegistrationCommand extends Command {
    @Override
    public void execute() throws ServletException, IOException {
        String login = req.getParameter("login");
        String password = req.getParameter("pass");
        String name = req.getParameter("name");
        if(dao.checkIsUserExists(login)){
            req.setAttribute("Error","user with " + login + " login already exists");
            req.getRequestDispatcher("/dataError.jsp").forward(req,resp);
        }
        else {
            User user = new User();
            user.setLogin(login);
            user.setName(name);
            user.setPassword(password);
            int id = dao.registrateUser(user);
            user.setIsSuperUser(false);
            user.setId(id);
            req.getSession().setAttribute("User", user);
            req.getSession().setAttribute("registrated", true);
            resp.sendRedirect("/test/client?command=Authorization");
        }
    }
}
