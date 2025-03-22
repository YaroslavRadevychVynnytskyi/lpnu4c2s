clear
clc
close();

//параметри сигналів
A1=-3; A2=6; A3=15; A4=-0.12;
w1=6; w2=1/5; w3=3; w4=8;
phi1=%pi/5; phi2=%pi/6; phi3=0; phi4=%pi/7;

M= 2^4;
koef=2^3;

//розрахунок граничних частот
w_gr = max([w1, w2, w4, w3]);
f_gr = w_gr / (2 * %pi);
dt = 1 / (2 * f_gr * koef);

T=10 * %pi;
t = 0 : dt : T - dt;

//формування сигналу
x=A1*cos(w1*t+phi1)-A2*sin(w2*t+phi2)+A3*sin(w3*t+phi3)-A4*cos(w4*t+phi4);

//максимальне та мінімальне значення амплітуди
maxA=max(abs(x));
minA=-maxA

//розрахунок квантування
N = length(x);
k = (maxA - minA) / (M - 1);
K = minA : k : maxA;
y = floor(x / k) * k;
if modulo(M, 2) == 0 then
    y = y + k / 2;
end

//відображення рівнів квантування
KK = ones(N, 1) * K;
xlabel('Час, с'); 
ylabel('Рівні квантування');

//графіки
plot2d(t,x,3)
plot2d2(t,y,5)

legend('Дискретний сигнал','Квантований сигнал');
plot(t, KK, 'k--');

//абсолютна похибка
a=max(abs(y-x))
disp("Абсолютна похибка (a)=", a)

//середня похибка
b=(1/N)*(sum(y)-sum(x))
disp("Середня похибка (b)=", b)

//дисперсія
d=(1/N)*sum((y-x).^2)
disp("Дисперсія (d)=", d)

