package com.univ.webService.validation;

public class Validation {
    public static String checkXSS(String s) {
        return s.replaceAll("<", "&lt;").replaceAll(">", "&gt;").replaceAll("\"", "&quot;").
                replaceAll("'", "&apos;").replaceAll("&", "&amp;");
    }

    public static String checkValidation(String s) {
        if (s.matches("^[A-Za-z0-9]{1,35}")) {
            return s;
        }
        return ",";
    }

    public static String checkDigitValidation(String s) {
        if (s.matches("^[1-9][0-9]{0,4}")) {
            return s;
        }
        return "0";

    }
}
