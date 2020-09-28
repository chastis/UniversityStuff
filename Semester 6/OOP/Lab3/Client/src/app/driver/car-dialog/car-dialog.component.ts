import {Component, Inject, OnInit} from '@angular/core';
import {MAT_DIALOG_DATA, MatDialogRef} from '@angular/material/dialog';
import {ClientProfileComponent} from '../../client/client-profile/client-profile.component';
import {User} from '../../models/user.model';
import {BookingService} from '../../service/bookingService/booking.service';
import {CarClassService} from '../../service/carClassService/car-class.service';
import {UserService} from '../../service/userService/user.service';
import {FormControl, FormGroup, Validators} from '@angular/forms';
import {Observable} from 'rxjs';
import {getCar} from '../../models/car.model';

@Component({
  selector: 'app-car-dialog',
  templateUrl: './car-dialog.component.html',
  styleUrls: ['./car-dialog.component.css']
})
export class CarDialogComponent implements OnInit {
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
      carClass: new FormControl(),
      seatsNumber: new FormControl(4, [Validators.required, Validators.min(0)]),
    });
    this.classList = this.carClassService.getCarClasses();
  }

  submit(): void {
    if (this.form.valid) {
      this.data.car = getCar(null, this.form.get('seatsNumber').value,
        this.form.get('carClass').value, Date.now().toString(),
        true);
      this.userService.setCurrentUser(this.data);
      this.userService.updateUser(this.data).subscribe(
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
