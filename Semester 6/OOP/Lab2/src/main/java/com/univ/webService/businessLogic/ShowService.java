package com.univ.webService.businessLogic;

import com.univ.webService.DAO.AbonentDAO;
import com.univ.webService.DAO.AreaDAO;
import com.univ.webService.DAO.BillingDAO;
import com.univ.webService.DAO.TariffDAO;
import com.univ.webService.dataModel.Abonent;
import com.univ.webService.dataModel.Area;
import com.univ.webService.dataModel.Billing;
import com.univ.webService.dataModel.Tariff;
import com.univ.webService.factory.BeanFactory;
import com.univ.webService.servlet.Constants;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;
import java.sql.SQLException;

public class ShowService {

    public void showUserInfo(HttpSession session, HttpServletRequest request, int idAbonent, String pass, String login,
                             AbonentDAO abonentDAO, AreaDAO areaDAO, BillingDAO billingDAO, TariffDAO tariffDAO) throws SQLException {

        session.setAttribute("idAbonent", idAbonent);
        Abonent abonent;
        try {
            abonent = abonentDAO.getAbonentFromDB(idAbonent, Constants.SELECT_ALL_STR, Constants.SELECT_ALL_STR, Constants.IS_USER).get(0);
        } catch (Exception e) {
            session.setAttribute("sessoinId", Constants.LOGIN_ACCOUNT);
            ((LoginService) BeanFactory.getBean(LoginService.class)).loginAccount(session, request,
                    pass, login, abonentDAO);
            return;
        }
        Area area = areaDAO.getAreaFromDB(abonent.getIdAreaCode()).get(0);
        Billing billing = billingDAO.getBillingFromDB(abonent.getIdBilling()).get(0);
        Tariff tariff = tariffDAO.getTariffFromDB(billing.getIdTariff(), Constants.SELECT_ALL_INT).get(0);

        session.setAttribute("nameTariff", tariff.getNameTariff());
        session.setAttribute("priceTariff", tariff.getPrice());
        session.setAttribute("balance", billing.getBalance());
        session.setAttribute("chargeAmount", billing.getChargeAmount());
        session.setAttribute("connectionDate", billing.getConnectionDate());
        session.setAttribute("area", area.getNameArea());
        session.setAttribute("name", abonent.getName());
        session.setAttribute("surname", abonent.getSurname());
        session.setAttribute("number", abonent.getPhoneNumber());
        session.setAttribute("status", billing.getStatus());
        session.setAttribute("billingId", billing.getIdBilling());
        session.setAttribute("sessionId", Constants.SHOW_USER_BY_ID);
    }

}
