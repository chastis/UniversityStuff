package com.knu.demo.controller;

import com.knu.demo.service.CarClassService;
import lombok.RequiredArgsConstructor;
import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.List;

@RestController
@CrossOrigin
@RequiredArgsConstructor
public class CarClassController {
    private final CarClassService carClassService;

    @GetMapping(value = "/carClass")
    public List<String> getCarClasses() {
        return carClassService.getCarClasses();
    }
}
