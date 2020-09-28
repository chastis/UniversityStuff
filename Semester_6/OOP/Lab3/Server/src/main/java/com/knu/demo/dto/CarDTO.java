package com.knu.demo.dto;

import com.fasterxml.jackson.annotation.JsonInclude;
import lombok.Data;
import lombok.NoArgsConstructor;

import javax.validation.constraints.NotNull;
import java.sql.Date;

@Data
@NoArgsConstructor
@JsonInclude(JsonInclude.Include.NON_NULL)
public class CarDTO {
    private Long id;

    @NotNull(message = "Seats number is required")
    private Integer seatsNumber;

    @NotNull(message = "Car class is required")
    private String carClass;

    private Date lastInspection;

    private Boolean serviceable;
}
