import {Injectable} from '@angular/core';
import {HttpClient} from '@angular/common/http';
import {Observable} from 'rxjs';
import {Ride} from './models/ride.model';
import {environment} from '../environments/environment';
import {Booking} from './models/booking.model';

@Injectable({
  providedIn: 'root'
})
export class RideService {

  constructor(private http: HttpClient) {
  }

  addRide(ride: Ride): Observable<Ride> {
    return this.http.post<Ride>(environment.rideService, ride);
  }

  getRideBookingsByCar(carId: number): Observable<Booking[]> {
    return this.http.get<Booking[]>(environment.rideService + '/booking/' + carId);
  }
}
