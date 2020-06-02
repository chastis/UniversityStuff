package com.onlineshop.model;

import javax.persistence.*;
import java.util.List;

@Entity
@Table(name = "CLIENT")
public class Client {

    @Id
    @GeneratedValue(strategy= GenerationType.IDENTITY)
    private int idClient;

    @Column (name = "name")
    private String name;

    @Column (name = "surname")
    private String surname;

    @Column (name = "idBilling")
    private int idBilling;

    @ManyToMany(fetch = FetchType.EAGER, cascade = CascadeType.MERGE)
    @JoinTable(name = "CLIENT_BILLING",
            joinColumns = {@JoinColumn(name = "CLIENT_ID", referencedColumnName = "idClient")},
            inverseJoinColumns = {@JoinColumn(name = "BILLING_ID", referencedColumnName = "idBilling")})
    private List<Billing> billingList;



    @Column (name = "login")
    private String login;

    @Column (name = "password")
    private String password;

    @Column (name = "isAdmin")
    private int isAdmin;

    public int getIdClient() {
        return idClient;
    }

    public String getName() {
        return name;
    }

    public String getSurname() {
        return surname;
    }

    public int getIdBilling() {
        return idBilling;
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

    public void setIdClient(int idClient) {
        this.idClient = idClient;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setSurname(String surname) {
        this.surname = surname;
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
