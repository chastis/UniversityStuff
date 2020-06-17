package com.knu.demo.entity;

import lombok.Data;
import lombok.NoArgsConstructor;
import org.hibernate.annotations.Type;
import org.hibernate.annotations.TypeDef;

import javax.persistence.*;

@Data
@Entity
@Table(name = "bookings", schema = "public")
@TypeDef(
        name = "car_class",
        typeClass = PostgreSQLEnumType.class
)
@TypeDef(
        name = "ride_status",
        typeClass = PostgreSQLEnumType.class
)
@NoArgsConstructor
public class Booking {
    @Id
    @GeneratedValue(generator = "bookings_id_seq", strategy = GenerationType.SEQUENCE)
    @SequenceGenerator(name = "bookings_id_seq", sequenceName = "bookings_id_seq", allocationSize = 1)
    @Column(name = "id", updatable = false)
    private Long id;

    @Enumerated(EnumType.STRING)
    @Column(columnDefinition = "min_class")
    @Type(type = "car_class")
    private CarClass minClass;

    @Column(name = "depart")
    private String depart;

    @Column(name = "destination")
    private String destination;

    @Column(name = "min_seats")
    private Integer minSeats;

    @Enumerated(EnumType.STRING)
    @Column(columnDefinition = "status", name = "status")
    @Type(type = "ride_status")
    @OrderColumn
    private RideStatus rideStatus;

    @ManyToOne
    private User user;
}


