package com.univ.webService.DAO;

import com.univ.webService.dataConnection.DataConnection;
import com.univ.webService.dataModel.Billing;
import com.univ.webService.servlet.Constants;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class BillingDAO {
    public List<Billing> getBillingFromDB(int idBilling) throws SQLException {

        final String sqlQuery =
                String.format(
                        "SELECT * FROM Billing WHERE idBilling %s ",
                        idBilling == Constants.SELECT_ALL_INT ? "LIKE '%'" : "= " + idBilling
                );
        List<Billing> getBillingArr = new ArrayList<>();
        Connection connection = DataConnection.getDBConnection();
        PreparedStatement pstmt = connection.prepareStatement(sqlQuery);
        ResultSet rs = pstmt.executeQuery();

        while (rs.next()) {
            Billing billing = new Billing(rs.getInt("idBilling"), rs.getInt("Balance"), rs.getInt("chargeAmount"),
                    rs.getString("connectionDate"), rs.getInt("idTariff"), rs.getString("Status"));
            getBillingArr.add(billing);
        }
        connection.close();

        return getBillingArr;
    }

    public void updateBillingStatusDB(int idBilling, String status) throws SQLException {
        status = status.equals("disabled") ? "enabled" : "disabled";
        String sqlQuery =
                String.format(
                        "UPDATE Billing SET Status = '%s' WHERE idBilling = '%s'",
                        status,
                        idBilling
                );
        DataConnection.updateDB(sqlQuery);
    }

    public void updateBonusBillingDB(int idBilling, int bonus) throws SQLException {
        String sqlQuery =
                String.format(
                        "UPDATE Billing SET chargeAmount = '%s' WHERE idBilling = '%s'",
                        bonus,
                        idBilling
                );
        DataConnection.updateDB(sqlQuery);
    }

    public void updateBalanceBillingDB(int idBilling, int balance) throws SQLException {
        String sqlQuery =
                String.format(
                        "UPDATE Billing SET Balance = '%s' WHERE idBilling = '%s'",
                        balance,
                        idBilling
                );
        DataConnection.updateDB(sqlQuery);
    }

    public void updateTariffIdBillingDB(int idBilling, int idTariff) throws SQLException {
        String sqlQuery =
                String.format(
                        "UPDATE Billing SET idTariff = '%s' WHERE idBilling = '%s'",
                        idTariff,
                        idBilling
                );
        DataConnection.updateDB(sqlQuery);
    }

    public void updateConnectionDatedBillingDB(int idBilling, String time) throws SQLException {
        String sqlQuery =
                String.format(
                        "UPDATE Billing SET connectionDate = '%s' WHERE idBilling = '%s'",
                        time,
                        idBilling
                );
        DataConnection.updateDB(sqlQuery);
    }
}
