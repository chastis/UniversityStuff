SELECT d.dep_id,
p.per_id,
count(*)      as per_cnt,
max(m.actual) as has_actual_template
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

INSERT
into my_temporary_table (id, value_1, value_2, value_3, value_4)
values (1991, 1, 2, 3, 4),
(1992, 5, 6, 
7, 8
),
(1993, 9, 10, 11, 12);