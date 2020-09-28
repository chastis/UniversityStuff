clear
figure
dt = 0.01;
T = 5;
t = 0:dt:T;

y = load("f11.txt");
N = length(y);
plot(t, y), grid

fourier_func = zeros(1, N);
for m = 1:N
  for j = 1:N
    fourier_func(m) = fourier_func(m) + 1/N*y(j)*exp(1)^(-1i*2*pi/N*m*j);
  end
end
figure

df = 1/T;
n = length(t);
plot(abs(fourier_func)), grid
f = 0:df:round(n/2) * df;
figure
plot(f, abs(fourier_func(1:round(n/2)+1))) 


fourier_func = abs(fourier_func);
counter = 0;
extr = zeros(2,1);
for j = 3:round(N/2)-1
  if (fourier_func(j) > fourier_func(j+1) && fourier_func(j) > fourier_func(j-1) && abs(fourier_func(j)-fourier_func(j+1)) > 1)
    counter = counter + 1;
    extr(counter) = j*df;
  end
end

f_sin = sin(2*pi*extr(1)*t);

A = [sum(t.^6), sum(t.^5), sum(t.^4), sum(f_sin.*t.^3), sum(t.^3);
     sum(t.^5), sum(t.^4), sum(t.^3), sum(f_sin.*t.^2), sum(t.^2);
     sum(t.^4), sum(t.^3), sum(t.^2), sum(f_sin.*t),    sum(t);
     sum(f_sin.*t.^3), sum(f_sin.*t.^2), sum(f_sin.*t), sum(f_sin.*f_sin), sum(N*f_sin);
     sum(t.^3), sum(t.^2), sum(t), sum(N*f_sin), N];
     
c = [sum(y.*t.^3), sum(y.*t.^2), sum(y.*t), sum(y.*f_sin),  sum(y)];

a = inv(A)*c'
temp = a'
aprox_f = a(1).*t.^3 + a(2).*t.^2 + a(3).*t + a(4).*f_sin +a(5);

figure
plot(t, aprox_f), grid

error_value = sum((aprox_f-y).^2)