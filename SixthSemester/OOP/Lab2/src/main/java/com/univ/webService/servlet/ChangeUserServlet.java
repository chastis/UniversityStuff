package com.univ.webService.servlet;

import com.univ.webService.DAO.BillingDAO;
import com.univ.webService.businessLogic.ChangeService;
import com.univ.webService.factory.BeanFactory;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;
import java.sql.SQLException;

@WebServlet("/change-user-status")
public class ChangeUserServlet extends HttpServlet {
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession();
        try {
            int billingId = Integer.parseInt(session.getAttribute("billingId").toString());
            int idAbonent = Integer.parseInt(session.getAttribute("idAbonent").toString());
            String status = session.getAttribute("status").toString();
            String pass = session.getAttribute("pass").toString();
            String login = session.getAttribute("login").toString();
            ((ChangeService) BeanFactory.getBean(ChangeService.class)).changeUserStatus(session, request, billingId,
                    status, idAbonent, pass, login, ((BillingDAO) BeanFactory.getBean(BillingDAO.class)));
        } catch (SQLException e) {
            request.getRequestDispatcher("Error.jsp").forward(request, response);
        }
        request.getRequestDispatcher("response.jsp").forward(request, response);

    }
}
