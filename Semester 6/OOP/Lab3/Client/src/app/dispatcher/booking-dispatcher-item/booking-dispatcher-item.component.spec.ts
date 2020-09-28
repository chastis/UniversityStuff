import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { BookingDispatcherItemComponent } from './booking-dispatcher-item.component';

describe('BookingDispatcherItemComponent', () => {
  let component: BookingDispatcherItemComponent;
  let fixture: ComponentFixture<BookingDispatcherItemComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ BookingDispatcherItemComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(BookingDispatcherItemComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
