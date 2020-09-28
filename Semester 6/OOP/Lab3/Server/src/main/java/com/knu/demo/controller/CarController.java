package com.knu.demo.controller;

import com.knu.demo.dto.CarDTO;
import com.knu.demo.service.CarControllerService;
import lombok.RequiredArgsConstructor;
import org.springframework.web.bind.annotation.*;

import javax.validation.Valid;
import java.util.List;

@RestController
@CrossOrigin
@RequiredArgsConstructor
public class CarController {
    private final CarControllerService carService;

    @GetMapping(value = "/car/booking/{bookingId}")
    public List<CarDTO> getCarsByBooking(@Valid @PathVariable Long bookingId) {
        return carService.findCarByBookingId(bookingId);
    }
}
