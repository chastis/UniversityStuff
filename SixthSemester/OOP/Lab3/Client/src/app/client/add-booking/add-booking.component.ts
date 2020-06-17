import {Component, Inject, OnInit} from '@angular/core';
import {MAT_DIALOG_DATA, MatDialogRef} from '@angular/material/dialog';
import {ClientProfileComponent} from '../client-profile/client-profile.component';
import {User} from '../../models/user.model';
import {BookingService} from '../../service/bookingService/booking.service';
import {FormControl, FormGroup, Validators} from '@angular/forms';
import {getBooking} from '../../models/booking.model';
import {Observable} from 'rxjs';
import {CarClassService} from '../../service/carClassService/car-class.service';
import {UserService} from '../../service/userService/user.service';

@Component({
  selector: 'app-add-booking',
  templateUrl: './add-booking.component.html',
  styleUrls: ['./add-booking.component.css']
})
export class AddBookingComponent implements OnInit {
  form: FormGroup;
  classList: Observable<string[]>;

  constructor(public dialogRef: MatDialogRef<ClientProfileComponent>,
              @Inject(MAT_DIALOG_DATA) public data: User,
              private bookingService: BookingService,
              private carClassService: CarClassService,
              private userService: UserService) {
  }

  ngOnInit(): void {
    this.form = new FormGroup({
      minClass: new FormControl(),
      depart: new FormControl('', [Validators.required, Validators.maxLength(30)]),
      destination: new FormControl('', [Validators.required, Validators.maxLength(30)]),
      minSeats: new FormControl(4, [Validators.required, Validators.min(0)])
    });
    this.classList = this.carClassService.getCarClasses();
  }

  submit(): void {
    if (this.form.valid) {
      const booking = getBooking(null,
        this.form.get('minClass').value,
        this.form.get('depart').value,
        this.form.get('destination').value,
        this.form.get('minSeats').value,
        'PENDING',
        this.userService.getCurrentUser().email);
      this.bookingService.postBooking(booking).subscribe(
        _ => this.dialogRef.close(),
        err => {
          console.log(err);
          alert(err.message);
        }
      );
    }
  }

  loadClassList(): Observable<string[]> {
    this.classList.subscribe(
      data => console.log(data)
    );
    if (this.classList == null) {
      this.classList = this.carClassService.getCarClasses();
    }
    return this.classList;
  }
}
