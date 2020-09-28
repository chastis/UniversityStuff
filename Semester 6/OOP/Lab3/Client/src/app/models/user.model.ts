import {Car} from './car.model';

export interface User {
  id: number;
  email: string;
  name: string;
  surname: string;
  role: string;
  password: string;
  car: Car;
}

export function getEmptyUser(): User {
  return {
    id: null,
    email: null,
    name: null,
    surname: null,
    role: null,
    password: null,
    car: null
  };
}

export function getUser(id: number, email: string,
                        name: string, surname: string,
                        role: string, password: string,
                        car: Car): User {
  return {
    id,
    email,
    name,
    surname,
    role,
    password,
    car
  };
}
