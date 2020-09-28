package com.knu.demo.service;

import com.knu.demo.entity.RideStatus;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Service;

import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

@Service
@RequiredArgsConstructor
public class RideStatusService {
    public List<String> getRideStatus() {
        return Arrays.stream(RideStatus.values()).map(Enum::toString).collect(Collectors.toList());
    }
}
