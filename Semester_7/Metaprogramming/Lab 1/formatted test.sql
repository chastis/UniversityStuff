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
) ;

CREATE TABLE "A";

-- comment

/* 



    another comment 
*/


SELECT "T"."Table_Name" AS "THE TABLE NAME",
	 "Count"("I"."Id")  AS "NUMBER OF FIELDS"
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