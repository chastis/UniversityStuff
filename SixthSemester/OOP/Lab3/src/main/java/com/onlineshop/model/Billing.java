package com.onlineshop.model;

import javax.persistence.*;
import java.util.List;

@Entity
@Table(name = "BILLING")
public class Billing {
    @Id
    @GeneratedValue(strategy= GenerationType.IDENTITY)
    private int idBilling;

    @Column (name = "balance")
    private int balance;

    @Column (name = "idGoods")
    private int idGoods;

    @ManyToMany(fetch = FetchType.EAGER, cascade = CascadeType.MERGE)
    @JoinTable(name = "BILLING_GOODS",
            joinColumns = {@JoinColumn(name = "BILLING_ID", referencedColumnName = "idBilling")},
            inverseJoinColumns = {@JoinColumn(name = "GOODS_ID", referencedColumnName = "idGoods")})
    private List<Goods> goodsList;

    @Column (name = "status")
    private String status;

    public void setIdBilling(int idBilling) {
        this.idBilling = idBilling;
    }

    public void setBalance(int balance) {
        this.balance = balance;
    }

    public void setIdGoods(int idGoods) {
        this.idGoods = idGoods;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public int getIdBilling() {
        return idBilling;
    }

    public int getBalance() {
        return balance;
    }

    public int getIdGoods() {
        return idGoods;
    }

    public String getStatus() {
        return status;
    }
}
