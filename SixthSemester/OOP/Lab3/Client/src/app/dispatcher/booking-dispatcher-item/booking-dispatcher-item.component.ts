import {Component, EventEmitter, Input, OnInit, Output} from '@angular/core';
import {Booking} from '../../models/booking.model';
import {BookingDispatcherDialogComponent} from '../booking-dispatcher-dialog/booking-dispatcher-dialog.component';
import {MatDialog} from '@angular/material/dialog';

@Component({
  selector: 'app-booking-dispatcher-item',
  templateUrl: './booking-dispatcher-item.component.html',
  styleUrls: ['./booking-dispatcher-item.component.css']
})
export class BookingDispatcherItemComponent implements OnInit {
  @Input() booking: Booking;
  @Output() changed = new EventEmitter<boolean>();

  constructor(public dialog: MatDialog) {
  }

  ngOnInit(): void {
  }

  showDialog() {
    const dialogRef = this.dialog.open(
      BookingDispatcherDialogComponent,
      {
        width: '30em',
        data: this.booking,
      }
    );

    dialogRef.afterClosed().subscribe(
      _ => this.changed.emit(true)
    )
    ;
  }
}
