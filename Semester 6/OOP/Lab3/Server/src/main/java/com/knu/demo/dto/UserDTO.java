package com.knu.demo.dto;

import com.fasterxml.jackson.annotation.JsonInclude;
import lombok.Data;
import lombok.NoArgsConstructor;

import javax.validation.constraints.NotNull;

@Data
@NoArgsConstructor
@JsonInclude(JsonInclude.Include.NON_NULL)
public class UserDTO {
    @NotNull(message = "Email is required")
    private String email;

    @NotNull(message = "Name is required")
    private String name;

    private String surname;

    private CarDTO car;
}
