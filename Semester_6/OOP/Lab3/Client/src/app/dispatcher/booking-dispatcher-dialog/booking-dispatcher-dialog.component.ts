import {Component, Inject, OnInit} from '@angular/core';
import {Booking} from '../../models/booking.model';
import {BookingService} from '../../service/bookingService/booking.service';
import {Observable} from 'rxjs';
import {MAT_DIALOG_DATA, MatDialogRef} from '@angular/material/dialog';
import {ClientProfileComponent} from '../../client/client-profile/client-profile.component';
import {User} from '../../models/user.model';
import {CarService} from '../../service/carService/car.service';
import {FormControl, FormGroup, Validators} from '@angular/forms';
import {Car} from '../../models/car.model';
import {RideService} from '../../ride.service';
import {getRide} from '../../models/ride.model';

@Component({
  selector: 'app-booking-dispatcher-dialog',
  templateUrl: './booking-dispatcher-dialog.component.html',
  styleUrls: ['./booking-dispatcher-dialog.component.css']
})
export class BookingDispatcherDialogComponent implements OnInit {
  cars: Observable<Car[]>;
  form: FormGroup;

  constructor(public dialogRef: MatDialogRef<ClientProfileComponent>,
              @Inject(MAT_DIALOG_DATA) public booking: Booking,
              private bookingService: BookingService,
              private carService: CarService,
              private rideService: RideService) {
  }

  ngOnInit(): void {
    this.cars = this.carService.getCarsByBooking(this.booking.id);
    this.form = new FormGroup({
      car: new FormControl(),
      price: new FormControl(0, [Validators.required, Validators.min(0)])
    });
  }

  submit() {
    this.addRide();
  }

  reject() {
    this.updateBooking();
  }

  updateBooking() {
    this.bookingService.updateBooking(this.booking.id, 'REJECTED').subscribe(
      _ => this.dialogRef.close(),
      err => {
        console.log(err);
        alert(err.message);
      }
    );
  }

  addRide() {
    const ride = getRide(null, this.form.get('price').value, this.form.get('car').value.id, this.booking.id);
    this.rideService.addRide(ride).subscribe(
      _ => this.dialogRef.close(),
      err => {
        console.log(err);
        alert(err.message);
      }
    );
  }
}
