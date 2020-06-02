import beans.Account;
import beans.Card;
import beans.User;
import database.ConcreteDAO;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.mockito.Mock;
import org.mockito.Mockito;
import org.mockito.MockitoAnnotations;



import javax.servlet.RequestDispatcher;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.PrintWriter;
import java.io.StringWriter;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import static junit.framework.TestCase.assertTrue;
import static org.junit.Assert.assertEquals;
import static org.mockito.Mockito.*;


public class ServletTest {
    @Mock private HttpServletRequest request;
    @Mock private HttpServletResponse response;
    @Mock private RequestDispatcher requestDispatcher;
    private ConcreteDAO concreteDAO;

    @Before
    public void setUp() throws Exception {
        ConcreteDAO.isTomcatDB = false;
        concreteDAO = ConcreteDAO.getInstance();
        MockitoAnnotations.initMocks(this);
    }

    @Test
    public void doPostAuth() throws Exception {
        when(request.getParameter("login")).thenReturn("q");
        when(request.getParameter("pass")).thenReturn("q");
        HttpSession session = mock(HttpSession.class);
        when(request.getSession()).thenReturn(session);
        when(request.getParameter("sign")).thenReturn("in");
        when(request.getRequestDispatcher("index.html")).thenReturn(requestDispatcher);
        StringWriter stringWriter = new StringWriter();
        PrintWriter writer = new PrintWriter(stringWriter);
        when(response.getWriter()).thenReturn(writer);
        new AuthorizationServlet().doPost(request, response);
        assertTrue(stringWriter.toString().contains("tester"));
        assertTrue(stringWriter.toString().contains("123"));
        verify(request.getSession(), times(1)).setAttribute(eq("User"), any(User.class));
        //verify(request.getSession(), times(1)).setAttribute("User", any());
        //verify(requestDispatcher).forward(request,response);
    }
    @Test
    public void doPostAuthFail() throws Exception {
        when(request.getParameter("login")).thenReturn("123");
        when(request.getParameter("pass")).thenReturn("123");
        HttpSession session = mock(HttpSession.class);
        when(request.getSession()).thenReturn(session);
        when(request.getParameter("sign")).thenReturn("in");
        when(request.getRequestDispatcher("index.html")).thenReturn(requestDispatcher);
        when(request.getRequestDispatcher("/dataError.jsp")).thenReturn(requestDispatcher);
        new AuthorizationServlet().doPost(request, response);
        verify(request.getSession(), times(1)).setAttribute(eq("User"), eq((Class<?>) null));
    }
    @Test
    public void doPostAuthZeroLogin() throws Exception {
        when(request.getParameter("login")).thenReturn("");
        when(request.getParameter("pass")).thenReturn("123");
        HttpSession session = mock(HttpSession.class);
        when(request.getSession()).thenReturn(session);
        when(request.getParameter("sign")).thenReturn("in");
        when(request.getRequestDispatcher("index.html")).thenReturn(requestDispatcher);
        when(request.getRequestDispatcher("/dataError.jsp")).thenReturn(requestDispatcher);
        new AuthorizationServlet().doPost(request, response);
        verify(request, times(1)).setAttribute("Error","Wrong login , or password");
    }
    @Test
    public void doPostAuthSuperUser() throws Exception {
        when(request.getParameter("login")).thenReturn("a");
        when(request.getParameter("pass")).thenReturn("a");
        HttpSession session = mock(HttpSession.class);
        when(request.getSession()).thenReturn(session);
        when(request.getParameter("sign")).thenReturn("in");
        when(request.getRequestDispatcher("index.html")).thenReturn(requestDispatcher);
        when(request.getRequestDispatcher("/admin.jsp")).thenReturn(requestDispatcher);
        StringWriter stringWriter = new StringWriter();
        PrintWriter writer = new PrintWriter(stringWriter);
        when(response.getWriter()).thenReturn(writer);
        new AuthorizationServlet().doPost(request, response);
        verify(request.getSession(), times(1)).setAttribute(eq("bankName"), anyString());
        verify(request.getSession(), times(1)).setAttribute(eq("blockedCards"), any(List.class));
    }
    @Test
    public void doGetPay() throws Exception {
        when(request.getParameter("money")).thenReturn("10");
        when(request.getParameter("info")).thenReturn("info");
        when(request.getParameter("card")).thenReturn("123");
        HttpSession session = mock(HttpSession.class);
        when(request.getSession()).thenReturn(session);
        when(request.getParameter("sign")).thenReturn("in");
        when(request.getParameter("command")).thenReturn("Pay");
        Map<Card, Account> cardAccountMap = new HashMap<>();
        Card card = new Card();
        card.setCardNumber("123");
        Account account = new Account();
        account.setMoneyAmount(100);
        cardAccountMap.put(card, account);
        when(session.getAttribute("cardAccountMap")).thenReturn(cardAccountMap);
        User user = new User();
        user.setId(22);
        when(session.getAttribute("User")).thenReturn(user);
        when(session.getAttribute("Payments")).thenReturn(new ArrayList<String>());
        when(request.getRequestDispatcher("index.html")).thenReturn(requestDispatcher);
        StringWriter stringWriter = new StringWriter();
        PrintWriter writer = new PrintWriter(stringWriter);
        when(response.getWriter()).thenReturn(writer);
        new ClientServlet().doGet(request, response);
        assertTrue(stringWriter.toString().contains("22"));
        assertTrue(stringWriter.toString().contains("10"));
        assertTrue(stringWriter.toString().contains("info"));
        assertTrue(stringWriter.toString().contains("123"));
    }
    @Test
    public void doGetPayWithBlockedCard() throws Exception {
        when(request.getParameter("money")).thenReturn("10");
        when(request.getParameter("info")).thenReturn("info");
        when(request.getParameter("card")).thenReturn("9876");
        when(request.getParameter("sign")).thenReturn("in");

        Map<Card, Account> cardAccountMap = new HashMap<>();
        Card card = new Card();
        card.setCardNumber("9876");
        Account account = new Account();
        account.setMoneyAmount(100);
        cardAccountMap.put(card, account);
        HttpSession session = mock(HttpSession.class);
        when(request.getSession()).thenReturn(session);
        when(session.getAttribute("cardAccountMap")).thenReturn(cardAccountMap);
        ClientServlet clientServlet = new ClientServlet();
        when(request.getParameter("command")).thenReturn("Block");
        clientServlet.doGet(request, response);
        when(request.getParameter("command")).thenReturn("Pay");
        clientServlet.doGet(request, response);
        verify(request.getSession(), times(1)).setAttribute(eq("warning"), eq("Warning: Account is blocked"));
    }
    @Test
    public void doGetPayNotEnoughMoney() throws Exception {
        when(request.getParameter("money")).thenReturn("10");
        when(request.getParameter("info")).thenReturn("info");
        when(request.getParameter("card")).thenReturn("123");
        when(request.getParameter("sign")).thenReturn("in");

        Map<Card, Account> cardAccountMap = new HashMap<>();
        Card card = new Card();
        card.setCardNumber("123");
        Account account = new Account();
        account.setMoneyAmount(1);
        cardAccountMap.put(card, account);
        HttpSession session = mock(HttpSession.class);
        when(request.getSession()).thenReturn(session);
        when(session.getAttribute("cardAccountMap")).thenReturn(cardAccountMap);
        ClientServlet clientServlet = new ClientServlet();
        when(request.getParameter("command")).thenReturn("Pay");
        clientServlet.doGet(request, response);
        verify(request.getSession(), times(1)).setAttribute(eq("warning"), eq("Warning: not enough money"));
    }
    @Test
    public void doGetTopUpAcc() throws Exception {
        when(request.getParameter("money")).thenReturn("10");
        when(request.getParameter("card")).thenReturn("123");

        Map<Card, Account> cardAccountMap = new HashMap<>();
        Card card = new Card();
        card.setCardNumber("123");
        Account account = new Account();
        account.setMoneyAmount(1);
        cardAccountMap.put(card, account);
        HttpSession session = mock(HttpSession.class);
        when(request.getSession()).thenReturn(session);
        when(session.getAttribute("cardAccountMap")).thenReturn(cardAccountMap);
        ClientServlet clientServlet = new ClientServlet();
        when(request.getParameter("command")).thenReturn("TopUp");
        clientServlet.doGet(request, response);
        verify(request.getSession(), times(1)).setAttribute(eq("topup"), eq("+10$ to account."));
    }
    @Test
    public void doGetUnblock() throws Exception {
        when(request.getParameter("card")).thenReturn("9876");

        List<Card> blockedCards = new ArrayList<>();
        Card card = new Card();
        card.setCardNumber("9876");
        blockedCards.add(card);
        HttpSession session = mock(HttpSession.class);
        when(request.getSession()).thenReturn(session);
        when(session.getAttribute("blockedCards")).thenReturn(blockedCards);
        when(request.getRequestDispatcher("admin.jsp")).thenReturn(requestDispatcher);
        ClientServlet clientServlet = new ClientServlet();
        when(request.getParameter("command")).thenReturn("Unblock");
        clientServlet.doGet(request, response);
        verify(requestDispatcher, times(1)).forward(request, response);
    }
}