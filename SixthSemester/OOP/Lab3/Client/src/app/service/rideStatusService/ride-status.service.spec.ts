import { TestBed } from '@angular/core/testing';

import { RideStatusService } from './ride-status.service';

describe('RideStatusService', () => {
  let service: RideStatusService;

  beforeEach(() => {
    TestBed.configureTestingModule({});
    service = TestBed.inject(RideStatusService);
  });

  it('should be created', () => {
    expect(service).toBeTruthy();
  });
});
