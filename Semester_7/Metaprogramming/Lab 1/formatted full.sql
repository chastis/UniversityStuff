CREATE
    TABLE "Author"( "Id"     INT           NOT NULL
                    PRIMARY KEY, 
                    "F_Name" VARCHAR( 40 ) NOT NULL, 
                    "L_Name" VARCHAR( 40 ) NOT NULL, 
                    CONSTRAINT "Author_Name_Is_Unique" UNIQUE( "F_Name", "L_Name" ) );

CREATE
    TABLE "Book"( "Id"    INT            NOT NULL
                  PRIMARY KEY, 
                  "Title" VARCHAR( 160 ) NOT NULL, 
                  "Yr"    DECIMAL( 4 ) CHECK( "Yr" "Between" -1000 AND 2099 ) );

CREATE
    TABLE "Book_Author"( "Book_Id" INT NOT NULL, 
                         "Auth_Id" INT NOT NULL, 
                         CONSTRAINT "Book_Author_Pk" 
                             PRIMARY KEY( "Book_Id", "Auth_Id" ), 
                         CONSTRAINT "Book_Author_Book_Fk" 
                             FOREIGN KEY( "Book_Id" ) REFERENCES "Book"( "Id" ) 
                                 ON DELETE CASCADE, 
                         CONSTRAINT "Book_Author_Auth_Fk" 
                             FOREIGN KEY( "Auth_Id" ) REFERENCES "Author"( "Id" ) 
                                 ON DELETE CASCADE );

CREATE VIEW "Book_Info"
    AS
SELECT "B".*, 
    "Count"( DISTINCT "C"."Auth_Id" )
        AS "AUTHORS_COUNT"
FROM "Book" "B", "Book_Author" "C"
WHERE "B"."Id" = "C"."Book_Id";

CREATE
    TABLE "My_Table"( "Id"   INT           NOT NULL, 
                      "Name" VARCHAR( 60 ) NOT NULL, 
                      "Note" VARCHAR( 2000 ) );

SELECT "T"."Table_Name"
           AS "THE TABLE NAME", 
    "Count"( "I"."Id" )
        AS "NUMBER OF FIELDS"
FROM "Sys"."Tables" "T", "Sys"."Indices" "I"
WHERE "T"."Table_Name" = "I"."Table_Name"
GROUP BY "T"."Table_Name"
HAVING "Count"( "I"."Id" ) > 0 ORDER BY 2 DESC; 

INSERT INTO "My_Temporary_Table"( "Id", "Value_1", "Value_2", "Value_3", "Value_4" ) VALUES( 1991, 1, 2, 3, 4 ),( 1992, 5, 6, 7, 8 ),( 1993, 9, 10, 11, 12 ); 

INSERT INTO "My_Wide_Table" VALUES( "Get_Last_Id"( ), 
                                    "Complex_Expression_1" + "Complex_Expression_2", 
                                    "Long_Expression_1" * "Long_Expression_2" - "Long_Expression_3" ); 

UPDATE "My_Staff_Size" SET "Id"              = "Id" + 1, 
                           "Name"            = \'a name\', 
                           "Note"            = \'and a note\', 
                           "Additional_Note" = \'Processed.\', 
                           "Status"          = -1;

SELECT MAX( "Q4" )
FROM "My_Staff_Size";

SELECT "Id", "Alias", "Name", "Name_2", "Note", "Tms" 
FROM "My_Table";

SELECT "D"."Dep_Id",
    "P"."Per_Id", 
    "Count"( * )
        AS "PER_CNT",
    MAX( "M"."Actual" )
        AS "HAS_ACTUAL_TEMPLATE"
FROM "Department" "D"
    JOIN            "Manager" "M"
        ON "D"."Dep_Id"      = "M"."Dep_Id" 
    LEFT JOIN       "Person" "P"
        ON "M"."Per_Id"      = "P"."Per_Id", "Message" "M"
    LEFT OUTER JOIN "Mark" "Mk"
        ON "M"."Id"          = "Mk"."Msg_Id" 
    LEFT JOIN       "Template" "Tp"
        ON "M"."Template_Id" = "Tp"."Id"
WHERE "D"."Dep_Id" = "M"."Dep_1"
GROUP BY "D"."Dep_Id", "P"."Per_Id"
HAVING "Count"( * ) >= 2 ORDER BY "PER_CNT" DESC;

SELECT "A".*
FROM "Small_Table_1" "A"
    NATURAL JOIN    "Small_Table_2" "B" 
    NATURAL JOIN    "Small_Table_3" "C" 
    JOIN            "Medium_Table_4" "D" USING( "Id" ) 
    LEFT OUTER JOIN "Medium_Table_5" "E"
        ON "D"."X" = "E"."X" 
    LEFT OUTER JOIN "Medium_Table_6" "F"
        ON "E"."Y" = "F"."Y" 
    INNER JOIN      "Medium_Table_7" "G"
        ON "F"."Z" = "G"."Z";

SELECT "A".*,
    "D".*, "H".*
FROM "Small_Table_1" "A"
    CROSS JOIN      "Small_Table_2" "B"
    CROSS JOIN      "Small_Table_3" "C", "Medium_Table_4" "D"
    LEFT OUTER JOIN "Medium_Table_5" "E"
        ON "D"."Id"     = "E"."Id" 
    LEFT OUTER JOIN "Medium_Table_6" "F"
        ON "E"."Id"     = "F"."Id" 
    INNER JOIN      "Medium_Table_7" "G"
        ON "D"."Ref_Id" = "G"."Ref_Id", "Big_Table_8" "H"
    CROSS JOIN( SELECT 42
                FROM "Dual" ) "Z0" 
    JOIN "Another_Table"
        ON "H"."Ref_Id" = "Another_Table"."Id"; 

DELETE
FROM "Message"
WHERE "Dep_Id" NOT "In"( SELECT "Dep_Id"
                         FROM "Department"
                         WHERE "Actual" IS NOT NULL );

CREATE
    TABLE "Author"( "Id"     INT           NOT NULL
                    PRIMARY KEY, 
                    "F_Name" VARCHAR( 40 ) NOT NULL, 
                    "L_Name" VARCHAR( 40 ) NOT NULL, 
                    CONSTRAINT "Author_Name_Is_Unique" UNIQUE( "F_Name", "L_Name" ) );

CREATE
    TABLE "Book"( "Id"    INT            NOT NULL
                  PRIMARY KEY, 
                  "Title" VARCHAR( 160 ) NOT NULL, 
                  "Yr"    DECIMAL( 4 ) CHECK( "Yr" "Between" -1000 AND 2099 ) );

CREATE
    TABLE "Book_Author"( "Book_Id" INT NOT NULL, 
                         "Auth_Id" INT NOT NULL, 
                         CONSTRAINT "Book_Author_Pk" 
                             PRIMARY KEY( "Book_Id", "Auth_Id" ), 
                         CONSTRAINT "Book_Author_Book_Fk" 
                             FOREIGN KEY( "Book_Id" ) REFERENCES "Book"( "Id" ) 
                                 ON DELETE CASCADE, 
                         CONSTRAINT "Book_Author_Auth_Fk" 
                             FOREIGN KEY( "Auth_Id" ) REFERENCES "Author"( "Id" ) 
                                 ON DELETE CASCADE );

CREATE VIEW "Book_Info"
    AS
SELECT "B".*, 
    "Count"( DISTINCT "C"."Auth_Id" )
        AS "AUTHORS_COUNT"
FROM "Book" "B", "Book_Author" "C"
WHERE "B"."Id" = "C"."Book_Id";

SELECT 1;

SELECT 2;

SELECT 3;

SELECT 4;

CREATE "Domain" "Coordinate"
    AS DECIMAL( 7, 3 );

CREATE "Domain" "Height"
    AS DECIMAL( 6, 3 ) "Default" 0.0;

SELECT "Id", "Name", "Kind", 
    CASE
        WHEN "Id" < 0 THEN 'C' 
        ELSE NULL END
            AS "WAS_CONVERTED", 
    CASE
        WHEN "Kind" = 'O' THEN 'organization' 
        WHEN "Kind" = 'P' THEN 'person' 
        WHEN "Kind" = 'XX' THEN 'something gone wrong here, looks like' + 'this code should be unreachable' 
        WHEN "Kind" = '' THEN 'alias' 
        ELSE 'unknown subject' END
            AS "KIND_NAME_1", "Fun"( 1, 2, 3, 4, 5, 6, 7, 8, 9 ), "Fun"( "Fun"( 1, 2, 3 ), "Fun"( 4, 5, 6 ), "Fun"( 7, 8, 9 ) ), "Fun"( 'Long argument that occupies almost the line', 'Another long argument that is even longer that the previous one\', 'One more argument', 'The shortest one', 'And the last one' )
FROM "Faces" "F"
    LEFT OUTER JOIN "Staff" "S" 
        ON "F"."Id" = "S"."Id"
WHERE( "Kind", "Name" ) NOT "In"( SELECT "Kind", "Name"
                                FROM "Banned_Faces" ) AND NOT "Exists"( SELECT *
                                                                        FROM "Banned_Faces" "B"
                                                                        WHERE "F"."Kind" = "B"."Kind" AND "F"."Name" = "B"."Name" ) AND "Current_Date" <= "Current_Time" /******************* * my table * *******************/
create
table "my_table"( "name" varchar( 80 ) not null 
constraint "my_table_name_ak" unique, 
"note" varchar( 2000 ) )