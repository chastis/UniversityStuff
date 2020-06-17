import {Component, OnInit} from '@angular/core';
import {Router} from '@angular/router';
import {User} from '../models/user.model';
import {UserService} from '../service/userService/user.service';
import {RegistrationService} from '../service/registrationService/registration.service';
import {KeycloakService} from 'keycloak-angular';

@Component({
  selector: 'app-navigation',
  templateUrl: './navigation.component.html',
  styleUrls: ['./navigation.component.css']
})
export class NavigationComponent implements OnInit {
  currentUser: User;
  login: Promise<boolean>;

  constructor(private router: Router,
              private userService: UserService,
              private registrationService: RegistrationService,
              private keycloakAngular: KeycloakService) {
  }

  ngOnInit(): void {
    this.currentUser = this.userService.getCurrentUser();
    this.login = this.keycloakAngular.isLoggedIn();
  }

  toProfile() {
    const roles = this.keycloakAngular.getUserRoles();
    if (roles.includes('dispatcher')) {
      this.router.navigateByUrl('/dispatcher_profile');
    } else if (roles.includes('client')) {
      this.router.navigateByUrl('/user_profile');
    } else if (roles.includes('driver')) {
      this.router.navigateByUrl('/driver_profile');
    }
  }

  logout() {
    this.registrationService.logout(this.currentUser);
    this.keycloakAngular.logout();
  }

}
