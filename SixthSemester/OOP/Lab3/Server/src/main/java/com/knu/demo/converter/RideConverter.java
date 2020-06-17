package com.knu.demo.converter;

import com.knu.demo.dto.RideDTO;
import com.knu.demo.entity.Booking;
import com.knu.demo.entity.Car;
import com.knu.demo.entity.Ride;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Component;

import javax.persistence.Converter;
import java.util.List;
import java.util.stream.Collectors;

@Component
@RequiredArgsConstructor
public class RideConverter {
    public RideDTO convertToDTO(Ride ride) {
        RideDTO rideDTO = new RideDTO();
        rideDTO.setId(ride.getId());
        rideDTO.setBookingId(ride.getBooking().getId());
        rideDTO.setCarId(ride.getCar().getId());
        rideDTO.setPrice(ride.getPrice());

        return rideDTO;
    }

    public Ride convertToEntity(RideDTO rideDTO, Booking booking, Car car) {
        Ride ride = new Ride();
        ride.setId(rideDTO.getId());
        ride.setBooking(booking);
        ride.setCar(car);
        ride.setPrice(rideDTO.getPrice());

        return ride;
    }

    public List<RideDTO> convertToListDTO(List<Ride> rides) {
        return rides.stream().map(this::convertToDTO).collect(Collectors.toList());
    }
}

//@NotNull(message = "Price required")
//    private int price;
//
//    private int carId;
//
//    private int bookingId;


//private Long id;
//
//    @Column(name = "price")
//    private int price;
//
//    @OneToOne
//    private Car car;
//
//    @OneToOne
//    private Booking booking;
