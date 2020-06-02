package beans;

import java.util.ArrayList;
import java.util.List;

public class Bank {
    private int id;
    private String name;
    private List<Integer> accounts = new ArrayList<>();
    private List<Integer> admins = new ArrayList<>();
    public void setId(int id){this.id = id;}
    public int getId(){return id;}
    public void setName(String name){this.name = name;}
    public String getName(){return name;}
    public void setAccounts(Integer accounts){this.accounts.add(accounts);}
    public List<Integer> getAccounts(){return accounts;}
    public void setAdmins(Integer admins){this.admins.add(admins);}
    public List<Integer> getAdmins(){return admins;}


}
