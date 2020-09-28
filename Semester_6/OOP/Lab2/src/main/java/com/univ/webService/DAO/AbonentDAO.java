package com.univ.webService.DAO;

import com.univ.webService.dataConnection.DataConnection;
import com.univ.webService.dataModel.Abonent;
import com.univ.webService.servlet.Constants;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class AbonentDAO {
    public List<Abonent> getAbonentFromDB(int idAbonent, String login, String password, int isAdmin) throws SQLException {
        List<Abonent> getAbonentArr = new ArrayList<>();
        Connection connection = DataConnection.getDBConnection();

        final String sqlQuery =
                String.format(
                        "SELECT * FROM Abonent WHERE idAbonent %s AND Login %s AND Password %s AND isAdmin %s",
                        idAbonent == Constants.SELECT_ALL_INT ? "LIKE '%'" : "= " + idAbonent,
                        login.equals(Constants.SELECT_ALL_STR) ? "LIKE '%'" : "= '" + login + "'",
                        password.equals(Constants.SELECT_ALL_STR) ? "LIKE '%'" : "= '" + password + "'",
                        isAdmin == Constants.SELECT_ALL_INT ? "LIKE '%'" : "= " + isAdmin
                );
        PreparedStatement pstmt = connection.prepareStatement(sqlQuery);
        ResultSet rs = pstmt.executeQuery();

        while (rs.next()) {
            Abonent abonent = new Abonent(rs.getInt("idAbonent"), rs.getString("Name"), rs.getString("Surname"),
                    rs.getString("phoneNumber"), rs.getInt("idAreaCode"), rs.getInt("idBilling"),
                    rs.getString("Login"), rs.getString("Password"), rs.getInt("isAdmin"));
            getAbonentArr.add(abonent);
        }
        connection.close();
        return getAbonentArr;
    }
}
