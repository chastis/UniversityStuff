package command;

import beans.Account;
import beans.Card;
import beans.User;

import javax.servlet.ServletException;
import java.io.IOException;
import java.util.List;

public class BlockCommand extends Command{
    @Override
    public void execute() throws IOException {
        String cardNumber = req.getParameter("card");
        Account account = getAccount(cardNumber);
        if(account == null){
            return;
        }
        account.setIsBlocked(true);
        dao.blockAccount(account, true);
        req.getSession().setAttribute("warning", "Warning: blocked");

        req.getSession().setAttribute("block", true);
        resp.sendRedirect("/test/client?command=Payments");
    }
}
