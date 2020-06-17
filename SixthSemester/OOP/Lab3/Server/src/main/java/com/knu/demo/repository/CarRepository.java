package com.knu.demo.repository;

import com.knu.demo.entity.Car;
import com.knu.demo.entity.CarClass;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.List;
import java.util.Optional;

public interface CarRepository extends JpaRepository<Car, Long> {
    List<Car> findCarsByCarClassGreaterThanEqualAndSeatsNumberGreaterThanEqualAndServiceable(CarClass carClass, Integer seats, Boolean serviceable);

    Optional<Car> findCarById(Long id);
}
