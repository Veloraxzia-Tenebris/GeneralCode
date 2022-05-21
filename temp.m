FsOrig = 2500;
T_p = 1 / FsOrig;
tOrig = [0:T_p:pi];

Aorig = sin(tOrig * 440 * 2 * pi);
Eorig = sin(tOrig * 660 * 2 * pi);

y = Aorig + Eorig;
L = length(y);
NFFTorig = 2^nextpow2(L);
Y = fft(y, NFFTorig) / L;
fOrig = FsOrig / 2 * linspace(0, 1, NFFTorig / 2 + 1);

n = 60;
Wn = 0.5;
b = fir1(n, Wn);
[H, f] = freqz(b, 1, 512, FsOrig);

z = filter(b , 1, y);
zDown = z(1:2:end);
FsDown = FsOrig / 2;
L = length(zDown);
NFFTdown = 2^nextpow2(L);
Zdown = fft(zDown, NFFTdown) / L;
fDown = FsDown / 2 * linspace(0, 1, NFFTdown / 2 + 1);

figure()
plot(fOrig, abs(Y(1:(NFFTorig / 2 + 1))), 'g')
title('Anti-aliasing Filtered Spectrum')
xlabel('Frequency (Hz)')
ylabel('|Y(f)|')
hold on
plot(fDown, abs(Zdown(1:(NFFTdown / 2 + 1))), 'r--')
plot(f, abs(H) / max(abs(H)), 'b')
hold off
legend('Original Signal', 'Filtered Signal', 'Anti-Aliasing')