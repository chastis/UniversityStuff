package com.univ.webService.businessLogic;

import com.univ.webService.DAO.AbonentDAO;
import com.univ.webService.DAO.AreaDAO;
import com.univ.webService.DAO.BillingDAO;
import com.univ.webService.DAO.TariffDAO;
import com.univ.webService.dataModel.Tariff;
import com.univ.webService.factory.BeanFactory;
import com.univ.webService.servlet.Constants;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;
import java.sql.Date;
import java.sql.SQLException;
import java.text.SimpleDateFormat;

public class ChangeService {
    public void changeUserStatus(HttpSession session, HttpServletRequest request, int billingId, String status,
                                 int idAbonent, String pass, String login, BillingDAO billingDAO) throws SQLException {
        billingDAO.updateBillingStatusDB(billingId, status);
        session.setAttribute("sessionId", "109Admin");
        ((ShowService) BeanFactory.getBean(ShowService.class)).showUserInfo(session, request,
                idAbonent, pass, login, ((AbonentDAO) BeanFactory.getBean(AbonentDAO.class)),
                ((AreaDAO) BeanFactory.getBean(AreaDAO.class)), ((BillingDAO) BeanFactory.getBean(BillingDAO.class)),
                ((TariffDAO) BeanFactory.getBean(TariffDAO.class)));
    }

    public void changeTariff(HttpSession session, HttpServletRequest request, int tarifId, int balance, int bonus,
                             int billingId, String login, String pass) throws SQLException {
        TariffDAO tariffDAO = (TariffDAO) BeanFactory.getBean(TariffDAO.class);
        BillingDAO billingDAO = (BillingDAO) BeanFactory.getBean(BillingDAO.class);

        Tariff tariff = tariffDAO.getTariffFromDB(tarifId, Constants.SELECT_ALL_INT).get(0);
        if (bonus >= tariff.getPrice()) {
            bonus -= tariff.getPrice();
        } else {
            balance -= (tariff.getPrice() - bonus);
            bonus = 0;
            billingDAO.updateBalanceBillingDB(billingId, balance);
        }
        billingDAO.updateBonusBillingDB(billingId, bonus);
        billingDAO.updateTariffIdBillingDB(billingId, tariff.getIdTariff());
        billingDAO.updateConnectionDatedBillingDB(billingId,
                new SimpleDateFormat("yyyy-MM-dd HH:mm:ss").format(new Date(System.currentTimeMillis())));
        session.setAttribute("sessionId", Constants.ID_USER);
        ((LoginService) BeanFactory.getBean(LoginService.class)).loginAccount(session, request,
                pass, login,
                ((AbonentDAO) BeanFactory.getBean(AbonentDAO.class)));
    }

}
