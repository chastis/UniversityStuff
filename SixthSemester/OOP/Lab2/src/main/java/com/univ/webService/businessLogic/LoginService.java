package com.univ.webService.businessLogic;

import com.univ.webService.DAO.AbonentDAO;
import com.univ.webService.DAO.BillingDAO;
import com.univ.webService.DAO.TariffDAO;
import com.univ.webService.dataModel.Abonent;
import com.univ.webService.dataModel.Billing;
import com.univ.webService.dataModel.Tariff;
import com.univ.webService.factory.BeanFactory;
import com.univ.webService.servlet.Constants;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;
import java.sql.SQLException;
import java.util.List;

public class LoginService {
    public void loginAccount(HttpSession session, HttpServletRequest request, String pass, String login, AbonentDAO abonentDAO) throws SQLException {

        List<Abonent> abonentArr = abonentDAO.getAbonentFromDB(Constants.SELECT_ALL_INT, login, pass, Constants.SELECT_ALL_INT);
        if (abonentArr.size() == 1) {
            Abonent abonent = abonentArr.get(0);
            request.setAttribute("name", abonent.getName());
            request.setAttribute("surname", abonent.getSurname());
            request.setAttribute("number", abonent.getPhoneNumber());
            session.setAttribute("idAbonent", abonent.getIdAbonent());
            if (abonent.getIsAdmin() == 0) {
                session.setAttribute("sessionId", Constants.ID_USER);
                session.setAttribute("type", "Abonent");
                session.setAttribute("billingId", abonent.getIdBilling());
                session.setAttribute("areaCode", abonent.getIdAreaCode());
                showAvailablePackages(session, request);
            } else {
                session.setAttribute("sessionId", Constants.ID_ADMIN);
                session.setAttribute("type", "Admin");
                List<Abonent> userArr = abonentDAO.getAbonentFromDB(Constants.SELECT_ALL_INT, Constants.SELECT_ALL_STR,
                        Constants.SELECT_ALL_STR, Constants.IS_USER);
                request.setAttribute("abonentArr", userArr);
            }
        } else {
            session.setAttribute("sessionId", Constants.ERROR);
            session.setAttribute("type", "Wrong");
        }
    }

    private static void showAvailablePackages(HttpSession session, HttpServletRequest request) throws SQLException {
        int billingId = Integer.parseInt(session.getAttribute("billingId").toString());
        BillingDAO billingDAO = (BillingDAO) BeanFactory.getBean(BillingDAO.class);
        Billing billing = billingDAO.getBillingFromDB(billingId).get(0);
        session.setAttribute("balance", billing.getBalance());
        session.setAttribute("chargeAmount", billing.getChargeAmount());
        session.setAttribute("connectionDate", billing.getConnectionDate());
        TariffDAO tariffDAO = (TariffDAO) BeanFactory.getBean(TariffDAO.class);
        Tariff tariff = tariffDAO.getTariffFromDB(billing.getIdTariff(),
                Constants.SELECT_ALL_INT).get(0);
        session.setAttribute("tariff", tariff.getNameTariff());
        session.setAttribute("tariffPrice", tariff.getPrice());
        List<Tariff> tariffs = tariffDAO.getTariffFromDB(Constants.SELECT_ALL_INT,
                Integer.parseInt(session.getAttribute("areaCode").toString()));
        session.setAttribute("tariffs", tariffs);
        request.setAttribute("tariffs", tariffs);
    }

}
