import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { RideDriverItemComponent } from './ride-driver-item.component';

describe('RideDriverItemComponent', () => {
  let component: RideDriverItemComponent;
  let fixture: ComponentFixture<RideDriverItemComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ RideDriverItemComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(RideDriverItemComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
