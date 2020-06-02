package com.univ.webService.servlet;

import com.univ.webService.DAO.AbonentDAO;
import com.univ.webService.DAO.AreaDAO;
import com.univ.webService.DAO.BillingDAO;
import com.univ.webService.DAO.TariffDAO;
import com.univ.webService.businessLogic.ShowService;
import com.univ.webService.factory.BeanFactory;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;
import java.sql.SQLException;

import static com.univ.webService.validation.Validation.checkDigitValidation;
import static com.univ.webService.validation.Validation.checkXSS;

@WebServlet("/show-users")
public class UsersServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession();
        int idAbonent;
        try {
            idAbonent = Integer.parseInt(checkDigitValidation(checkXSS(request.getParameter("idAbonent"))));
        } catch (Exception e) {
            idAbonent = Integer.parseInt(session.getAttribute("idAbonent").toString());
        }
        session.setAttribute("idAbonent", idAbonent);
        try {
            ((ShowService) BeanFactory.getBean(ShowService.class)).showUserInfo(session, request, idAbonent,
                    session.getAttribute("pass").toString(), session.getAttribute("login").toString(),
                    ((AbonentDAO) BeanFactory.getBean(AbonentDAO.class)), ((AreaDAO) BeanFactory.getBean(AreaDAO.class)),
                    ((BillingDAO) BeanFactory.getBean(BillingDAO.class)), ((TariffDAO) BeanFactory.getBean(TariffDAO.class)));
        } catch (SQLException e) {
            request.getRequestDispatcher("Error.jsp").forward(request, response);
        }
        request.getRequestDispatcher("response.jsp").forward(request, response);
    }
}
