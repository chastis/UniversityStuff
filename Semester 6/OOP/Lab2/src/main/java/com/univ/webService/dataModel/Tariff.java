package com.univ.webService.dataModel;

public class Tariff {
    private int idTariff;
    private String nameTariff;
    private int price;
    private int idArea;

    public Tariff() {}

    public Tariff(int idTariff, String nameTariff, int price, int idArea) {
        this.idTariff = idTariff;
        this.nameTariff = nameTariff;
        this.price = price;
        this.idArea = idArea;
    }

    public void setIdTariff(int idTariff) {
        this.idTariff = idTariff;
    }

    public void setNameTariff(String nameTariff) {
        this.nameTariff = nameTariff;
    }

    public void setPrice(int price) {
        this.price = price;
    }

    public void setIdArea(int idArea) {
        this.idArea = idArea;
    }

    public int getIdTariff() {
        return idTariff;
    }

    public String getNameTariff() {
        return nameTariff;
    }

    public int getPrice() {
        return price;
    }

    public int getIdArea() {
        return idArea;
    }
}
