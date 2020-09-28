package com.univ.webService.businessLogic;

import com.univ.webService.DAO.AbonentDAO;
import com.univ.webService.DAO.AreaDAO;
import com.univ.webService.DAO.BillingDAO;
import com.univ.webService.DAO.TariffDAO;
import org.junit.jupiter.api.Test;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;
import java.sql.SQLException;

import static org.mockito.Mockito.mock;
import static org.mockito.Mockito.verify;

class ShowServiceTest {

    private AbonentDAO abonentDAO = mock(AbonentDAO.class);
    private AreaDAO areaDAO = mock(AreaDAO.class);
    private BillingDAO billingDAO = mock(BillingDAO.class);
    private TariffDAO tariffDAO = mock(TariffDAO.class);

    private HttpServletRequest request = mock(HttpServletRequest.class);
    private HttpSession session = mock(HttpSession.class);
    private ShowService showService = new ShowService();

    @Test
    void displayedUserInfo() throws SQLException {
        showService.showUserInfo(session, request, 5, "6", "user6", abonentDAO, areaDAO, billingDAO, tariffDAO);
        verify(abonentDAO).getAbonentFromDB(5, "", "", 0);
    }
}