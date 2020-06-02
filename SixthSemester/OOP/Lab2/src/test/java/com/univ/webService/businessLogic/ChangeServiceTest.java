package com.univ.webService.businessLogic;

import com.univ.webService.DAO.BillingDAO;
import org.junit.jupiter.api.Test;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;
import java.sql.SQLException;

import static org.mockito.Mockito.mock;
import static org.mockito.Mockito.verify;
import static org.mockito.internal.verification.VerificationModeFactory.times;

class ChangeServiceTest {

    private BillingDAO billingDAO = mock(BillingDAO.class);

    private HttpServletRequest request = mock(HttpServletRequest.class);
    private HttpSession session = mock(HttpSession.class);
    private ChangeService changeService = new ChangeService();

    @Test
    void UserStatusCanBeChanged() throws SQLException {
        changeService.changeUserStatus(session, request, 1, "disabled", 1, "pass", "login", billingDAO);
        verify(billingDAO, times(1)).updateBillingStatusDB(1, "disabled");
        verify(billingDAO).updateBillingStatusDB(1, "disabled");

    }

}