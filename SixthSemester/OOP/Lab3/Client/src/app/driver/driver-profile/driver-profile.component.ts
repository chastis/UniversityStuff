import {Component, OnInit} from '@angular/core';
import {Observable} from 'rxjs';
import {getUser, User} from '../../models/user.model';
import {Router} from '@angular/router';
import {KeycloakService} from 'keycloak-angular';
import {UserService} from '../../service/userService/user.service';
import {RegistrationService} from '../../service/registrationService/registration.service';
import {map, mergeMap} from 'rxjs/operators';
import {RideService} from '../../ride.service';
import {MatDialog} from '@angular/material/dialog';
import {CarDialogComponent} from '../car-dialog/car-dialog.component';
import {Booking} from '../../models/booking.model';

@Component({
  selector: 'app-driver-profile',
  templateUrl: './driver-profile.component.html',
  styleUrls: ['./driver-profile.component.css']
})
export class DriverProfileComponent implements OnInit {
  userData: Observable<User>;
  bookings: Observable<Booking[]>;

  constructor(private router: Router,
              private keycloakAngular: KeycloakService,
              private userService: UserService,
              private registrationService: RegistrationService,
              private rideService: RideService,
              public dialog: MatDialog) {
  }

  ngOnInit(): void {
    try {
      console.log(this.keycloakAngular.getKeycloakInstance().loadUserInfo());
      this.keycloakAngular.loadUserProfile(true).then(
        data => {
          const user = getUser(Number(data.id), data.email,
            data.firstName, data.lastName,
            'DRIVER', '',
            null);
          this.userData = this.registrationService.registerUser(user).pipe(
            map(resp => {
                this.userService.setCurrentUser(resp);
                return resp;
              },
              err => {
                console.log(err);
                alert(err.message);
              }),
          );
        },
        reason => {
          console.log(reason);
        }
      );
    } catch (e) {
      console.log('Failed to load user details');
    }

    this.loadBookings();
  }

  loadBookings() {
    const user = this.userService.getCurrentUser();
    if (user.car != null) {
      console.log(user.car);
      this.bookings = this.rideService.getRideBookingsByCar(user.car.id);
    }
  }


  setServiceable(serviceable: boolean) {
    const user = this.userService.getCurrentUser();
    user.car.serviceable = serviceable;
    user.car.lastInspection = Date.now().toString();
    this.userData = this.userService.updateUser(user).pipe(
      mergeMap(_ => this.registrationService.registerUser(user))
    );
  }

  addCar() {
    const dialogRef = this.dialog.open(
      CarDialogComponent,
      {
        width: '30em',
        data: this.userService.getCurrentUser()
      }
    );

    dialogRef.afterClosed().pipe(
      map(_ => this.userService.updateUser(this.userService.getCurrentUser())),
      mergeMap(_ => this.userData = this.registrationService.registerUser(this.userService.getCurrentUser()))
    );
  }
}
