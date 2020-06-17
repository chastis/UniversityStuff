package com.knu.demo.controller;

import com.knu.demo.service.RideStatusService;
import lombok.RequiredArgsConstructor;
import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.List;

@RestController
@CrossOrigin
@RequiredArgsConstructor
public class RideStatusController {
    private final RideStatusService rideStatusService;

    @GetMapping(value = "/rideStatus")
    public List<String> getRideStatus() {
        return rideStatusService.getRideStatus();
    }
}
