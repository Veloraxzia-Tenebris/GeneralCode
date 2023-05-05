% Sonny Ji
% ME380
% Homework #4
% Problem(s): 4

clc
clear all
diary

%----------------Problem 4 (c.ii)
%\/----------------------------------------\/
K = 80;

sysCL_1 = tf(K, [1 12 20+K]);
sysCL_2 = tf(K, [1 12 20 K]);

figure()
step(sysCL_1, sysCL_2)
legend("$G_c\left(s\right) = \frac{K}{s + 10}$", "$G_c\left(s\right) = \frac{K}{s \left(s + 10\right)}$", "Interpreter", "latex")
%/\----------------------------------------/\