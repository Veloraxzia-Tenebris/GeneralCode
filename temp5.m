figure()
fs = 2.4 * (10^9);
ts = 1 / fs;
fd = 2 * (10^9);

t = [0:(ts/1000):(ts*5)];

x1 = rectangularPulse(ts/10, 3*ts/10, t);
x2 = rectangularPulse(13*ts/10, 24*ts/10, t);
x3 = rectangularPulse(30*ts/10, 45*ts/10, t);

x = x1 + x2 + x3;

y = sin(2 * pi * t / ts);

z = fmmod(x, fs, fs*100, fd);

subplot(3, 1, 1)
plot(t, x)
title('Binary Data Stream')
subplot(3, 1, 2)
plot(t, y)
title('Carrier Signal')
subplot(3, 1, 3)
plot(t, z)
title('Modulated Signal')
xlabel('Time (s)');