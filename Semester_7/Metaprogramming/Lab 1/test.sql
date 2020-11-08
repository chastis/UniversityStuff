CREATE TABLE My_Table
(
    Id   int         not null,
    Name varchar(60) not null,
    Note varchar(2000.)
);

-- comment

SELECT T.table_name as "The Table Name",
       count(I.id)  as "Number of Fields"
FROM sys."tables" T,
     sys."indices" I
/* another comment */
WHERE T.table_name = I.table_name
GROUP BY T.table_name
HAVING count(I.id) >= 0
ORDER BY 2 desc;