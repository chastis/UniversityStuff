package com.knu.demo.entity;

import lombok.Data;
import lombok.NoArgsConstructor;

import javax.persistence.*;

@Data
@Entity
@Table(name = "rides", schema = "public")
@NoArgsConstructor
public class Ride {
    @Id
    @GeneratedValue(generator = "rides_id_seq", strategy = GenerationType.SEQUENCE)
    @SequenceGenerator(name = "rides_id_seq", sequenceName = "rides_id_seq", allocationSize = 1)
    @Column(name = "id", updatable = false)
    private Long id;

    @Column(name = "price")
    private Integer price;

    @OneToOne(targetEntity = Car.class)
    private Car car;

    @OneToOne(fetch = FetchType.LAZY)
    private Booking booking;
}
