import {Component, EventEmitter, Input, OnInit, Output} from '@angular/core';
import {BookingService} from '../../service/bookingService/booking.service';
import {Booking} from '../../models/booking.model';

@Component({
  selector: 'app-ride-driver-item',
  templateUrl: './ride-driver-item.component.html',
  styleUrls: ['./ride-driver-item.component.css']
})
export class RideDriverItemComponent implements OnInit {
  @Input() booking: Booking;
  @Output() changed = new EventEmitter<boolean>();

  constructor(private bookingService: BookingService) {
  }

  ngOnInit(): void {
  }

  updateRide() {
    this.bookingService.updateBooking(this.booking.id, 'COMPLETED').subscribe(
      _ => this.changed.emit(true)
    );
  }
}
