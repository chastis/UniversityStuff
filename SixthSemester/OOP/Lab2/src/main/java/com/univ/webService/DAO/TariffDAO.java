package com.univ.webService.DAO;

import com.univ.webService.dataConnection.DataConnection;
import com.univ.webService.dataModel.Tariff;
import com.univ.webService.servlet.Constants;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class TariffDAO {
    public List<Tariff> getTariffFromDB(int idTariff, int idArea) throws SQLException {

        final String sqlQuery =
                String.format("SELECT * FROM Tariff WHERE idTariff %s AND idArea %s",
                        idTariff == Constants.SELECT_ALL_INT ? "LIKE '%'" : "= " + idTariff,
                        idArea == Constants.SELECT_ALL_INT ? "LIKE '%'" : "= " + idArea
                );
        List<Tariff> getTariffArr = new ArrayList<>();
        Connection connection = DataConnection.getDBConnection();
        PreparedStatement pstmt = connection.prepareStatement(sqlQuery);
        ResultSet rs = pstmt.executeQuery();

        while (rs.next()) {
            Tariff tariff = new Tariff(rs.getInt("idTariff"), rs.getString("nameTariff"),
                    rs.getInt("Price"), rs.getInt("idArea"));
            getTariffArr.add(tariff);
        }

        connection.close();
        return getTariffArr;
    }

}
