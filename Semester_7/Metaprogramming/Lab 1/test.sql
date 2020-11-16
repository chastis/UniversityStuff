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
) ;

create table a;

-- comment

/* 
         
	

    another comment 
*/

       
SELECT T.table_name as "The Table Name",
count(I.id)  as "Number of Fields"
FROM sys."tables" T,
sys."indices" I

WHERE T.* = I.table_name
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

create table My_Table
(
-- internal columns
    Id decimal(9) not null                                                                       -- entity surrogate identifier (thanks, Cap)
        constraint My_Table_Id_ch                                                                -- positive
            check (Id > 0) 
             constraint My_Table_pk primary key,
    Kind char(1) not null                                                                        -- kind of entry
        constraint My_Table_Kind_ch check (Kind in ('O','P','F')),                               -- O is bla-blah, P is …, F is …
    Status decimal(1) default 1 constraint My_Table_Status_ch check ( Status between -1 and 3 ), -- 1..3 actual, 0 in progress, -1 archived

-- natural data
    Name varchar(80) not null constraint My_Table_Name_ak unique,
    Note varchar(2000))
