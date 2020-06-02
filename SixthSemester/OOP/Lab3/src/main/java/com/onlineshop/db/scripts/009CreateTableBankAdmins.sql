create table Bank_admins(
    bank_id int NOT NULL,
    user_id bigint NOT NULL,
	CONSTRAINT FK_USESRS_ADMINS FOREIGN KEY (user_id) REFERENCES USERS (id),
    CONSTRAINT FK_BANKS_ADMINS FOREIGN KEY (bank_id) REFERENCES BANKS (id)
);