clear
clc

% input observed data
observed_data_y = dlmread('y1.txt',' ');
[sizeM, sizeN] = size(observed_data_y);
% spring stiffness
c = [0.14, 0.3, 0.1, 0.12]';
% mass
m = [10, 28, 21]';

% dt size
h = 0.2;
% start of interval
t0 = 0;
% end of interval
tk = 50;
% error value
eps = 1e-6;

% I(beta)
I = inf;
% number of steps in algorithm
stepsCounter = 0;

% result of algorithm
yResult = zeros(sizeM, sizeN);

while (I > eps)
  stepsCounter = stepsCounter + 1;
  y = observed_data_y(:, 1);
  yResult(:, 1) = y;
  deltaY = zeros(6, 1);
  U = zeros(6, 3);
  integral_UU = zeros(3, 3);
  integral_Uy = zeros(3, 1);
  I = 0.0;
  A = countA(m, c);
  
  % count integrals by Riemann sum
  for i = 2:sizeN
    % count U(n+1), y(n+1) by Runge-Kutta formulas
    U_next = RungeKutta_for_U(A, U, y, m, c, h);
    Y_next = RungeKutta_for_Y(A, y, h);
    deltaY_next = observed_data_y(:, i) - Y_next;
    yResult(:, i) = y;
    
    % add Riemann sum to integrals     
    integral_UU = integral_UU + h*(U'*U+U_next'*U_next)/2.0;
    integral_Uy = integral_Uy + h*(U'*deltaY + U_next'*deltaY_next)/2.0;
    % error count
    I = I + h*(deltaY'*deltaY + deltaY_next'*deltaY_next)/2.0;
    % change values for next step
    U = U_next; y = Y_next; deltaY = deltaY_next;
  end    
  
  % count delta beta
  % integral_UU
  delta = pinv(integral_UU)*integral_Uy;
  % change beta values
  c(3) = c(3) + delta(1);
  m(1) = m(1) + delta(2);
  m(3) =  m(3) + delta(3);
  
  disp(['I = ', num2str(I)])
end

disp(['Number of Iterations ', num2str(stepsCounter)])

disp(['c(3) = ', num2str(c(3))])
disp(['m(1) = ', num2str(m(1))])
disp(['m(3) = ', num2str(m(3))])

