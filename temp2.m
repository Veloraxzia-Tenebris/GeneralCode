Fs = 10000;
T_p = 1 / Fs;
t = [0:T_p:pi];
f = 440;
y = sin(t * f * 2 * pi);

shift = 100;
yShifted = y .* exp(j * 2 * pi * shift * t);
L = length(t);
NFFT = 2^nextpow2(L);
Y = fft(y, NFFT) / L;
YShifted = fft(yShifted, NFFT) / L;
f = Fs / 2 * linspace(0, 1, NFFT / 2 + 1);

figure()
subplot(2, 1, 1)
plot(f, abs(Y(1:NFFT / 2 + 1)), 'b')
title('Sinusoid (Frequency Domain)')
ylabel('|Y|')
xlim([0 600])
subplot(2, 1, 2)
plot(f, abs(YShifted(1:NFFT / 2 + 1)), 'b')
title('Shifted Sinusoid (Frequency Domain)')
xlabel('Frequency (Hz)')
ylabel('|Y Shifted|')
xlim([0 600])