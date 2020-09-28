package com.univ.webService.businessLogic;

import com.univ.webService.DAO.AbonentDAO;
import org.junit.jupiter.api.Test;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;
import java.sql.SQLException;

import static org.mockito.Mockito.*;

class LoginServiceTest {

    private AbonentDAO abonentDAO = mock(AbonentDAO.class);

    private HttpServletRequest request = mock(HttpServletRequest.class);
    private HttpSession session = mock(HttpSession.class);
    private LoginService loginService = new LoginService();

    @Test
    void sessionCanBeSaved() throws SQLException {
        loginService.loginAccount(session, request, "admin", "admin", abonentDAO);
        verify(abonentDAO).getAbonentFromDB(-1, "admin", "admin", -1);
    }
}