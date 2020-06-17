import {Injectable} from '@angular/core';
import {HttpClient} from '@angular/common/http';
import {Observable} from 'rxjs';
import {environment} from '../../../environments/environment';

@Injectable({
  providedIn: 'root'
})
export class RideStatusService {

  constructor(private http: HttpClient) {
  }

  getRideStatus(): Observable<string[]> {
    return this.http.get<string[]>(environment.rideStatusService);
  }
}
