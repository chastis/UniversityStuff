package command;

import beans.Account;
import beans.Card;
import database.DAO;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public abstract class Command {
    protected HttpServletRequest req;
    protected HttpServletResponse resp;
    protected DAO dao;


    public void setReq(HttpServletRequest req) {
        this.req = req;
    }

    public void setResp(HttpServletResponse resp) {
        this.resp = resp;
    }

    public void setDao(DAO dao) {
        this.dao = dao;
    }

    public abstract void execute() throws ServletException,IOException;

    public void refreshBlocked(){
        Map<Card, Account> cardAccountMap =  (Map<Card, Account>)req.getSession().getAttribute("cardAccountMap");
        List<Card> cards = new ArrayList<>(cardAccountMap.keySet());
        List<Account> accounts = new ArrayList<>(cardAccountMap.values());
        List<Account> accountsBd = dao.getAccounts(cards);
        boolean isSomeBlocked = false;
        for(int i = 0; i < accounts.size(); i++){
            for(int j = 0; j < accountsBd.size(); j++){
                Account old = accounts.get(i);
                Account fresh = accountsBd.get(i);
                if(old.getId() == fresh.getId()){
                    if(fresh.getIsBlocked()){
                        isSomeBlocked = true;
                    }
                    old.setIsBlocked(fresh.getIsBlocked());
                    break;
                }
            }
        }
        if(!isSomeBlocked){
            req.getSession().setAttribute("block", false);
        }
    }

    public Account getAccount(String cardNumber) throws IOException {
        if(cardNumber.equals("")){
            req.getSession().setAttribute("warning",
                    "Warning: No card. Contact to support");
            return null;
        }
        Map<Card, Account> cardAccountMap =  (Map<Card, Account>)req.getSession().getAttribute("cardAccountMap");
        List<Card> cards = new ArrayList<>(cardAccountMap.keySet());

        Card card = null;
        for(Card item : cards){
            if(item.getCardNumber().equals(cardNumber)){
                card = item;
                break;
            }
        }
        if(card == null){
            return null;
        }
        Account account = cardAccountMap.get(card);
        if(account == null){
            if(req.getSession().getAttribute("warning") == null) {
                req.getSession().setAttribute("warning",
                        "Warning: no account with " + cardNumber + ". Contact to support");
            }
            resp.sendRedirect("/test/client?command=Payments");
            return null;
        }
        return account;
    }
}
