SELECT "D"."Dep_Id",
    "P"."Per_Id",
    "Count"( * )     
        AS "PER_CNT",
    MAX( "M"."Actual" )
        AS "HAS_ACTUAL_TEMPLATE"
FROM "Department" "D"
    JOIN           "Manager" "M"
        ON "D"."Dep_Id" = "M"."Dep_Id"
    LEFT JOIN      "Person" "P"
        ON "M"."Per_Id" = "P"."Per_Id",
        "Message" "M"
    LEFT OUTER JOIN "Mark" "Mk"
        ON "M"."Id" = "Mk"."Msg_Id"
    LEFT JOIN      "Template" "Tp"
        ON "M"."Template_Id" = "Tp"."Id"
WHERE "D"."Dep_Id" = "M"."Dep_1"
GROUP BY "D"."Dep_Id", "P"."Per_Id"
HAVING "Count"( * ) >= 2
ORDER BY "PER_CNT" DESC;

INSERT
    INTO "My_Temporary_Table"( "Id", "Value_1", "Value_2", "Value_3", "Value_4" )
    VALUES( 1991, 1, 2, 3, 4 ),
    ( 1992, 5, 6, 
      7, 8
      ),
    ( 1993, 9, 10, 11, 12 );