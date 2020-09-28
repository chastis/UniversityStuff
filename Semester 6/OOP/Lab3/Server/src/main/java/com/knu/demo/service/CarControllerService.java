package com.knu.demo.service;

import com.knu.demo.converter.CarConverter;
import com.knu.demo.dto.CarDTO;
import com.knu.demo.entity.Booking;
import com.knu.demo.exception.BookingNotFoundException;
import com.knu.demo.service.data.BookingService;
import com.knu.demo.service.data.CarService;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.Optional;

@Service
@RequiredArgsConstructor
public class CarControllerService {
    private final CarService carService;
    private final BookingService bookingService;

    private final CarConverter carConverter;

    public List<CarDTO> findCarByBookingId(Long bookingId) {
        Optional<Booking> booking = bookingService.findBookingById(bookingId);
        if (!booking.isPresent()) {
            throw new BookingNotFoundException("Booking with id " + bookingId + " not found");
        }
        return carConverter.convertToListDTO(carService.findCarByBooking(booking.get()));
    }

}
