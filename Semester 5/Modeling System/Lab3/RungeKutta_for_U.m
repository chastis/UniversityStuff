
function retval = RungeKutta_for_U (A, U, y, m, c, h)
  k1 = h*dU_dt(A, U, y, m, c);
  k2 = h*dU_dt(A, U + k1/2.0, y, m, c);
  k3 = h*dU_dt(A, U + k2/2.0, y, m, c);
  k4 = h*dU_dt(A, U + k3, y, m, c);
  retval = U + (k1 + k2*2.0 + k3*2.0 + k4)/6.0;
end
