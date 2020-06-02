package beans;

import java.util.ArrayList;
import java.util.List;

public class User {
    private int id;
    private String name;
    private String login;
    private String password;
    private boolean isSuperUser;
    private List<Card> cards = new ArrayList<>();
    public void setId(int id){this.id = id;}
    public int getId(){return id;}
    public void setName(String name){this.name = name;}
    public String getName(){return name;}
    public void addCart(Card card){cards.add(card);}
    public List<Card> getCards(){return cards;}
    public void setLogin(String login){this.login = login;}
    public String getLogin(){return login;}
    public void setPassword(String password){this.password = password;}
    public String getPassword(){return password;}
    public void setIsSuperUser(boolean isSuperUser){this.isSuperUser = isSuperUser;}
    public boolean getIsSuperUser(){return isSuperUser;}
}
