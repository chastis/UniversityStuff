package com.onlineshop.service;


import com.onlineshop.constants.Constants;
import com.onlineshop.dao.BillingDAO;
import com.onlineshop.dao.ClientDAO;
import com.onlineshop.dao.GoodsDAO;
import com.onlineshop.model.Billing;
import com.onlineshop.model.Client;
import com.onlineshop.model.Goods;

import javax.annotation.Resource;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;
import java.sql.SQLException;

public class ShowService {
    @Resource
    private ClientDAO clientDAO;
    @Resource
    private BillingDAO billingDAO;
    @Resource
    private GoodsDAO goodsDAO;

    public void showUserInfo(HttpSession session, HttpServletRequest request) throws SQLException {

        int idAbonent;
        try {
            idAbonent = Integer.parseInt(request.getParameter("idAbonent"));
        } catch (Exception e) {
            idAbonent = Integer.parseInt(session.getAttribute("idAbonent").toString());
        }
        session.setAttribute("idAbonent", idAbonent);
        Client client;
        try {
            client = clientDAO.getClient(idAbonent, Constants.SELECT_ALL_STR, Constants.SELECT_ALL_STR, Constants.IS_CLIENT).get(0);
        } catch (Exception e) {
            session.setAttribute("sessoinId", Constants.LOGIN_ACCOUNT);
            return;
        }
        Billing billing = billingDAO.getBillingById(client.getIdBilling()).get(0);
        Goods goods = goodsDAO.getGoods(billing.getIdGoods()).get(0);

        session.setAttribute("nameGoods", goods.getNameGoods());
        session.setAttribute("priceGoods", goods.getPrice());
        session.setAttribute("balance", billing.getBalance());
        session.setAttribute("name", client.getName());
        session.setAttribute("surname", client.getSurname());
        session.setAttribute("status", billing.getStatus());
        session.setAttribute("billingId", billing.getIdBilling());
        session.setAttribute("sessionId", Constants.SHOW_CLIENT_BY_ID);
    }

}
