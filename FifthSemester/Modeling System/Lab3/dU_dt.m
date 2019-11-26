

function retval = dU_dt (A, U, y, m, c)
  dAy_b = zeros(6, 3);
  dAy_b(6,1) =(y(3)-y(5))/m(3);
  dAy_b(2,2) = ((c(2)+c(1))*y(1)- c(2)*y(3))/m(1)^2;
  dAy_b(4,1) = (-y(3)+y(5))/m(2);
  dAy_b(6,3) = (-c(3)*y(3)+(c(4)+c(3))*y(5))/m(3)^2;
  retval = A*U + dAy_b;
end
