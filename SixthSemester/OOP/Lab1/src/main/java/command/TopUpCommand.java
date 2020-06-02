package command;

import beans.Account;
import beans.Card;

import javax.servlet.ServletException;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class TopUpCommand  extends Command {
    @Override
    public void execute() throws ServletException, IOException {
        int money = Integer.valueOf(req.getParameter("money"));
        String cardNumber = req.getParameter("card");

        Account account = getAccount(cardNumber);

        if(account == null){
            return;
        }
        if(account.getIsBlocked()){
            req.getSession().setAttribute("warning", "Warning: Account is blocked");
        }
        else {
            account.setMoneyAmount(account.getMoneyAmount() + money);
            dao.updateAccount(account);
            req.getSession().setAttribute("topup", "+" + money + "$ to account.");
        }
        resp.sendRedirect("/test/client?command=Payments");
    }
}
