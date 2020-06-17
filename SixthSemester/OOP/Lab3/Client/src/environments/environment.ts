// This file can be replaced during build by using the `fileReplacements` array.
// `ng build --prod` replaces `environment.ts` with `environment.prod.ts`.
// The list of file replacements can be found in `angular.json`.

import {KeycloakConfig} from 'keycloak-angular';

const keycloakConfig: KeycloakConfig = {
  url: 'http://localhost:8080/auth',
  realm: 'Autobase',
  clientId: 'autobase-frontend',
  credentials: {
    secret: '0bbb934e-e713-4ac8-94fb-711741217b78',
  }
};

export const environment = {
  production: true,
  envName: 'local',
  keycloak: keycloakConfig,
  registerService: 'http://localhost:8180/registration',
  logoutService: 'http://localhost:8180/sso/logout',
  bookingService: 'http://localhost:8180/booking',
  rideStatusService: 'http://localhost:8180/rideStatus',
  carClassStatusService: 'http://localhost:8180/carClass',
  carService: 'http://localhost:8180/car',
  userService: 'http://localhost:8180/user',
  rideService: 'http://localhost:8180/ride'
};

/*
 * For easier debugging in development mode, you can import the following file
 * to ignore zone related error stack frames such as `zone.run`, `zoneDelegate.invokeTask`.
 *
 * This import should be commented out in production mode because it will have a negative impact
 * on performance if an error is thrown.
 */
// import 'zone.js/dist/zone-error';  // Included with Angular CLI.
