import {Component, OnInit} from '@angular/core';
import {Router} from '@angular/router';
import {KeycloakService} from 'keycloak-angular';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent implements OnInit {
  title = 'Client';

  constructor(private router: Router,
              private keycloakAngular: KeycloakService) {
  }

  ngOnInit(): void {
    const roles = this.keycloakAngular.getUserRoles();
    if (roles.includes('dispatcher')) {
      this.router.navigateByUrl('/dispatcher_profile');
    } else if (roles.includes('client')) {
      this.router.navigateByUrl('/user_profile');
    } else if (roles.includes('driver')) {
      this.router.navigateByUrl('/driver_profile');
    }
  }
}
