package com.knu.demo.service.data;

import com.knu.demo.entity.User;
import com.knu.demo.exception.UserNotFound;
import com.knu.demo.repository.UserRepository;
import com.knu.demo.service.RideControllerService;
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
public class UserServiceTest {

    @InjectMocks
    private UserService userService;

    @Mock
    private UserRepository userRepository;
    @Mock
    private User user;

    @Test
    public void updateTestCorrectly(){
        when(userRepository.findByEmail(any())).thenReturn(Optional.of(user));

        assertEquals(user, userService.update(user));

        verify(user).setCar(any());

    }

    @Test
    public void updateTestThrowsUserNotFound(){
        when(userRepository.findByEmail(any())).thenReturn(Optional.empty());

        assertThrows(UserNotFound.class, ()->userService.update(user));

        verify(user, never()).setCar(any());
    }

}