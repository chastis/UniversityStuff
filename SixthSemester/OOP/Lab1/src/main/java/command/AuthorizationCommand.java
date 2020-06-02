package command;

import beans.Account;
import beans.Bank;
import beans.Card;
import beans.User;

import javax.security.auth.login.AccountException;
import javax.servlet.ServletException;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class AuthorizationCommand extends Command {

    @Override
    public void execute() throws IOException, ServletException {
        User user;
        if(req.getSession().getAttribute("registrated") == null
                || !(boolean)req.getSession().getAttribute("registrated")){
            user=dao.getUser(req.getParameter("login"),req.getParameter("pass"));
            req.getSession().setAttribute("User", user);

           // req.getSession().setAttribute("registrated", false);
        }
        else{
            user = (User)req.getSession().getAttribute("User");
            req.getSession().setAttribute("registrated", false);
        }
        if (user!=null){
            resp.getWriter().write(user.getName()); // testing
            if(user.getIsSuperUser()){
                Bank bank = dao.getBank(user);

                List<Card> blockedCards = dao.getBlockedCards(bank.getAccounts());

                req.getSession().setAttribute("blockedCards", blockedCards);
                req.getSession().setAttribute("bankName", bank.getName());
                req.getRequestDispatcher("/admin.jsp").forward(req, resp);
            }
            else {
                req.getSession().setAttribute("block", false);
                req.getSession().setAttribute("Payments", null);
                List<Card> cards = dao.getUsersCards(user);
                List<Account> accounts = dao.getAccounts(cards);
                Map<Card, Account> cardAccountMap = new HashMap<>();
                for (int i = 0; i < cards.size(); i++) {
                    cardAccountMap.put(cards.get(i), accounts.get(i));
                    resp.getWriter().write(cards.get(i).getCardNumber());
                }

                req.getSession().setAttribute("cardAccountMap", cardAccountMap);
                resp.sendRedirect("client?command=Payments");
            }
        }
        else{
            req.setAttribute("Error","Wrong login , or password");
            req.getRequestDispatcher("/dataError.jsp").forward(req,resp);
        }

    }
}
