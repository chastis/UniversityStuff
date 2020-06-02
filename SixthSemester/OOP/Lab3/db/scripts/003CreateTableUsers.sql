create table USERS (
    id bigint auto_increment,
    name varchar(255),
	username VARCHAR(255),
	password VARCHAR(255),
	enabled boolean,
	PRIMARY KEY (id)
);
