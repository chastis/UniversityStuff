export interface Ride {
  id: number;
  price: number;
  carId: number;
  bookingId: number;
}

export function getEmptyRide(): Ride {
  return {
    id: null,
    price: null,
    carId: null,
    bookingId: null
  };
}

export function getRide(id: number, price: number, carId: number, bookingId: number): Ride {
  return {
    id,
    price,
    carId,
    bookingId
  };
}
