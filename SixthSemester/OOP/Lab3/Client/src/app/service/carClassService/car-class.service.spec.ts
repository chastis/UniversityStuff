import { TestBed } from '@angular/core/testing';

import { CarClassService } from './car-class.service';

describe('CarClassService', () => {
  let service: CarClassService;

  beforeEach(() => {
    TestBed.configureTestingModule({});
    service = TestBed.inject(CarClassService);
  });

  it('should be created', () => {
    expect(service).toBeTruthy();
  });
});
