package com.knu.demo.service;

import com.knu.demo.entity.CarClass;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Service;

import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

@Service
@RequiredArgsConstructor
public class CarClassService {
    public List<String> getCarClasses() {
        return Arrays.stream(CarClass.values()).map(Enum::toString).collect(Collectors.toList());
    }
}
