package com.knu.demo.service.data;

import com.knu.demo.entity.Booking;
import com.knu.demo.entity.Ride;
import com.knu.demo.entity.RideStatus;
import com.knu.demo.repository.RideRepository;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.stream.Collectors;

@Service
@RequiredArgsConstructor
public class RideService {
    private final RideRepository rideRepository;

    public Ride save(Ride ride) {
        return rideRepository.save(ride);
    }

    public List<Booking> getRideBookingsByCar(Long carId) {
        return rideRepository.findRidesByCarIdAndBookingRideStatus(carId, RideStatus.WAITING).stream().map(Ride::getBooking).collect(Collectors.toList());
    }
}
