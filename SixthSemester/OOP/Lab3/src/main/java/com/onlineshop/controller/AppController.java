package com.onlineshop.controller;

import java.io.IOException;
import java.sql.SQLException;
import java.util.*;

import com.onlineshop.constants.Constants;
import com.onlineshop.service.*;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.MessageSource;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.security.core.Authentication;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.stereotype.Controller;
import org.springframework.ui.ModelMap;
import org.springframework.validation.BindingResult;
import org.springframework.validation.FieldError;
import org.springframework.web.bind.annotation.*;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;



@Controller
@RequestMapping("/")
@ComponentScan("com.onlineshop")
public class AppController {
   @Autowired
   private ChangeService changeService;
    @Autowired
    private LoginService loginService;
   @Autowired
   private ShowService showService;


    @GetMapping(value = "/login")
    public String loginAccount(HttpServletRequest request) {
        HttpSession session = request.getSession();
        if (session.getAttribute("sessionId") == null) session.setAttribute("sessionId", Constants.LOGIN_ACCOUNT);
        if (request.getParameter("sessionId") != null)
            session.setAttribute("sessionId", request.getParameter("sessionId"));
        try {
            loginService.loginAccount(session, request);
        } catch (SQLException e) {
            return "error";
        }
        if (session.getAttribute("sessionId") == Constants.ID_CLIENT)
            return "user";
        else if (session.getAttribute("sessionId") == Constants.ID_ADMIN)
            return "admin";
        else
            return "index";
    }

    @GetMapping(value = "/show-users")
    public String ShowUser(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            HttpSession session = request.getSession();

            try {
                showService.showUserInfo(session, request);
            } catch (SQLException e) {
                return "error";
            }
        if (session.getAttribute("sessionId") == Constants.ID_CLIENT)
            return "user";
        else if (session.getAttribute("sessionId") == Constants.ID_ADMIN)
            return "admin";
        else
            return "index";
    }

    @GetMapping(value="/buy-goods")
    public String ChangeClient(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            HttpSession session = request.getSession();
            try {
                changeService.buyGoods(session, request);
            } catch (SQLException e) {
                return "error";
            }
        if (session.getAttribute("sessionId") == Constants.ID_CLIENT)
            return "user";
        else if (session.getAttribute("sessionId") == Constants.ID_ADMIN)
            return "admin";
        else
            return "index";
    }

    @GetMapping(value="/change-client-status")
   public String ChangeClientStatus(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            HttpSession session = request.getSession();
            try {
                ChangeService changeService = new ChangeService();
                changeService.changeClientStatus(session, request);
            } catch (SQLException e) {
                return "error";
            }
        if (session.getAttribute("sessionId") == Constants.ID_CLIENT)
            return "user";
        else if (session.getAttribute("sessionId") == Constants.ID_ADMIN)
            return "admin";
            return "index";
    }

    @GetMapping(value = "/login")
    public String login() {
        if (isCurrentAuthenticationAnonymous()) {
            return "login";
        } else {
            String username = getPrincipal();
            User user = userService.findByUsername(username);
            for(UserProfile profile : user.getUserProfiles()){
                if(profile.getType().equals("ADMIN")){
                    return "redirect:/admin";
                }
            }
            return "redirect:/user";
        }

    }
    @GetMapping(value="/logout")
    public String logoutPage (){
        Authentication auth = SecurityContextHolder.getContext().getAuthentication();
        if (auth != null){
            SecurityContextHolder.getContext().setAuthentication(null);
        }
        return "redirect:/login?logout";
    }


}