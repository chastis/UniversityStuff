package com.onlineshop;

import org.springframework.security.crypto.bcrypt.BCryptPasswordEncoder;

public class PassEncoder {

    public static void main(String[] args) {
        String password = "admin";
        BCryptPasswordEncoder passwordEncoder = new BCryptPasswordEncoder();
        System.out.println(passwordEncoder.encode(password));
    }
}

