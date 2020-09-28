export interface Booking {
  id: number;
  minClass: string;
  depart: string;
  destination: string;
  minSeats: number;
  status: string;
  userEmail: string;
}

export function getEmptyBooking(): Booking {
  return {
    id: null,
    minClass: null,
    depart: null,
    destination: null,
    minSeats: null,
    status: null,
    userEmail: null
  };
}

export function getBooking(id: number, minClass: string, depart: string, destination: string, minSeats: number, status: string, userEmail: string): Booking {
  return {
    id,
    minClass,
    depart,
    destination,
    minSeats,
    status,
    userEmail
  };
}
