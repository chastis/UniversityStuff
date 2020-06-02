package com.onlineshop.model;

import javax.persistence.*;

@Entity
@Table(name = "GOODS")
public class Goods {
    @Id
    @GeneratedValue(strategy= GenerationType.IDENTITY)
    private int idGoods;

    @Column(name = "nameGoods")
    private String nameGoods;

    @Column(name = "price")
    private int price;


    public int getIdGoods() {
        return idGoods;
    }

    public void setIdGoods(int idGoods) {
        this.idGoods = idGoods;
    }

    public String getNameGoods() {
        return nameGoods;
    }

    public void setNameGoods(String nameGoods) {
        this.nameGoods = nameGoods;
    }

    public int getPrice() {
        return price;
    }

    public void setPrice(int price) {
        this.price = price;
    }
}
