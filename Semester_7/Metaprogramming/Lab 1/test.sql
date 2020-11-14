CREATE TABLE My_Table
(
	    Id   int         not null,
	Name varchar(60) not null,
    Note varchar(2000.)
    values 
    (
        1991, 
        1, 
        2, 
        3, 
        4
    )
);

create table a;

-- comment
	
SELECT T.table_name as "The Table Name",
        count(I.id)  as "Number of Fields"
FROM sys."tables" T,
     sys."indices" I
/* 
      another comment 
*/
WHERE T.table_name = I.table_name
GROUP BY T.table_name
HAVING count(I.id) >= 0
ORDER BY 2 desc;

CREATE TABLE Position
(
     Pos  integer     not null primary key,
     Name varchar(80) not null unique,
     Note varchar(1000)
);


CREATE TABLE Detail
(
     Id   integer     not null,
     Name varchar(26) not null,
     Note varchar(1000),
     Pos  decimal(4)  not null,
     constraint Detail_pk
          primary key (Id),
     constraint Detail_fk
          foreign key (Pos)
               references Position
               on delete cascade ( a,
               d,
               b)
);