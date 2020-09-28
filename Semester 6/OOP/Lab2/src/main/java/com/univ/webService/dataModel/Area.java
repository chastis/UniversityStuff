package com.univ.webService.dataModel;

public class Area {
    private int idArea;
    private String nameArea;

    public Area() {}

    public Area(int idArea, String nameArea) {
        this.idArea = idArea;
        this.nameArea = nameArea;
    }
    public void setIdArea(int idArea) {
        this.idArea = idArea;
    }

    public void setNameArea(String nameArea) {
        this.nameArea = nameArea;
    }

    public int getIdArea() {
        return idArea;
    }

    public String getNameArea() {
        return nameArea;
    }
}
