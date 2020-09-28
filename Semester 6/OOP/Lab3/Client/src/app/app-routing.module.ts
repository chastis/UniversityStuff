import {NgModule} from '@angular/core';
import {Routes, RouterModule} from '@angular/router';
import {AppAuthGuard} from './service/AppAuthGuard';
import {AppComponent} from './app.component';
import {ClientProfileComponent} from './client/client-profile/client-profile.component';
import {DispatcherProfileComponent} from './dispatcher/dispatcher-profile/dispatcher-profile.component';
import {DriverProfileComponent} from './driver/driver-profile/driver-profile.component';


const routes: Routes = [
  {
    path: 'user_profile',
    canActivate: [AppAuthGuard],
    component: ClientProfileComponent,
    data: {roles: ['client']}
  },
  {
    path: 'dispatcher_profile',
    canActivate: [AppAuthGuard],
    component: DispatcherProfileComponent,
    data: {roles: ['dispatcher']}
  },
  {
    path: 'driver_profile',
    canActivate: [AppAuthGuard],
    component: DriverProfileComponent,
    data: {roles: ['driver']}
  },
  {
    path: '',
    canActivate: [AppAuthGuard],
    component: AppComponent
  }
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule {
}
