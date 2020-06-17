import {Component, Input, OnInit} from '@angular/core';
import {Booking} from '../../models/booking.model';

@Component({
  selector: 'app-booking-simple-item',
  templateUrl: './booking-simple-item.component.html',
  styleUrls: ['./booking-simple-item.component.css']
})
export class BookingSimpleItemComponent implements OnInit {
  @Input() booking: Booking;

  constructor() {
  }

  ngOnInit(): void {
  }

}
