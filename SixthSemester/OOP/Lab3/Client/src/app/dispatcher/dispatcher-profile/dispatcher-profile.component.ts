import {Component, OnInit} from '@angular/core';
import {Observable} from 'rxjs';
import {Booking} from '../../models/booking.model';
import {BookingService} from '../../service/bookingService/booking.service';

@Component({
  selector: 'app-dispatcher-profile',
  templateUrl: './dispatcher-profile.component.html',
  styleUrls: ['./dispatcher-profile.component.css']
})
export class DispatcherProfileComponent implements OnInit {
  pendingBookings: Observable<Booking[]>;

  constructor(private bookingService: BookingService) {
  }

  ngOnInit(): void {
    this.loadBookings();
  }

  loadBookings() {
    this.pendingBookings = this.bookingService.getBookingsByStatus('PENDING');
  }

}
