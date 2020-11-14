CREATE TABLE My_Table
(
   Id   int         not null,
   Name varchar(60) not null,
   Note varchar(2000)
);



SELECT T.table_name as "The Table Name", count(I.id) as "Number of Fields"
FROM sys."tables" T,
     sys."indices" I
WHERE T.table_name = I.table_name
GROUP BY T.table_name
HAVING count(I.id) > 0
ORDER BY 2 desc;

INSERT
into my_temporary_table (id, value_1, value_2, value_3, value_4)
values (1991, 1, 2, 3, 4),
       (1992, 5, 6, 7, 8),
       (1993, 9, 10, 11, 12);

INSERT
into my_wide_table
values (get_last_id(),
        complex_expression_1 + complex_expression_2,
        long_expression_1 * long_expression_2 - long_expression_3);


UPDATE my_staff_size
set id              = id + 1,
    name            = 'a name',
    note            = 'and a note',
    additional_note = 'Processed.',
    status          = -1;


SELECT max(q4)
from my_staff_size;


SELECT id,     -- an abstract identifier starting from 1
       alias,  -- optional alias, nullable
       name,   -- the name
       name_2, -- additional name if exists
       note,   -- multi-line text
       tms     -- timestamp (the long value from java's Date)
from my_table;


SELECT d.dep_id, p.per_id, count(*) as per_cnt, max(m.actual) as has_actual_template
from department d
        join manager m on d.dep_id = m.dep_id
        left join person p on m.per_id = p.per_id,
     message m
        left outer join mark mk on m.id = mk.msg_id
        left join template tp on m.template_id = tp.id
where d.dep_id = m.dep_1
group by d.dep_id, p.per_id
having count(*) >= 2
order by per_cnt desc;


SELECT A.*
from Small_Table_1 A
        natural join Small_Table_2 B
        natural join Small_Table_3 C
        join Medium_Table_4 D using (Id)
        left outer join Medium_Table_5 E on D.X = E.X
        left outer join Medium_Table_6 F on E.Y = F.Y
        inner join Medium_Table_7 G on F.Z = G.Z;


SELECT A.*, D.*, H.*
from Small_Table_1 A
        cross join Small_Table_2 B
        cross join Small_Table_3 C,
     Medium_Table_4 D
        left outer join Medium_Table_5 E on D.Id = E.Id
        left outer join Medium_Table_6 F on E.Id = F.Id
        inner join Medium_Table_7 G on D.Ref_Id = G.Ref_Id,
     Big_Table_8 H
        cross join (select 42 from dual) Z0
        join Another_Table on H.Ref_Id = Another_Table.Id;


DELETE
from message
where dep_id not in (select dep_id from department where actual is not null);

create table Author
(
   Id     int         not null primary key,
   F_Name varchar(40) not null,
   L_Name varchar(40) not null,
   constraint Author_Name_is_Unique unique (F_Name, L_Name)
);


create table Book
(
   Id    int          not null primary key,
   Title varchar(160) not null,
   Yr    decimal(4) check (Yr between -1000 and 2099)
);


create table Book_Author
(
   Book_Id int not null,
   Auth_Id int not null,
   constraint Book_Author_pk primary key (Book_Id, Auth_Id),
   constraint Book_Author_Book_fk foreign key (Book_Id) references Book (Id) on delete cascade,
   constraint Book_Author_Auth_fk foreign key (Auth_Id) references Author (Id) on delete cascade
);


create view Book_Info as
select B.*, count(distinct C.Auth_Id) as Authors_Count
from Book B,
     Book_Author C
where B.Id = C.Book_Id;

-- several statements on the line
select 1;
select 2;
select 3;
select 4;


-- a couple of domains
create
domain Coordinate as decimal(7,3);
create
domain Height as decimal(6,3) default 0.0;

select Id,
       Name,
       Kind,
       case when Id < 0 then 'C' else null end as Was_Converted,
       case
          when Kind = 'O' then 'organization'
          when Kind = 'P' then 'person'
          when Kind = 'XX' then 'something gone wrong here, looks like' + 'this code should be unreachable'
          when Kind = '' then 'alias'
          else 'unknown subject' end           as Kind_Name_1,
       fun(1, 2, 3, 4, 5, 6, 7, 8, 9),
       fun(fun(1, 2, 3), fun(4, 5, 6), fun(7, 8, 9)),
       fun('Long argument that occupies almost the line',
           'Another long argument that is even longer that the previous one', 'One more argument', 'The shortest one',
           'And the last one')
from Faces F
        left outer join Staff S on F.Id = S.Id
where (Kind, Name) not in (select Kind, Name from Banned_Faces)
  and not exists(select * from Banned_Faces B where F.Kind = B.Kind and F.Name = B.Name)
  and current_date <= current_time

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
   constraint Detail_pk primary key (Id),
   constraint Detail_fk foreign key (Pos) references Position on delete cascade
);
 	
/*******************
 *  My Table       *
 *******************/
create table My_Table
(
-- internal columns
   Id     decimal(9)  not null                                       -- entity surrogate identifier (thanks, Cap)
      constraint My_Table_Id_ch                                      -- positive
         check (Id > 0)
      constraint My_Table_pk primary key,
   Kind   char(1)     not null                                       -- kind of entry
      constraint My_Table_Kind_ch check (Kind in ('O', 'P', 'F')),   -- O is bla-blah, P is …, F is …
   Status decimal(1) default 1
      constraint My_Table_Status_ch check (Status between -1 and 3), -- 1..3 actual, 0 in progress, -1 archived

-- natural data
   Name   varchar(80) not null
      constraint My_Table_Name_ak unique,
   Note   varchar(2000)
)
