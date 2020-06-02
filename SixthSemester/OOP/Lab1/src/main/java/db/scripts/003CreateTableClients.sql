create table Clients (
    id int auto_increment,
    name varchar(255),
	login VARCHAR(255),
	password VARCHAR(255),
	isSuperUser tinyint,
	PRIMARY KEY (id)
);