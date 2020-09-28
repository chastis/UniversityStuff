package com.univ.webService.servlet;

import com.univ.webService.DAO.AbonentDAO;
import com.univ.webService.businessLogic.LoginService;
import com.univ.webService.factory.BeanFactory;
import com.univ.webService.validation.Validation;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;
import java.sql.SQLException;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession();
        if (session.getAttribute("sessionId") == null) session.setAttribute("sessionId", Constants.LOGIN_ACCOUNT);
        if (request.getParameter("sessionId") != null)
            session.setAttribute("sessionId", request.getParameter("sessionId"));
        String pass;
        String login;
        try {
            pass = request.getParameter("pass").equals(Constants.EMPTY_FIELD) ? "," : request.getParameter("pass");
            login = request.getParameter("login");
        } catch (Exception e) {
            pass = session.getAttribute("pass").toString();
            login = session.getAttribute("login").toString();
        }
        pass = Validation.checkValidation(Validation.checkXSS(pass));
        login = Validation.checkValidation(Validation.checkXSS(login));
        session.setAttribute("pass", pass);
        session.setAttribute("login", login);
        try {
            AbonentDAO abonentDAO = (AbonentDAO) BeanFactory.getBean(AbonentDAO.class);
            ((LoginService) BeanFactory.getBean(LoginService.class)).loginAccount(session, request, pass, login, abonentDAO);
        } catch (SQLException e) {
            request.getRequestDispatcher("Error.jsp").forward(request, response);
        }
        request.getRequestDispatcher("response.jsp").forward(request, response);

    }


}
