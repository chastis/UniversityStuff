import {Injectable} from '@angular/core';
import {HttpClient} from '@angular/common/http';
import {environment} from '../../../environments/environment';
import {Booking} from '../../models/booking.model';
import {Observable} from 'rxjs';

@Injectable({
  providedIn: 'root'
})
export class BookingService {

  constructor(private http: HttpClient) {
  }

  postBooking(booking: Booking): Observable<Booking> {
    return this.http.post<Booking>(environment.bookingService, booking);
  }

  getBookingsByUser(userEmail: string): Observable<Booking[]> {
    return this.http.get<Booking[]>(environment.bookingService + '/user/' + userEmail);
  }

  getBookingsByStatus(status: string): Observable<Booking[]> {
    return this.http.get<Booking[]>(environment.bookingService + '/status/' + status);
  }

  updateBooking(bookingId: number, status: string): Observable<Booking> {
    return this.http.patch<Booking>(environment.bookingService + '/' + bookingId + '/status/' + status, status);
  }
}
