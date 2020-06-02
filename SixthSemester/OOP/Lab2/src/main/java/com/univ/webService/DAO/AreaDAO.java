package com.univ.webService.DAO;

import com.univ.webService.dataConnection.DataConnection;
import com.univ.webService.dataModel.Area;
import com.univ.webService.servlet.Constants;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class AreaDAO {
    public List<Area> getAreaFromDB(int idArea) throws SQLException {

        final String sqlQuery =
                String.format(
                        "SELECT idArea, nameArea FROM Area WHERE idArea %s",
                        (idArea == Constants.SELECT_ALL_INT ? "LIKE '%'" : "= " + idArea)

                );
        List<Area> getAreaArr = new ArrayList<>();
        Connection connection = DataConnection.getDBConnection();
            PreparedStatement pstmt = connection.prepareStatement(sqlQuery);
            ResultSet rs = pstmt.executeQuery();
            while (rs.next()) {
                Area area = new Area(rs.getInt("idArea"), rs.getString("nameArea"));
                getAreaArr.add(area);
            }
            connection.close();

        return getAreaArr;
    }

}
