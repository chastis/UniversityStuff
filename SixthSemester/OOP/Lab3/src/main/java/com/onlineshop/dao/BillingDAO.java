package com.onlineshop.dao;

import com.onlineshop.model.Billing;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Modifying;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.query.Param;

import java.util.List;

public interface BillingDAO extends JpaRepository<Billing, Integer> {
    @Query("SELECT b from Billing b where b.idBilling =?1")
    List<Billing> getBillingById(int idBilling);

    @Modifying
    @Query("UPDATE Billing u SET u.status = :Status WHERE u.idBilling = :idBilling")
    int updateBillingStatusDB(@Param("Status") String status, @Param("idBilling") int idBilling);

    @Modifying
    @Query("UPDATE Billing u SET u.balance = :Balance WHERE u.idBilling = :idBilling")
    int updateBillingBalanceDB(@Param("Balance") int balance, @Param("idBilling") int idBilling);

    @Modifying
    @Query("UPDATE Billing u SET u.idGoods = :idGoods WHERE u.idBilling = :idBilling")
    int updateBillingidGoodsDB(@Param("idGoods") int idGoods, @Param("idBilling") int idBilling);




}
