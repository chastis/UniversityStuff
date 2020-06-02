package com.onlineshop.service;

import com.onlineshop.constants.Constants;
import com.onlineshop.dao.BillingDAO;
import com.onlineshop.dao.ClientDAO;
import com.onlineshop.dao.GoodsDAO;
import com.onlineshop.model.Goods;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import javax.annotation.Resource;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;
import java.sql.SQLException;

@Service
@Transactional
public class ChangeService {
    @Resource
    private ClientDAO clientDAO;
    @Resource
    private BillingDAO billingDAO;
    @Resource
    private GoodsDAO goodsDAO;
    public void changeClientStatus(HttpSession session, HttpServletRequest request) throws SQLException {
        session.setAttribute("sessionId", "Admin");
        int billingId = Integer.parseInt(session.getAttribute("billingId").toString());
        String status = session.getAttribute("status").toString();
        billingDAO.updateBillingStatusDB(status, billingId);
        ShowService showService = new ShowService();
        showService.showUserInfo(session, request);
    }

    public void buyGoods(HttpSession session, HttpServletRequest request) throws SQLException {

        int goodsID = Integer.parseInt(request.getParameter("goodsID"));
        int balance = Integer.parseInt(session.getAttribute("balance").toString());
        int billingId = Integer.parseInt(session.getAttribute("billingId").toString());
        Goods goods = goodsDAO.getGoods(goodsID).get(0);
        if (balance >= goods.getPrice()) {
            balance -= goods.getPrice();
        } else {
            balance = 0;
        }
        billingDAO.updateBillingidGoodsDB(billingId, goods.getIdGoods());
        billingDAO.updateBillingBalanceDB(billingId, balance);
        session.setAttribute("sessionId", Constants.ID_CLIENT);
        LoginService loginService = new LoginService();
        loginService.loginAccount(session, request);
    }

}
