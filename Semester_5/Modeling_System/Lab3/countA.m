% counts matrix A

function retval = countA(m, c)
  A = zeros(6, 6);
  A(1, 2) = 1;
  A(3, 4) = 1;
  A(5, 6) = 1;
  A(2, 1) = -(c(1)+c(2))/m(1);
  A(2, 3) = c(2)/m(1);
  
  A(4, 1) = c(2)/m(2);
  A(4, 3) = -(c(2)+c(3))/m(2);
  A(4, 5) = c(3)/m(2);
  
  A(6, 3) = c(3)/m(3);
  A(6, 5) = -(c(3)+c(4))/m(3);
  retval = A;
end
