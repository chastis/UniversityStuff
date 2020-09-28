package com.knu.demo.service;

import com.knu.demo.converter.CarConverter;
import com.knu.demo.converter.UserConverter;
import com.knu.demo.dto.UserDTO;
import com.knu.demo.entity.Car;
import com.knu.demo.service.data.CarService;
import com.knu.demo.service.data.UserService;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Service;

@Service
@RequiredArgsConstructor
public class UserControllerService {
    private final UserService userService;
    private final CarService carService;

    private final UserConverter userConverter;
    private final CarConverter carConverter;

    public UserDTO update(UserDTO userDTO) {
        Car car = carService.save(carConverter.convertToEntity(userDTO.getCar()));
        userDTO.setCar(carConverter.convertToDTO(car));
        return userConverter.convertToDto(userService.update(userConverter.convertToEntity(userDTO)));
    }
}
