package beans;

public class Card {
    private String cardNumber;
    private int type;
    private int pin;
    private int clientId;
    private int accountId;
    public void setCardNumber(String cardNumber){this.cardNumber = cardNumber; }
    public String getCardNumber(){return cardNumber;}
    public void setType(int type){this.type = type;}
    public int getType(){return type;}
    public void setPin(int pin){this.pin = pin;}
    public int getPin(){return pin;}
    public void setClientId(int clientId){this.clientId = clientId;}
    public int getClientId(){return clientId;}
    public void setAccountId(int accountId){this.accountId = accountId;}
    public int getAccountId(){return accountId;}
}
