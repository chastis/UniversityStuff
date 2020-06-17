package com.knu.demo.service.data;

import com.knu.demo.entity.User;
import com.knu.demo.exception.UserNotFound;
import com.knu.demo.repository.UserRepository;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.Optional;

@Service
@RequiredArgsConstructor
public class UserService {
    private final UserRepository userRepository;

    public Optional<User> findUserByEmail(String email) {
        return userRepository.findByEmail(email);
    }

    @Transactional
    public User update(User currentUser) {
        Optional<User> oldUser = userRepository.findByEmail(currentUser.getEmail());
        if (!oldUser.isPresent()) {
            throw new UserNotFound("User with email " + currentUser.getEmail() + " not found");
        }
        User user = oldUser.get();
        user.setCar(currentUser.getCar());
        return user;
    }
}
