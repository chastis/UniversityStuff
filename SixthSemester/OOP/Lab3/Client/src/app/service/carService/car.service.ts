import {Injectable} from '@angular/core';
import {HttpClient} from '@angular/common/http';
import {Car} from '../../models/car.model';
import {Observable} from 'rxjs';
import {Booking} from '../../models/booking.model';
import {environment} from '../../../environments/environment';

@Injectable({
  providedIn: 'root'
})
export class CarService {

  constructor(private http: HttpClient) {
  }

  getCarsByBooking(bookingId: number): Observable<Car[]> {
    return this.http.get<Car[]>(environment.carService + '/booking/' + bookingId);
  }
}
