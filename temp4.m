% Increasing precision
digits(50)

% Setting mass matrix
m = [1 0 0 0 0;
	0 1 0 0 0;
	0 0 1 0 0;
	0 0 0 1 0;
	0 0 0 0 1;];

% Setting spring matrix
k = [2 -1  0  0  0;
    -1  2 -1  0  0;
     0 -1  2 -1  0;
	0  0 -1  2 -1;
	0  0  0 -1  2;];

L = 1;
T = 1;

k = k * 6 * (T / L);

% Solving natural frequencies
[V, E] = eig(k, m);
wn = sqrt(E);


V1 = [0 0 0 0 0; V; 0 0 0 0 0;];
u1 = V1(:, [1]).';
u2 = V1(:, [2]).';
u3 = V1(:, [3]).';
u4 = V1(:, [4]).';
u5 = V1(:, [5]).';
u = [0:1:6];

% (c)
u11 = V(:, [1]).';
u33 = V(:, [3]);
orthogon = vpa(u11 * m * u33);

% (d)
x0 = [1 -1 -1 1 -1].';
x00 = [0 0 1 0 0].';
w = [];
for i = [1:1:5]
	w = [w; wn(i, i)];
end
alpha = [];
beta = [];
mu = [];
for i = [1:1:5]
	alpha = [alpha; (V(:, i).' * m * x0)];
	beta = [beta; (V(:, i).' * m * x00)];
	mu = [mu; (V(:, i).' * m * V(:, i))];
end
C = [];
phi = [];
for i = [1:1:5]
	C = [C; sqrt((alpha(i)^2) + (beta(i) / w(i))^2)];
	phi = [phi; atan2((alpha(i) * w(i)), (beta(i)))];
end

Vc = V .* C.';


% Plotting (b)
figure('Name', 'Problem 20 (b)', 'NumberTitle', 'off')
subplot(5, 1, 1)
plot(u, u1, '-om')
title('Problem (20): Mode 1')
ylabel('{u}1')
xlabel('u')
grid on
ylim([-1 1])
subplot(5, 1, 2)
plot(u, u2, '-om')
title('Problem (20): Mode 2')
ylabel('{u}2')
xlabel('u')
grid on
ylim([-1 1])
subplot(5, 1, 3)
plot(u, u3, '-om')
title('Problem (20): Mode 3')
ylabel('{u}3')
xlabel('u')
grid on
ylim([-1 1])
subplot(5, 1, 4)
plot(u, u4, '-om')
title('Problem (20): Mode 4')
ylabel('{u}4')
xlabel('u')
grid on
ylim([-1 1])
subplot(5, 1, 5)
plot(u, u5, '-om')
title('Problem (20): Mode 5')
ylabel('{u}5')
xlabel('u')
grid on
ylim([-1 1])

% (e)
t = [0:0.001:10];
x1 = 0;
for i = [1:1:5]
	x1 = x1 + (Vc(1, i) * sin(w(i) * t + phi(i)));
end
x2 = 0;
for i = [1:1:5]
	x2 = x2 + (Vc(2, i) * sin(w(i) * t + phi(i)));
end
x3 = 0;
for i = [1:1:5]
	x3 = x3 + (Vc(3, i) * sin(w(i) * t + phi(i)));
end
x4 = 0;
for i = [1:1:5]
	x4 = x4 + (Vc(4, i) * sin(w(i) * t + phi(i)));
end
x5 = 0;
for i = [1:1:5]
	x5 = x5 + (Vc(5, i) * sin(w(i) * t + phi(i)));
end
figure('Name', 'Problem 20 (e)', 'NumberTitle', 'off')
subplot(5, 1, 1)
plot(t, x1, 'm')
title('Problem (20): x1')
ylabel('x1(t)')
xlabel('t')
grid on
subplot(5, 1, 2)
plot(t, x2, 'm')
title('Problem (20): x2')
ylabel('x2(t)')
xlabel('t')
grid on
subplot(5, 1, 3)
plot(t, x3, 'm')
title('Problem (20): x3')
ylabel('x3(t)')
xlabel('t')
grid on
subplot(5, 1, 4)
plot(t, x4, 'm')
title('Problem (20): x4')
ylabel('x4(t)')
xlabel('t')
grid on
subplot(5, 1, 5)
plot(t, x5, 'm')
title('Problem (20): x5')
ylabel('x5(t)')
xlabel('t')
grid on