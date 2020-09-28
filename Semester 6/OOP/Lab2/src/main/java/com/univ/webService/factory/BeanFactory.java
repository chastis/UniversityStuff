package com.univ.webService.factory;

import com.univ.webService.DAO.AbonentDAO;
import com.univ.webService.DAO.AreaDAO;
import com.univ.webService.DAO.BillingDAO;
import com.univ.webService.DAO.TariffDAO;
import com.univ.webService.businessLogic.ChangeService;
import com.univ.webService.businessLogic.LoginService;
import com.univ.webService.businessLogic.ShowService;

import java.util.HashMap;
import java.util.Map;

public class BeanFactory {

    private static Map<Class<?>, Object> beans = new HashMap<>();

    static {
        AbonentDAO abonentDAO = new AbonentDAO();
        beans.put(AbonentDAO.class, abonentDAO);

        AreaDAO areaDAO = new AreaDAO();
        beans.put(AreaDAO.class, areaDAO);

        BillingDAO billingDAO = new BillingDAO();
        beans.put(BillingDAO.class, billingDAO);

        TariffDAO tariffDAO = new TariffDAO();
        beans.put(TariffDAO.class, tariffDAO);

        ChangeService changeService = new ChangeService();
        beans.put(ChangeService.class, changeService);

        LoginService loginService = new LoginService();
        beans.put(LoginService.class, loginService);

        ShowService showService = new ShowService();
        beans.put(ShowService.class, showService);
    }

    public static Object getBean(Class<?> beanClass) {
        return beans.get(beanClass);
    }

}
