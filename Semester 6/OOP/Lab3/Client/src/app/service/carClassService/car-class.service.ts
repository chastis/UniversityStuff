import {Injectable} from '@angular/core';
import {Observable} from 'rxjs';
import {HttpClient} from '@angular/common/http';
import {environment} from '../../../environments/environment';

@Injectable({
  providedIn: 'root'
})
export class CarClassService {

  constructor(private http: HttpClient) {
  }

  getCarClasses(): Observable<string[]> {
    return this.http.get<string[]>(environment.carClassStatusService);
  }
}
