package com.knu.demo.service;

import com.knu.demo.converter.BookingConverter;
import com.knu.demo.dto.BookingDTO;
import com.knu.demo.entity.Booking;
import com.knu.demo.entity.RideStatus;
import com.knu.demo.entity.User;
import com.knu.demo.exception.UserNotFound;
import com.knu.demo.service.data.BookingService;
import com.knu.demo.service.data.UserService;
import lombok.RequiredArgsConstructor;
import org.springframework.context.ApplicationEventPublisher;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.Optional;

@Service
@RequiredArgsConstructor
public class BookingControllerService {
    private final BookingConverter bookingConverter;
    private final BookingService bookingService;
    private final UserService userService;
    private final ApplicationEventPublisher applicationEventPublisher;

    public void save(BookingDTO bookingDTO) {
        Optional<User> user = userService.findUserByEmail(bookingDTO.getUserEmail());
        Booking currentBooking = bookingConverter.convertToEntity(bookingDTO);

        if (!user.isPresent()) {
            throw new UserNotFound("User with email " + bookingDTO.getUserEmail() + " not found");
        }

        currentBooking.setUser(user.get());

        BookingDTO savedUserDto = bookingConverter.convertToDTO(bookingService.save(currentBooking));
        applicationEventPublisher.publishEvent(savedUserDto);
    }

    public List<BookingDTO> findBookingsByUser(String userEmail) {
        return bookingConverter.convertToListDTO(bookingService.findUserBookings(userEmail));
    }

    public List<BookingDTO> findBookingsByStatus(String bookingStatus) {
        return bookingConverter.convertToListDTO(bookingService.findBookingByStatus(RideStatus.valueOf(bookingStatus)));
    }

    public BookingDTO updateBookingStatus(Long bookingId, String status) {
        return bookingConverter.convertToDTO(this.bookingService.updateBooking(bookingId, RideStatus.valueOf(status)));
    }
}
