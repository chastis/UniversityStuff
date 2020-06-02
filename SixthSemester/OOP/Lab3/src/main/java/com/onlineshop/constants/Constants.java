package com.onlineshop.constants;

public class Constants {
    public static final String LOGIN_ACCOUNT = "2";
    public static final String SHOW_CLIENTS = "109Admin";
    public static final String CHANGE_CLIENT_STATUS = "12";
    public static final String ID_ADMIN = "7";
    public static final String ID_CLIENT = "100";
    public static final String ERROR = "0";
    public static final String SHOW_CLIENT_BY_ID = "8";
    public static final String CLIENT_REQUEST =  "SELECT * FROM Client WHERE idClient %s AND Login %s AND Password %s AND isAdmin %s";
    public static final String GOODS_REQUEST = "SELECT * FROM Goods WHERE idGoods ";
    public static final String BILLING_REQUEST =  "SELECT * FROM Billing WHERE idBilling %s ";
    public static final String UPDATE_BILL_STATUS =  "UPDATE Billing SET Status = '%s' WHERE idBilling = '%s'";
    public static final String UPDATE_BILL_BALANCE =  "UPDATE Billing SET Balance = '%s' WHERE idBilling = '%s'";
    public static final String UPDATE_BILL_IDGOODS =   "UPDATE Billing SET idGoods = '%s' WHERE idBilling = '%s'";
    public static final String ADMIN = "Admin";
    public static final String CLIENT = "Client";
    public static final int SELECT_ALL_INT = -1;
    public static final String SELECT_ALL_STR = "";
    public static final int IS_CLIENT = 0;
    public static final String EMPTY_FIELD = "";
}
