%Random frequencies for sine waves
f1 = 0.1*randi([1, 30], 1, 1);
f2 = 0.1*randi([1, 30], 1, 1);
%Precision of graph
T = 0.01;
%Zero padding for FFT
P = 50000;
%How strict the peak filtering is
pp = 150;
%How green the green is
g = 0.6;
%Setting x from 0 to 2pi with above precision and creating sine waves
x = 0:T:2*pi;
y1 = sin((f1*2*pi*x)+0.25);
y2 = 1.5*sin((f2*2*pi*x)+0.125);
%Set interpreter to LaTeX
set(groot,'defaultAxesTickLabelInterpreter','latex');
set(groot,'defaultLegendInterpreter','latex');
%LaTeX strings for sine waves
s1 = strcat('$sin(', num2str(f1), '\cdot 2 \pi x + 0.25)$');
s2 = strcat('$1.5sin(', num2str(f2), '\cdot 2 \pi x + 0.125)$');
%X range of graph
xran = 6;
%Plot sine waves
subplot(2, 2, 1)
plot(x, y1, 'r', x, y2, 'b')
xlim([0, xran])
xlabel('Seconds (s)')
ylim([-3, 3])
yticks(-3:1:3)
title('Two Sine Waves')
legend({s1, s2}, 'Location', 'southeast')
%Plot combined sine wave
subplot(2, 2, 3)
plot(x, y1 + y2, 'Color', [0, g, 0])
xlim([0, xran])
xlabel('Seconds (s)')
ylim([-3, 3])
yticks(-3:1:3)
title('Two Sine Waves Added Together')
%Zero padding
y1 = [y1 zeros(1, P)];
y2 = [y2 zeros(1, P)];
%Fourier transform of all 3 signals
Y1 = fft(y1);
Y2 = fft(y2);
Y3 = fft(y1 + y2);
Y1 = abs(Y1);
Y2 = abs(Y2);
Y3 = abs(Y3);
%Finding peaks using uppy
u1 = uppy(Y1, P, 200);
u2 = uppy(Y2, P, 200);
u3 = uppy(Y3, P, pp);
%X normalization constant
uu = (1/T)/length(Y1);
%Normalized x array for FFT
X = (0:length(Y1)-1)*uu;
%Plot fourier transform of two sine waves with peaks circled
subplot(2, 2, 2)
plot(X, Y1, 'r', X, Y2, 'b', u1(1)*uu, Y1(u1), 'om', u2(1)*uu, Y2(u2), 'om')
xlim([0, 3.5])
xlabel('Frequency (Hz)')
text(u1(1)*uu + 0.1, Y1(u1), sprintf('%1.1f Hz', u1(1)*uu))
text(u2(1)*uu + 0.1, Y2(u2), sprintf('%1.1f Hz', u2(1)*uu))
title('Fourier Transform of Two Sine Waves')
legend({s1, s2}, 'Location', 'southeast')
%Plot fourier transform of combined singal with peaks circled
subplot(2, 2, 4)
plot(X, Y3, 'Color', [0, g, 0])
xlim([0, 3.5])
xlabel('Frequency (Hz)')
%Circling peaks of FFT of combined signal
hold on
for i = 1:length(u3)
    text(u3(i)*uu + 0.1, Y3(u3(i)), sprintf('%1.1f Hz', u3(i)*uu))
    plot(u3(i)*uu, Y3(u3(i)), 'om')
end
hold off
title('Fourier Transform of Two Sine Waves Added Together')
%Function for finding peaks because findpeaks() doesn't work
%m is the function
%T2 is the zero padding length
%p is the deviation
function n = uppy(m, T2, p)
    n = [];
    for i = 1:(T2/2)
        if (m(i) > (mean(m) + p)) && (m(i) > m(i + 1)) && (m(i) > m(i - 1))
            n = [n, i];
        end
    end
end