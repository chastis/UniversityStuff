package command;

import beans.Account;
import beans.Card;
import beans.Payment;
import beans.User;

import javax.servlet.ServletException;
import javax.servlet.http.HttpSession;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class PayCommand  extends Command {
    @Override
    public void execute() throws ServletException, IOException {
        int money = Integer.valueOf(req.getParameter("money"));
        String info = req.getParameter("info");
        String cardNumber = req.getParameter("card");
        Account account = getAccount(cardNumber);

        if(account == null){
            return;
        }

        int accountMoney = account.getMoneyAmount();
        if(account.getIsBlocked()){
            req.getSession().setAttribute("warning", "Warning: Account is blocked");
        }
        else if(accountMoney < money){
            req.getSession().setAttribute("warning", "Warning: not enough money");
        }
        else {
            account.setMoneyAmount(accountMoney - money);
            dao.updateAccount(account);
            HttpSession session = req.getSession();
            List<String> payments = (List<String>) session.getAttribute("Payments");
            Payment payment = new Payment();
            payment.setMoney(money);
            payment.setInfo(info);
            payment.setCard(Integer.valueOf(cardNumber));
            User user = (User)req.getSession().getAttribute("User");
            payment.setClient(user.getId());
            resp.getWriter().write(payment.getClient() + " " + payment.getMoney() + " " + payment.getInfo() + " " + payment.getCard());
            int paymentId = dao.addPayment(payment);
            payments.add("ID: " + paymentId + ". Info: " + info +
                    ". Spended money: " + money + ". Card: " + cardNumber);
            session.setAttribute("Payments", payments);
            //add payment to db
        }
        resp.sendRedirect("/test/client?command=Payments");
    }
}
