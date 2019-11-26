clc
clear


X = imread("x2.bmp");
X = double(X);
X = [X; ones(size(X, 2), 1)'];
imshow(uint8(X));

figure
Y = imread("y2.bmp");
Y = double(Y);
imshow(uint8(Y));


X_pseudo = Grevil(X);
A = Y * X_pseudo + rand(size(Y, 1), size(X, 1)) * Z(X_pseudo, X);
is_correct = A * X;

figure
imshow(uint8(is_correct));

X_pseudo = MurPenroze(X);
A = Y * X_pseudo + rand(size(Y, 1), size(X, 1)) * Z(X_pseudo, X);
is_correct = A * X;

figure
imshow(uint8(is_correct));


function returnable_value = Z(A, A_pseudo)
  returnable_value = eye(size (A_pseudo, 1)) - A_pseudo * A;
end

function returnable_value = Grevil(A)
  is_swap = 0;
  if (size(A, 1) > size(A, 2))
    is_swap = 1; 
    A = A';
  end
  
  current_vector = A(1, :)';
  A_pseudo = 0;                  
  current_vector_scalar = current_vector' * current_vector;
  if (current_vector_scalar == 0)                 
    A_pseudo = current_vector;
  else
    A_pseudo = current_vector / current_vector_scalar;
  end
  
  A_iter = current_vector';
  for i = 2 : size(A, 1)
    current_vector = A(i, :)';                  
    Z_A = Z(A_iter, A_pseudo);       
    A_iter = [A_iter; current_vector'];         
    denom_Z = current_vector' * Z_A * current_vector;         
    if (denom_Z > 0.000001)       
      A_pseudo = [(A_pseudo - (Z_A * current_vector * current_vector' * A_pseudo) / denom_Z), (Z_A * current_vector) / denom_Z]; 
    else
      R_A = A_pseudo * A_pseudo';     
      denom_R = 1 + current_vector' * R_A * current_vector;                          
      A_pseudo = [(A_pseudo - (R_A * current_vector * current_vector' * A_pseudo) / denom_R), (R_A * current_vector) / denom_R];
    end
  end
  
  if (is_swap)
    A_pseudo = A_pseudo';
  end
  returnable_value = A_pseudo;
 end


function returnable_value = J (A_current, A_next)
  returnable_value = max(max((A_current - A_next) .^ 2));      
end

function returnable_value = MurPenroze (A)
  is_swap = 0;
  if (size(A,1) > size(A,2))        
    is_swap = 1;
    A = A';
  end
  
  epsilon = 1e-8;                                 
  infinity = 1e9;
  A_pseudo_current = infinity * ones(size(A))';   
  A_pseudo_next = -infinity * ones(size(A))';
  delta = 10.0;
  counter = 0;
  while (J(A_pseudo_current, A_pseudo_next) > epsilon) 
    A_pseudo_current = A_pseudo_next;
    A_pseudo_next = A' * inv(A * A' + (delta) * eye(size(A, 1))); 
    delta = delta / 2.0;
    counter = counter + 1;
    printf("%d\n", counter);
  end
  
  if (is_swap)
    A_pseudo_next = A_pseudo_next';
  end
  returnable_value = A_pseudo_next;
end