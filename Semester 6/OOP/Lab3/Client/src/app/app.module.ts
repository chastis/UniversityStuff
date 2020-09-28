import {BrowserModule} from '@angular/platform-browser';
import {APP_INITIALIZER, NgModule} from '@angular/core';

import {AppRoutingModule} from './app-routing.module';
import {AppComponent} from './app.component';
import {NavigationComponent} from './navigation/navigation.component';
import {ClientProfileComponent} from './client/client-profile/client-profile.component';
import {BrowserAnimationsModule} from '@angular/platform-browser/animations';
import {KeycloakAngularModule, KeycloakBearerInterceptor, KeycloakService} from 'keycloak-angular';
import {MatCardModule} from '@angular/material/card';
import {MatButtonModule} from '@angular/material/button';
import {MatInputModule} from '@angular/material/input';
import {MatSelectModule} from '@angular/material/select';
import {MatPaginatorModule} from '@angular/material/paginator';
import {MatListModule} from '@angular/material/list';
import {MatToolbarModule} from '@angular/material/toolbar';
import {MatIconModule} from '@angular/material/icon';
import {FormsModule, ReactiveFormsModule} from '@angular/forms';
import {MatFormFieldModule} from '@angular/material/form-field';
import {MatDialogModule} from '@angular/material/dialog';
import {HTTP_INTERCEPTORS, HttpClientModule} from '@angular/common/http';
import {RouterModule} from '@angular/router';
import {FlexLayoutModule, FlexModule} from '@angular/flex-layout';
import {initializer} from '../utils/app-init';
import {AppAuthGuard} from './service/AppAuthGuard';
import { AddBookingComponent } from './client/add-booking/add-booking.component';
import { BookingSimpleItemComponent } from './client/booking-simple-item/booking-simple-item.component';
import { DispatcherProfileComponent } from './dispatcher/dispatcher-profile/dispatcher-profile.component';
import { DriverProfileComponent } from './driver/driver-profile/driver-profile.component';
import { BookingDispatcherItemComponent } from './dispatcher/booking-dispatcher-item/booking-dispatcher-item.component';
import { BookingDispatcherDialogComponent } from './dispatcher/booking-dispatcher-dialog/booking-dispatcher-dialog.component';
import { RideDriverItemComponent } from './driver/ride-driver-item/ride-driver-item.component';
import { CarDialogComponent } from './driver/car-dialog/car-dialog.component';

@NgModule({
  declarations: [
    AppComponent,
    NavigationComponent,
    ClientProfileComponent,
    AddBookingComponent,
    BookingSimpleItemComponent,
    DispatcherProfileComponent,
    DriverProfileComponent,
    BookingDispatcherItemComponent,
    BookingDispatcherDialogComponent,
    RideDriverItemComponent,
    CarDialogComponent
  ],
  imports: [
    BrowserModule,
    AppRoutingModule,
    BrowserAnimationsModule,
    KeycloakAngularModule,
    MatCardModule,
    MatButtonModule,
    MatInputModule,
    MatSelectModule,
    MatPaginatorModule,
    MatListModule,
    MatToolbarModule,
    MatIconModule,
    MatDialogModule,
    MatFormFieldModule,
    FormsModule,
    ReactiveFormsModule,
    FlexModule,
    FlexLayoutModule,
    RouterModule,
    HttpClientModule
  ],
  providers: [
    {
      provide: APP_INITIALIZER,
      useFactory: initializer,
      deps: [KeycloakService],
      multi: true
    },
    {
      provide: AppAuthGuard
    },
    {
      provide: HTTP_INTERCEPTORS,
      useClass: KeycloakBearerInterceptor,
      multi: true
    }
  ],
  bootstrap: [AppComponent]
})
export class AppModule {
}
