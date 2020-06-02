package beans;

public class Payment {
    private int id;
    private int money;
    private int clientId;
    private int cardNumber;
    private String info;

    public void setId(int id){this.id = id;}
    public int getId(){return id;}
    public void setMoney(int money){this.money = money;}
    public int getMoney(){return money;}
    public void setClient(int clientId){this.clientId = clientId;}
    public int getClient(){return clientId;}
    public void setCard(int cardNumber){this.cardNumber = cardNumber;}
    public int getCard(){return cardNumber;}
    public void setInfo(String info){this.info = info;}
    public String getInfo(){return info;}
}
