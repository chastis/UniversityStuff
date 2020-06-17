package com.knu.demo.service;

import com.knu.demo.converter.BookingConverter;
import com.knu.demo.dto.BookingDTO;
import com.knu.demo.entity.Booking;
import com.knu.demo.entity.User;
import com.knu.demo.exception.UserNotFound;
import com.knu.demo.service.data.BookingService;
import com.knu.demo.service.data.UserService;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.mockito.InjectMocks;
import org.mockito.Mock;
import org.mockito.junit.MockitoJUnitRunner;
import org.springframework.context.ApplicationEventPublisher;

import java.util.Optional;

import static org.junit.Assert.*;
import static org.mockito.ArgumentMatchers.any;
import static org.mockito.Mockito.*;

@RunWith(MockitoJUnitRunner.class)
public class BookingControllerServiceTest {
    @InjectMocks
    private BookingControllerService bookingControllerService;

    @Mock
    private BookingConverter bookingConverter;
    @Mock
    private BookingService bookingService;
    @Mock
    private UserService userService;
    @Mock
    private ApplicationEventPublisher applicationEventPublisher;
    @Mock
    private User user;
    @Mock
    private Booking currentBooking;
    @Mock
    private BookingDTO bookingDTO;

    @Test
    public void saveBookingTestCorrect(){
        Optional<User> userOptional=Optional.of(user);

        when(userService.findUserByEmail(any())).thenReturn(userOptional);
        when(bookingConverter.convertToEntity(any())).thenReturn(currentBooking);
        when(bookingService.save(any())).thenReturn(currentBooking);
        when(bookingConverter.convertToDTO(any())).thenReturn(bookingDTO);

        bookingControllerService.save(bookingDTO);

        verify(currentBooking).setUser(user);
        verify(applicationEventPublisher).publishEvent(bookingDTO);

    }

    @Test
    public void saveBookingTestException(){

        when(userService.findUserByEmail(any())).thenReturn(Optional.empty());
        when(bookingConverter.convertToEntity(any())).thenReturn(currentBooking);

        assertThrows(UserNotFound.class, ()->bookingControllerService.save(bookingDTO)) ;

        verify(currentBooking, never()).setUser(user);
        verify(applicationEventPublisher, never()).publishEvent(bookingDTO);

    }

}