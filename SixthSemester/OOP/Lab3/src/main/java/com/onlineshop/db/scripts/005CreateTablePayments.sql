create table Payments (
    id int auto_increment,
    money int,
	clientId int,
	cardNumber int, 
	info varchar(1000),
	PRIMARY KEY (id)
);