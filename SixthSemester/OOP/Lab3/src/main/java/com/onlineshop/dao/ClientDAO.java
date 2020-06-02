package com.onlineshop.dao;

import com.onlineshop.model.Client;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;

import java.util.List;

public interface ClientDAO extends JpaRepository<Client, Integer> {
    @Query("SELECT client FROM Client client where  client.idClient = ?1 and client.login = ?2 and client.password =?3 and client.isAdmin = ?4")
    List<Client> getClient(int idClient, String login, String password, int isAdmin);
}
