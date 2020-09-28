package com.univ.webService.dataConnection;

import org.apache.commons.dbcp2.BasicDataSource;

import javax.sql.DataSource;
import java.sql.*;
import java.util.Properties;


public class DataConnection {

    private static final DataSource datasource = createDataSource();

    public static Connection getDBConnection() throws SQLException {
        return datasource.getConnection();
    }

    private static DataSource createDataSource() {
        Properties env = loadJdbcPropertiesFromClassPath();
        BasicDataSource datasource = new BasicDataSource();
        datasource.setDriverClassName(env.getProperty("jdbc.driverClassName"));
        datasource.setUrl(env.getProperty("jdbc.url"));
        datasource.setUsername(env.getProperty("jdbc.username"));
        datasource.setPassword(env.getProperty("jdbc.password"));
        return datasource;
    }

    private static Properties loadJdbcPropertiesFromClassPath() {
        Properties properties = new Properties();
        properties.setProperty("jdbc.driverClassName", "com.mysql.cj.jdbc.Driver");
        properties.setProperty("jdbc.url", "jdbc:mysql://localhost:3306/localdb?useUnicode=true&useJDBCCompliantTimezoneShift=true&useLegacyDatetimeCode=false&serverTimezone=UTC");
        properties.setProperty("jdbc.username", "root");
        properties.setProperty("jdbc.password", "m519021");
        return properties;
    }


    public static void updateDB(String sqlQuery) throws SQLException {
        Connection connection = DataConnection.getDBConnection();
        PreparedStatement pstmt = connection.prepareStatement(sqlQuery);
        pstmt.executeUpdate(sqlQuery);
        connection.close();

    }
}
