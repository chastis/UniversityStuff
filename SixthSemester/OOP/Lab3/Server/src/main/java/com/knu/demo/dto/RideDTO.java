package com.knu.demo.dto;

import com.fasterxml.jackson.annotation.JsonInclude;
import lombok.Data;
import lombok.NoArgsConstructor;

import javax.validation.constraints.NotNull;

@Data
@NoArgsConstructor
@JsonInclude(JsonInclude.Include.NON_NULL)
public class RideDTO {
    private Long id;

    @NotNull(message = "Price required")
    private Integer price;

    private Long carId;

    private Long bookingId;
}
