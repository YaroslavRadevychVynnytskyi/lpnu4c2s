clc;
clear;
close(); 

T = 15; // період сигналу
m = 8; 
N = 2^m; // кількість точок (N)
p = N / 4;           // параметр фільтрації
k1 = N / 2 - p;      // перший край фільтрації
k2 = N / 2 + p;      // другий край фільтрації
dt = T / N;          // крок дискретизації

//єдиний вектор часу
t1 = 0:dt:5-dt;
t2 = 5:dt:15;
t = [t1 t2];
disp("Розмірність t = " + string(length(t)));

//вектор сигналу
x1 = 36 + 0 * t1;
x2 = 1.3 * t2 - 19.5;
x = [x1 x2];
disp("Розмірність x = " + string(length(x)));

//вектор частот
w = 1:1:N;
disp("Розмірність w = " + string(length(w)));


//обрахунок спектральних коефіцієнтів
Sx = fft(x)/(N);
disp("Розмірність Sx = " + string(length(Sx)));

//візуалізація
figure(1,'BackgroundColor',[1,1,1])
subplot(3,1,1), 
h1 = plot(t, x, 'r', 'LineWidth', 2);
xtitle('Вхідний сигнал - x(n)')
h = gca()
xgrid();
set(h, "data_bounds", [t(1),-14; t($), 37]);

// другий підграфік: дійсна частина спектра
subplot(3,1,2),
h2 = plot(0:(N-1), real(Sx), 'b', 'LineWidth', 2);
xgrid();
title('Дійсна частина ШПФ', 'position', [N/2, max(real(Sx)) + 1]);

// третій підграфік: уявна частина спектра
subplot(3,1,3), 
h3 = plot(0:(N-1), imag(Sx), 'm', 'LineWidth', 2);
xgrid(); 
title('Уявна частина ШПФ', 'position', [N/2, max(imag(Sx)) + 0.5])

//модифіковані спектри
Sx1 = [Sx(1:k1) zeros(1,k2-k1) Sx(k2+1:N)];
Sx2 = [zeros(1,p) Sx(p+1:N-p) zeros(1,p)];
Sx3 = [Sx(1:N/4-p/2) zeros(1,p) Sx((N/4+p/2)+1:3*N/4-p/2) zeros(1,p) Sx(3*N/4+p/2+1:N)];
Sx4 = [zeros(1,N/4-p/2) Sx((N/4-p/2)+1:N/4+p/2) zeros(1,N/2-p) Sx(3*N/4-p/2+1:3*N/4+p/2) zeros(1,N/4-p/2)];

//візуалізація амплітудних спектрів
figure(2,'BackgroundColor',[1,1,1]);
set(gcf(), "position", [100, 100, 800, 600]);

// перший підграфік: амплітудний спектр
subplot(5,2,1), 
plot(w, abs(Sx)), 
xgrid();
xlabel(' '); // додати простір для заголовка
title('Амплітудний спектр X(k)', 'position', [N/4, max(abs(Sx))]);

// другий підграфік: модифікований амплітудний графік Xm1(k)
subplot(5,2,3), 
plot(w, abs(Sx1)), 
xgrid();
xlabel(' '); 
title('Модифікований амплітудний спектр Xm1(k)', 'position', [N/20, max(abs(Sx1))]);

// третій підграфік: модифікований амплітудний графік Xm2(k)
subplot(5,2,5), 
plot(w, abs(Sx2)),
xgrid(); 
xlabel(' '); // Додати простір для заголовка
title('Модифікований амплітудний спектр Xm2(k)', 'position', [N/20, max(abs(Sx2)) * 1.1]);

// четвертий підграфік: модифікований амплітудний графік Xm3(k)
subplot(5,2,7), 
plot(w, abs(Sx3)),
xgrid();
xlabel(' ');
title('Модифікований амплітудний спектр Xm3(k)', 'position', [N/20, max(abs(Sx3)) * 1.1]);

// п'ятий підграфік: модифікований амплітудний графік Xm4(k)
subplot(5,2,9), 
plot(w, abs(Sx4)),
xgrid(); 
xlabel(' ');
title('Модифікований амплітудний спектр Xm4(k)', 'position', [N/20, max(abs(Sx4)) * 1.1]);

//відновлення сигналів з модифікованих спектрів
x1 = N*ifft(Sx);
xm1 = N*ifft(Sx1);
xm2 = N*ifft(Sx2);
xm3 = N*ifft(Sx3);
xm4 = N*ifft(Sx4);

//візуалізація відновлених сигналів
subplot(5,2,2), 
plot(t, real(x1), 'r'); 

xgrid();
xlabel(' ');
title('Відновлений сигнал x1(n)','position',[T/4,max(abs(x1))]);

subplot(5,2,4), 
plot(t, real(xm1), 'r');

xgrid(); 
xlabel(' ');
title('Відновлений сигнал xm1(n)','position',[T/4,max(abs(xm1))]);

subplot(5,2,6), 
plot(t, real(xm2), 'r');
xgrid(); 
xlabel(' ');
title('Відновлений сигнал xm2(n)','position',[T/4,max(abs(xm2))]);

subplot(5,2,8), 
plot(t, real(xm3), 'r');
xgrid(); 
xlabel(' ');
title('Відновлений сигнал xm3(n)','position',[T/4,max(abs(xm3))]);

subplot(5,2,10), 
plot(t, real(xm4), 'r');
xgrid();
xlabel(' '); 
title('Відновлений сигнал xm4(n)','position',[T/4,max(abs(xm4))]);

//розрахунок похибок
onePr = 100/(N*max(abs(36),abs(-13)));
bm1 = onePr*(sum(abs(x-xm1)))
bm2 = onePr*(sum(abs(x-xm2)))
bm3 = onePr*(sum(abs(x-xm3)))
bm4 = onePr*(sum(abs(x-xm4)))

//виведення результатів похибок
disp('Кількість точок N=', N);
disp('Параметр фільрації p=', p);
bm(1)=bm1; bm(2)=bm2; bm(3)=bm3; bm(4)=bm4;
disp("Масив похибок bm",bm)

//розрахунок енергій сигналів
E_time = sum(abs(x).^2)/ N;   // енергія в часі для вхідного сигналу
E_spektr = sum(abs(Sx).^2);  // енергія в спектрі для вхідного сигналу


E_time1 = sum(abs(xm1).^2)/N; E_spektr1 = sum(abs(Sx1).^2);
E_time2 = sum(abs(xm2).^2)/N; E_spektr2 = sum(abs(Sx2).^2);
E_time3 = sum(abs(xm3).^2)/N; E_spektr3 = sum(abs(Sx3).^2);
E_time4 = sum(abs(xm4).^2)/N; E_spektr4 = sum(abs(Sx4).^2);

//збереження енергій у масиви
E_t(1)=E_time; 
E_t(2)=E_time1;
E_t(3)=E_time2; 
E_t(4)=E_time3;
E_t(5)=E_time4;

E_s(1)=E_spektr; 
E_s(2)=E_spektr1; 
E_s(3)=E_spektr2;
E_s(4)=E_spektr3; 
E_s(5)=E_spektr4;

E = [E_t, E_s];    // об'єднання енергій в один масив
disp("E=", E');    // виведення енергій
