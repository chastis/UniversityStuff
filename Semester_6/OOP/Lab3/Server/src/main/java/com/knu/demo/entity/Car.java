package com.knu.demo.entity;

import lombok.Data;
import lombok.NoArgsConstructor;
import org.hibernate.annotations.Type;
import org.hibernate.annotations.TypeDef;

import javax.persistence.*;
import java.sql.Date;

@Data
@Entity
@Table(name = "cars", schema = "public")
@TypeDef(
        name = "car_class",
        typeClass = PostgreSQLEnumType.class
)
@NoArgsConstructor
public class Car {
    @Id
    @GeneratedValue(generator = "cars_id_seq", strategy = GenerationType.SEQUENCE)
    @SequenceGenerator(name = "cars_id_seq", sequenceName = "cars_id_seq", allocationSize = 1)
    @Column(name = "id", updatable = false)
    private Long id;

    @Column(name = "seats_number")
    private Integer seatsNumber;

    @Enumerated(EnumType.STRING)
    @Column(name = "class")
    @Type(type = "car_class")
    private CarClass carClass;

    @Column(name = "last_inspection")
    private Date lastInspection;

    @Column(name = "serviceable")
    private Boolean serviceable;
}
