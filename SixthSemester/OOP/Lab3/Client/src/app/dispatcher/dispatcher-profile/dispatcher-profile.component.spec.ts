import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { DispatcherProfileComponent } from './dispatcher-profile.component';

describe('DispatcherProfileComponent', () => {
  let component: DispatcherProfileComponent;
  let fixture: ComponentFixture<DispatcherProfileComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ DispatcherProfileComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(DispatcherProfileComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
