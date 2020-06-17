package com.knu.demo.service.data;

import com.knu.demo.entity.User;
import com.knu.demo.repository.UserRepository;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

@Service
@RequiredArgsConstructor
public class RegistrationService {
    private final UserRepository userRepository;

    @Transactional
    public User save(User currentUser) {
        return userRepository.findByEmail(currentUser.getEmail()).orElseGet(() -> userRepository.save(currentUser));
    }
}
