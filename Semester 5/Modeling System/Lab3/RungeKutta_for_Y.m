
function retval = RungeKutta_for_Y (A, y, h)
  k1 = h*dy_dt(A, y);
  k2 = h*dy_dt(A, y + k1/2.0);
  k3 = h*dy_dt(A, y + k2/2.0);
  k4 = h*dy_dt(A, y + k3);
  retval = y + (k1 + k2*2.0 + k3*2.0 + k4)/6.0;
end
