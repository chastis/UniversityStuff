import {Component, OnInit} from '@angular/core';
import {Observable} from 'rxjs';
import {getUser, User} from '../../models/user.model';
import {Router} from '@angular/router';
import {KeycloakService} from 'keycloak-angular';
import {UserService} from '../../service/userService/user.service';
import {map} from 'rxjs/operators';
import {RegistrationService} from '../../service/registrationService/registration.service';
import {MatDialog} from '@angular/material/dialog';
import {AddBookingComponent} from '../add-booking/add-booking.component';
import {Booking} from '../../models/booking.model';
import {BookingService} from '../../service/bookingService/booking.service';

@Component({
  selector: 'app-client-profile',
  templateUrl: './client-profile.component.html',
  styleUrls: ['./client-profile.component.css']
})
export class ClientProfileComponent implements OnInit {
  userData: Observable<User>;
  bookings: Observable<Booking[]>;

  constructor(private router: Router,
              private keycloakAngular: KeycloakService,
              private userService: UserService,
              private registrationService: RegistrationService,
              private bookingService: BookingService,
              public dialog: MatDialog) {
  }

  ngOnInit(): void {
    try {
      console.log(this.keycloakAngular.getKeycloakInstance().loadUserInfo());
      this.keycloakAngular.loadUserProfile(true).then(
        data => {
          const user = getUser(Number(data.id), data.email,
            data.firstName, data.lastName,
            'CLIENT', '',
            null);
          this.userData = this.registrationService.registerUser(user).pipe(
            map(_ => {
                this.userService.setCurrentUser(user);
                return user;
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
    this.bookings = this.bookingService.getBookingsByUser(this.userService.getCurrentUser().email);
  }

  openDialog() {
    const dialogRef = this.dialog.open(
      AddBookingComponent,
      {
        width: '30em'
      }
    );

    dialogRef.afterClosed().subscribe(
      _ => this.loadBookings()
    );
  }
}
