% Sonny Ji
% ME380
% Homework #5
% Problem(s): 4

clc
clear all
diary

%----------------Problem 1.1
%\/----------------------------------------\/
G1 = tf([1 5], [1 2]);
G2 = tf([1], [1 2 5]);

G = G1 * G2;

figure('Name', 'Problem 1.1', 'NumberTitle', 'off')
rlocus(G)
%/\----------------------------------------/\