create table Bank_acc (
    bank_id int NOT NULL,
    acc_id int NOT NULL,
    CONSTRAINT FK_BANKS FOREIGN KEY (bank_id) REFERENCES BANKS (id),
    CONSTRAINT FK_ACCOUNTS FOREIGN KEY (acc_id) REFERENCES ACCOUNTS (id)
);