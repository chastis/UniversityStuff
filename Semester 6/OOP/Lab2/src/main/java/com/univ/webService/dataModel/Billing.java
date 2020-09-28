package com.univ.webService.dataModel;

public class Billing {
    private int idBilling;
    private int balance;
    private int chargeAmount;
    private String connectionDate;
    private int idTariff;
    private String status;

    public Billing() {}

    public Billing(int idBilling, int balance, int chargeAmount, String connectionDate, int idTariff, String status) {
        this.idBilling = idBilling;
        this.balance = balance;
        this.chargeAmount = chargeAmount;
        this.connectionDate = connectionDate;
        this.idTariff = idTariff;
        this.status = status;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public String getStatus() {
        return status;
    }

    public void setIdBilling(int idBilling) {
        this.idBilling = idBilling;
    }

    public void setBalance(int balance) {
        this.balance = balance;
    }

    public void setChargeAmount(int chargeAmount) {
        this.chargeAmount = chargeAmount;
    }

    public void setConnectionDate(String connectionDate) {
        this.connectionDate = connectionDate;
    }

    public void setIdTariff(int idTariff) {
        this.idTariff = idTariff;
    }

    public int getIdBilling() {
        return idBilling;
    }

    public int getBalance() {
        return balance;
    }

    public int getChargeAmount() {
        return chargeAmount;
    }

    public String getConnectionDate() {
        return connectionDate;
    }

    public int getIdTariff() {
        return idTariff;
    }
}
