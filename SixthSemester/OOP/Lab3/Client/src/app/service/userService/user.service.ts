import {Injectable} from '@angular/core';
import {AppAuthGuard} from '../AppAuthGuard';
import {HttpClient} from '@angular/common/http';
import {User} from '../../models/user.model';
import {Observable} from 'rxjs';
import {environment} from '../../../environments/environment';

@Injectable({
  providedIn: 'root'
})
export class UserService {

  constructor(private appAuthGuard: AppAuthGuard,
              private http: HttpClient) {
  }

  getCurrentUser(): User {
    return JSON.parse(localStorage.getItem('currentUser'));
  }

  setCurrentUser(user: User) {
    localStorage.setItem('currentUser', JSON.stringify(user));
  }

  logout() {
    if (this.appAuthGuard.isStillLoggedIn()) {
      this.appAuthGuard.doLogout();
      localStorage.clear();
    }
  }

  updateUser(user: User): Observable<string> {
    return this.http.patch<string>(environment.userService, user);
  }
}
