export interface Car {
  id: number;
  seatsNumber: number;
  carClass: string;
  lastInspection: string;
  serviceable: boolean;
}

export function getEmptyCar(): Car {
  return {
    id: null,
    seatsNumber: null,
    carClass: null,
    lastInspection: null,
    serviceable: null
  };
}

export function getCar(id: number, seatsNumber: number,
                       carClass: string, lastInspection: string,
                       serviceable: boolean): Car {
  return {
    id,
    seatsNumber,
    carClass,
    lastInspection,
    serviceable
  };
}
