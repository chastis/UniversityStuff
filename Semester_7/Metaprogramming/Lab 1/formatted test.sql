CREATE TABLE "My_Table"
(


		  "Id"   INT         NOT NULL,
		  "Name" VARCHAR(60) NOT NULL,
		  "Note" VARCHAR(2000.)
		  VALUES 
		  (
					1991, 
					1, 
					2, 
					3, 
					4
		  )
) 
;

CREATE TABLE "A";

SELECT "T"."Table_Name"
	 AS "THE TABLE NAME",
	 "Count"("I"."Id") 
		  AS "NUMBER OF FIELDS"
FROM "Sys"."Tables" "T",
	 "Sys"."Indices" "I"
WHERE "T".* = "I"."Table_Name"
GROUP BY "T"."Table_Name"
HAVING "Count"("I"."Id") >= 0
ORDER BY 2 DESC;

CREATE TABLE "Position"
(
		  "Pos"  INTEGER     NOT NULL PRIMARY KEY,
		  "Name" VARCHAR(80) NOT NULL UNIQUE,
		  "Note" VARCHAR(1000)
);



CREATE TABLE "Detail"
(
		  "Id"   INTEGER     NOT NULL,
		  "Name" VARCHAR(26) NOT NULL,
		  "Note" VARCHAR(1000),
		  "Pos"  DECIMAL(4)  NOT NULL,
		  CONSTRAINT "Detail_Pk"
			   PRIMARY KEY ("Id"),
		  CONSTRAINT "Detail_Fk"
			   FOREIGN KEY ("Pos")
					REFERENCES "Position"
					ON DELETE CASCADE ( "A",
							  "D",
							  "B")
);



CREATE TABLE "My_Table"
(
-- internal columns
		  "Id" DECIMAL(9) NOT NULL                                                                       -- entity surrogate identifier (thanks, Cap)
		  CONSTRAINT "My_Table_Id_Ch"                                                                -- positive
			   CHECK ("Id" > 0) 
		  CONSTRAINT "My_Table_Pk" PRIMARY KEY,
		  "Kind" CHAR(1) NOT NULL                                                                        -- kind of entry
			   CONSTRAINT "My_Table_Kind_Ch" CHECK ("Kind" "In" ('O','P','F')),                               -- O is bla-blah, P is …, F is …
		  "Status" DECIMAL(1) "Default" 1
			   CONSTRAINT "My_Table_Status_Ch" CHECK ( "Status" "Between" -1 "And" 3 ), -- 1..3 actual, 0 in progress, -1 archived

               -- natural data
		  "Name" VARCHAR(80) NOT NULL
			   CONSTRAINT "My_Table_Name_Ak" UNIQUE,
		  "Note" VARCHAR(2000))
