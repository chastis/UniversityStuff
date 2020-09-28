package com.univ.webService.dataModel;

public class Abonent {
    private int idAbonent;
    private String name;
    private String surname;
    private String phoneNumber;
    private int idAreaCode;
    private int idBilling;
    private String login;
    private String password;
    private int isAdmin;

    public Abonent() {
    }

    public Abonent(int idAbonent, String name, String surname, String phoneNumber, int idAreaCode,
                   int idBilling, String login, String password, int isAdmin) {
        this.idAbonent = idAbonent;
        this.name = name;
        this.surname = surname;
        this.phoneNumber = phoneNumber;
        this.idAreaCode = idAreaCode;
        this.idBilling = idBilling;
        this.login = login;
        this.password = password;
        this.isAdmin = isAdmin;
    }

    public String getLogin() {
        return login;
    }

    public String getPassword() {
        return password;
    }

    public int getIsAdmin() {
        return isAdmin;
    }

    public int getIdAbonent() {
        return idAbonent;
    }

    public String getName() {
        return name;
    }

    public String getSurname() {
        return surname;
    }

    public String getPhoneNumber() {
        return phoneNumber;
    }

    public int getIdAreaCode() {
        return idAreaCode;
    }

    public int getIdBilling() {
        return idBilling;
    }

    public void setIdAbonent(int idAbonent) {
        this.idAbonent = idAbonent;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setSurname(String surname) {
        this.surname = surname;
    }

    public void setPhoneNumber(String phoneNumber) {
        this.phoneNumber = phoneNumber;
    }

    public void setIdAreaCode(int idAreaCode) {
        this.idAreaCode = idAreaCode;
    }

    public void setIdBilling(int idBilling) {
        this.idBilling = idBilling;
    }

    public void setLogin(String login) {
        this.login = login;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public void setIsAdmin(int isAdmin) {
        this.isAdmin = isAdmin;
    }
}
