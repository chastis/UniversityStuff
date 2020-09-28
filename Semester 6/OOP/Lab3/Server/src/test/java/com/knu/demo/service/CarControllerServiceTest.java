package com.knu.demo.service;

import com.knu.demo.converter.CarConverter;
import com.knu.demo.dto.CarDTO;
import com.knu.demo.entity.Booking;
import com.knu.demo.entity.User;
import com.knu.demo.exception.BookingNotFoundException;
import com.knu.demo.exception.UserNotFound;
import com.knu.demo.service.data.BookingService;
import com.knu.demo.service.data.CarService;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.mockito.InjectMocks;
import org.mockito.Mock;
import org.mockito.junit.MockitoJUnitRunner;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

import static org.junit.Assert.*;
import static org.mockito.ArgumentMatchers.any;
import static org.mockito.Mockito.*;

@RunWith(MockitoJUnitRunner.class)
public class CarControllerServiceTest {

    @InjectMocks
    private CarControllerService carControllerService;

    @Mock
    private CarService carService;
    @Mock
    private BookingService bookingService;
    @Mock
    private CarConverter carConverter;
    @Mock
    private Booking booking;

    @Test
    public void saveBookingTestCorrect(){
        Optional<Booking> bookingOptional = Optional.of(booking);
        List<CarDTO> carDTOS = new ArrayList<>();

        when(bookingService.findBookingById(any())).thenReturn(bookingOptional);
        when(carConverter.convertToListDTO(any())).thenReturn(carDTOS);

        assertEquals(carControllerService.findCarByBookingId(0L),carDTOS);
    }

    @Test
    public void saveBookingTestException(){
        when(bookingService.findBookingById(any())).thenReturn(Optional.empty());

        assertThrows(BookingNotFoundException.class, ()->carControllerService.findCarByBookingId(0L));

        verify(carService, never()).findCarByBooking(any());
    }


}