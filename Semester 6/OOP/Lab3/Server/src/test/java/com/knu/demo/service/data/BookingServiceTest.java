package com.knu.demo.service.data;

import com.knu.demo.entity.Booking;
import com.knu.demo.entity.RideStatus;
import com.knu.demo.exception.BookingNotFoundException;
import com.knu.demo.repository.BookingRepository;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.mockito.InjectMocks;
import org.mockito.Mock;
import org.mockito.junit.MockitoJUnitRunner;

import java.util.Optional;

import static org.junit.Assert.*;
import static org.mockito.ArgumentMatchers.any;
import static org.mockito.Mockito.*;

@RunWith(MockitoJUnitRunner.class)
public class BookingServiceTest {

    @InjectMocks
    private BookingService  bookingService;

    @Mock
    private BookingRepository bookingRepository;
    @Mock
    private Booking booking;

    private final RideStatus rideStatus=RideStatus.WAITING;

    @Test
    public void updateBookingTestCorrectly(){
        when(bookingRepository.findById(any())).thenReturn(Optional.of(booking));

        assertEquals(bookingService.updateBooking(0L, rideStatus), booking);

        verify(booking).setRideStatus(rideStatus);
    }

    @Test
    public void updateBookingTestException(){
        when(bookingRepository.findById(any())).thenReturn(Optional.empty());

        assertThrows(BookingNotFoundException.class, ()->bookingService.updateBooking(0L, rideStatus));

        verify(booking, never()).setRideStatus(rideStatus);
    }

}