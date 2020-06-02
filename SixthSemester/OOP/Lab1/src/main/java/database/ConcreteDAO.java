package database;

import beans.*;
import com.mysql.cj.jdbc.MysqlDataSource;

import java.sql.Statement;
import java.sql.Connection;


import javax.naming.Context;
import javax.naming.InitialContext;
import javax.naming.NamingException;
import javax.sql.DataSource;
import java.sql.*;
import java.util.ArrayList;
import java.util.List;

//import org.apache.tomcat.jdbc.pool.DataSource;


public class ConcreteDAO implements DAO {

    private static volatile ConcreteDAO instance;
    private static DataSource dataSource;
    public static boolean isTomcatDB = true;
    Connection connection;

   /* static {
        tomcatDBConnection();
    }*/

    public void tomcatDBConnection(){
        try {
            Context initCtx = new InitialContext();
            Context envCtx = (Context) initCtx.lookup("java:comp/env/");
            dataSource = (DataSource) envCtx.lookup("jdbc/payments");


        } catch (NamingException e) {
            e.printStackTrace();
        }

    }
    public void DBConnection(){
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            MysqlDataSource mysqlDS = new MysqlDataSource();
            mysqlDS.setURL("jdbc:mysql://localhost:3306/payments?serverTimezone=UTC");
            mysqlDS.setUser("root");
            mysqlDS.setPassword("max12398");
            dataSource = mysqlDS;
            isTomcatDB = false;
            //dataSource = setupDataSource("jdbc:mysql://localhost:3306/payments","root", "max12398");
            //connection = DriverManager.getConnection("jdbc:mysql://hostname:port/dbname","username", "password");
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
    }

    private ConcreteDAO(){
        if(isTomcatDB) {
            tomcatDBConnection();
        }
        else{
            DBConnection();
        }
        connection = getConnection();
    }

    public static ConcreteDAO getInstance() {
        if(instance == null){
            synchronized (ConcreteDAO.class){
                if(instance == null){
                    instance = new ConcreteDAO();
                }
            }
        }
        return instance;
    }

    private static synchronized Connection getConnection() {
        try {
            // return (Connection)dataSource.getPooledConnection();//getConnection();
            return (Connection) dataSource.getConnection();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return null;
    }

    @Override
    public User getUser(String login, String password) {
        try {
            PreparedStatement preparedStatement =
                    connection.prepareStatement("select * from clients where login=? and password=?");
            preparedStatement.setString(1, login);
            preparedStatement.setString(2, password);
            ResultSet resultSet = preparedStatement.executeQuery();
            if (resultSet.next()) {
                User user = new User();
                user.setIsSuperUser(resultSet.getBoolean("isSuperUser"));
                user.setId(resultSet.getInt("id"));
                user.setName(resultSet.getString("name"));
                user.setLogin(login);
                user.setPassword(password);
                return user;
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }


        return null;
    }
    @Override
    public boolean checkIsUserExists(String login) {
        try {
            PreparedStatement preparedStatement =
                    connection.prepareStatement("select * from clients where login=?");
            preparedStatement.setString(1, login);
            ResultSet resultSet = preparedStatement.executeQuery();
            if (resultSet.next()) {
                return true;
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }


        return false;
    }
    @Override
    public List<Card> getUsersCards(User user) {
        try {

            int userId = user.getId();
            PreparedStatement preparedStatement =
                    connection.prepareStatement("select * from cards where clientId = ?");
            preparedStatement.setString(1, String.valueOf(userId));
            List<Card> cards = new ArrayList<>();
            ResultSet resultSet = preparedStatement.executeQuery();
            while (resultSet.next()) {
                Card card = new Card();
                card.setCardNumber(String.valueOf(resultSet.getInt("cardNumber")));
                card.setPin(resultSet.getInt("pin"));
                card.setClientId(resultSet.getInt("clientId"));
                card.setAccountId(resultSet.getInt("accId"));
                cards.add(card);
            }
            return cards;
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return null;
    }

    @Override
    public List<Payment> getPayments(User user) {
        try {
            int userId = user.getId();
            PreparedStatement preparedStatement =
                    connection.prepareStatement("select * from payments where clientId = ?");
            preparedStatement.setString(1, String.valueOf(userId));
            List<Payment> payments = new ArrayList<>();
            ResultSet resultSet = preparedStatement.executeQuery();
            while (resultSet.next()) {
                Payment payment = new Payment();
                payment.setId(resultSet.getInt("Id"));
                payment.setCard(resultSet.getInt("cardNumber"));
                payment.setMoney(resultSet.getInt("money"));
                payment.setInfo(resultSet.getString("info"));
                payment.setClient(resultSet.getInt("clientId"));
                payments.add(payment);
            }
            return payments;
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return null;
    }

    @Override
    public int addPayment(Payment payment) {
        try {

            PreparedStatement preparedStatement =
                    connection.prepareStatement("insert into payments(money, clientId, cardNumber, info)" +
                            " values(?, ?, ?, ?)", Statement.RETURN_GENERATED_KEYS);
            preparedStatement.setInt(1, payment.getMoney());
            preparedStatement.setInt(2, payment.getClient());
            preparedStatement.setInt(3, payment.getCard());
            preparedStatement.setString(4, payment.getInfo());
            preparedStatement.executeUpdate();
            ResultSet rs = preparedStatement.getGeneratedKeys();

            if (rs.next()) {
               return (int)rs.getLong(1);
            }


        } catch (SQLException e) {
            e.printStackTrace();
        }
        return -1;
    }

    @Override
    public Account getAccount(Card card) {
        try {
            int accId = card.getAccountId();
            PreparedStatement preparedStatement =
                    connection.prepareStatement("select * from accounts where id = ?");
            preparedStatement.setString(1, String.valueOf(accId));
            ResultSet resultSet = preparedStatement.executeQuery();
            if (resultSet.next()) {
                Account account = new Account();
                account.setId(resultSet.getInt("Id"));
                account.setMoneyAmount(resultSet.getInt("moneyAmount"));
                account.setIsBlocked(resultSet.getBoolean("isBlocked"));
                return account;
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return null;
    }

    @Override
    public Card getCard(String cardNum) {
        try {
            PreparedStatement preparedStatement =
                    connection.prepareStatement("select * from cards where cardNumber = ?");
            preparedStatement.setString(1, String.valueOf(cardNum));
            ResultSet resultSet = preparedStatement.executeQuery();
            if (resultSet.next()) {
                Card card = new Card();
                card.setCardNumber(String.valueOf(resultSet.getInt("cardNumber")));
                card.setPin(resultSet.getInt("pin"));
                card.setClientId(resultSet.getInt("clientId"));
                card.setAccountId(resultSet.getInt("accId"));
                return card;
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return null;
    }

    @Override
    public void updateAccount(Account account) {
        try {
            PreparedStatement preparedStatement =
                    connection.prepareStatement("update accounts set moneyAmount = ? where id = ?;");
            preparedStatement.setString(1, String.valueOf(account.getMoneyAmount()));
            preparedStatement.setString(2, String.valueOf(account.getId()));
            preparedStatement.executeUpdate();

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
    @Override
    public void blockAccount(Account account, boolean isBlock) {
        try {
            PreparedStatement preparedStatement =
                    connection.prepareStatement("update accounts set isBlocked = ? where id = ?;");
            preparedStatement.setBoolean(1, isBlock);
            preparedStatement.setString(2, String.valueOf(account.getId()));
            preparedStatement.executeUpdate();

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    @Override
    public List<Card> getBlockedCards(List<Integer> accounts) {
        try {
            PreparedStatement preparedStatement =
                    connection.prepareStatement("select * from cards join accounts on accId = id where isBlocked = 1;");
            ResultSet resultSet = preparedStatement.executeQuery();
            List<Card> cards = new ArrayList<>();
            while (resultSet.next()) {
                Integer accid = resultSet.getInt("accId");
                if(accounts.contains(accid)) {
                    Card card = new Card();
                    card.setCardNumber(String.valueOf(resultSet.getInt("cardNumber")));
                    card.setPin(resultSet.getInt("pin"));
                    card.setClientId(resultSet.getInt("clientId"));
                    card.setAccountId(accid);
                    cards.add(card);
                }
            }
            return cards;
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return null;
    }

    @Override
    public int registrateUser(User user) {
        try {

            PreparedStatement preparedStatement =
                    connection.prepareStatement("insert into clients(name, login, password, isSuperUser)" +
                            " values(?, ?, ?, 0)", Statement.RETURN_GENERATED_KEYS);
            preparedStatement.setString(1, user.getName());
            preparedStatement.setString(2, user.getLogin());
            preparedStatement.setString(3, user.getPassword());
            preparedStatement.executeUpdate();
            ResultSet rs = preparedStatement.getGeneratedKeys();

            if (rs.next()) {
                return (int)rs.getLong(1);
            }


        } catch (SQLException e) {
            e.printStackTrace();
        }
        return -1;
    }

    @Override
    public Bank getBank(User user) {
        try {
            PreparedStatement preparedStatement =
                    connection.prepareStatement("select * from banks where admins like ?");
            preparedStatement.setString(1, "%" + user.getId() + "%");
            ResultSet resultSet = preparedStatement.executeQuery();
            if (resultSet.next()) {
                Bank bank = new Bank();
                bank.setId(resultSet.getInt("id"));
                bank.setName(resultSet.getString("name"));
                String[] accounts = resultSet.getString("accounts").split(",");
                String[] admins = resultSet.getString("admins").split(",");

                for(String item : accounts){
                    bank.setAccounts(Integer.valueOf(item));
                }
                for(String item : admins){
                    bank.setAdmins(Integer.valueOf(item));
                }

                return bank;
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return null;
    }


    @Override
    public List<Account> getAccounts(List<Card> cards) {
        try {
            List<Integer> accIds = new ArrayList<>();
            for(Card item : cards){
                accIds.add(item.getAccountId());
            }
            String sql = "select * from accounts where ";
            for(Integer id :  accIds){
                sql += "id = " + id + " or ";
            }
            sql = sql.substring(0, sql.length() - 3);
            PreparedStatement preparedStatement =
                    connection.prepareStatement(sql);
            ResultSet resultSet = preparedStatement.executeQuery();
            List<Account> accounts = new ArrayList<>();
            while (resultSet.next()) {
                Account account = new Account();
                account.setId(resultSet.getInt("Id"));
                account.setMoneyAmount(resultSet.getInt("moneyAmount"));
                account.setIsBlocked(resultSet.getBoolean("isBlocked"));
                accounts.add(account);
            }
            return accounts;
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return null;
    }


}
