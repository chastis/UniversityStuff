import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { BookingSimpleItemComponent } from './booking-simple-item.component';

describe('BookingSimpleItemComponent', () => {
  let component: BookingSimpleItemComponent;
  let fixture: ComponentFixture<BookingSimpleItemComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ BookingSimpleItemComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(BookingSimpleItemComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
