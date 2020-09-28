import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { BookingDispatcherDialogComponent } from './booking-dispatcher-dialog.component';

describe('BookingDispatcherDialogComponent', () => {
  let component: BookingDispatcherDialogComponent;
  let fixture: ComponentFixture<BookingDispatcherDialogComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ BookingDispatcherDialogComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(BookingDispatcherDialogComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
