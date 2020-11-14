CREATE TABLE My_Table
(
	    Id   INT         NOT NULL,
	Name VARCHAR(60) NOT NULL,
	Note VARCHAR(2000.)
	Values 
	(
		1991, 
		1, 
		2, 
		3, 
		4
	)
);

CREATE TABLE A;

-- comment
	
SELECT T.Table_Name AS "THE TABLE NAME",
		Count(I.Id)  AS "NUMBER OF FIELDS"
FROM Sys."Tables" T,
	 Sys."Indices" I
/* 
	  another comment 
*/
where t.table_name = i.table_name
group by t.table_name
having count(i.id) >= 0
order by 2 desc;

create table position
(
	 pos  integer     not null primary key,
	 name varchar(80) not null unique,
	 note varchar(1000)
);


create table detail
(
	 id   integer     not null,
	 name varchar(26) not null,
	 note varchar(1000),
	 pos  decimal(4)  not null,
	 constraint detail_pk
		  primary key (id),
	 constraint detail_fk
		  foreign key (pos)
			   references position
			   on delete cascade ( a,
			   d,
			   b)
);