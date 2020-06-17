package com.knu.demo.converter;

import com.knu.demo.dto.CarDTO;
import com.knu.demo.entity.Car;
import com.knu.demo.entity.CarClass;
import org.springframework.stereotype.Component;

import javax.persistence.Converter;
import java.util.List;
import java.util.stream.Collectors;

@Component
public class CarConverter {
    public CarDTO convertToDTO(Car car) {
        CarDTO carDTO = new CarDTO();
        carDTO.setId(car.getId());
        carDTO.setCarClass(car.getCarClass().toString());
        carDTO.setSeatsNumber(car.getSeatsNumber());
        carDTO.setLastInspection(car.getLastInspection());
        carDTO.setServiceable(car.getServiceable());

        return carDTO;
    }

    public Car convertToEntity(CarDTO carDTO) {
        Car car = new Car();
        car.setId(carDTO.getId());
        car.setCarClass(CarClass.valueOf(carDTO.getCarClass()));
        car.setSeatsNumber(carDTO.getSeatsNumber());
        car.setLastInspection(carDTO.getLastInspection());
        car.setServiceable(carDTO.getServiceable());

        return car;
    }

    public List<CarDTO> convertToListDTO(List<Car> cars) {
        return cars.stream().map(this::convertToDTO).collect(Collectors.toList());
    }
}
