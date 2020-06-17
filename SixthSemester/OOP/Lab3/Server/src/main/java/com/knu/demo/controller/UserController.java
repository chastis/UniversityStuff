package com.knu.demo.controller;

import com.knu.demo.dto.UserDTO;
import com.knu.demo.service.UserControllerService;
import lombok.RequiredArgsConstructor;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.web.bind.annotation.PatchMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;

import javax.validation.Valid;

@RestController
@CrossOrigin
@RequiredArgsConstructor
public class UserController {
    private final UserControllerService userService;

    @PatchMapping(value = "/user")
    public ResponseEntity<String> updateUser(@Valid @RequestBody UserDTO userDTO) {
        userService.update(userDTO);
        return ResponseEntity.accepted().build();
    }
}
