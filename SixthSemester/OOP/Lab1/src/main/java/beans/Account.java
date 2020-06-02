package beans;

public class Account {
    private int id;
    private int moneyAmount;
    private boolean isBlocked;
    public void setId(int id){this.id = id;}
    public int getId(){return id;}
    public void setMoneyAmount(int moneyAmount){this.moneyAmount = moneyAmount;}
    public int getMoneyAmount(){return moneyAmount;}
    public void setIsBlocked(boolean isBlocked){this.isBlocked = isBlocked;}
    public boolean getIsBlocked(){return isBlocked;}
}
