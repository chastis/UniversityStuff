package com.knu.demo.service.data;

import com.knu.demo.entity.Booking;
import com.knu.demo.entity.Car;
import com.knu.demo.repository.CarRepository;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.Optional;

@Service
@RequiredArgsConstructor
public class CarService {
    private final CarRepository carRepository;

    public List<Car> findCarByBooking(Booking booking) {
        return carRepository.findCarsByCarClassGreaterThanEqualAndSeatsNumberGreaterThanEqualAndServiceable(booking.getMinClass(), booking.getMinSeats(), true);
    }

    public Optional<Car> findCarById(Long carId){
        return carRepository.findCarById(carId);
    }

    public Car save(Car car) {
        return carRepository.save(car);
    }

}
