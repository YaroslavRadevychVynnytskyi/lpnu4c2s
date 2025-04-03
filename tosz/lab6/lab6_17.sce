clear; 
clc; 
close(winsid());

rgb_Img = imread('/Users/root/Desktop/Ferrari_488_GTB.jpg');
G_Img = rgb2gray(rgb_Img);
B_Img = im2bw(G_Img, 0.5);

// Отримання розмірів
[height, width] = size(rgb_Img(:,:,1));


//----------------перше вікно - оригінальне, сіре та бінарне зображення------------------------
f1 = scf(1);
f1.figure_name = "Main type of photo";
f1.figure_size = [1000, 400];
f1.background = color("white");
clf(f1);

// оригінальне RGB зображення
subplot(1,3,1);
imshow(rgb_Img);
xtitle('RGB Image');
a = gca();
a.tight_limits = "on";
a.isoview = "on";
a.margins = [0.125 0.125 0.125 0.125];

// сіре зображення
subplot(1,3,2);
imshow(G_Img);
xtitle('Grayscale Image');
a = gca();
a.tight_limits = "on";
a.isoview = "on";
a.margins = [0.125 0.125 0.125 0.125];

// бінарне зображення
subplot(1,3,3);
imshow(B_Img);
xtitle('Binary Image');
a = gca();
a.tight_limits = "on";
a.isoview = "on";
a.margins = [0.125 0.125 0.125 0.125];

//---------------------друге вікно - обробка сірого зображення-------------------------
f2 = scf(2);
f2.figure_name = "Grayscale image processing";
f2.figure_size = [1000, 600];
f2.background = color("white");
clf(f2);

// перетворюємо зображення у вектор для гістограми
G_Img_vector = double(matrix(G_Img,1,-1));

// оригінальне сіре зображення
subplot(2,3,1);
imshow(G_Img);
xtitle('Original Grayscale');
a = gca();
a.tight_limits = "on";
a.isoview = "on";
a.margins = [0.125 0.125 0.125 0.125];

// гістограма оригінального зображення
subplot(2,3,4);
histplot(256, G_Img_vector);
xtitle('Original Histogram');
xlabel('Intensity');
ylabel('Pixel Count');

// еквалізоване зображення
eq_img = imhistequal(G_Img);
eq_img_vector = double(matrix(eq_img,1,-1));
subplot(2,3,2);
imshow(eq_img);
xtitle('Equalized Image');
a = gca();
a.tight_limits = "on";
a.isoview = "on";
a.margins = [0.125 0.125 0.125 0.125];

// гістограма після еквалізації
subplot(2,3,5);
histplot(256, eq_img_vector);
xtitle('Equalized Histogram');
xlabel('Intensity');
ylabel('Pixel Count');

// кореговане зображення 
alpha = 1.3;              // коефіцієнт контрасту
beta = 30;                // зсув яскравості
adjusted_img = G_Img * alpha + beta;
adjusted_img(adjusted_img > 255) = 255;
adjusted_img(adjusted_img < 0) = 0;
adjusted_img_vector = double(matrix(adjusted_img,1,-1));
subplot(2,3,3);
imshow(adjusted_img);
xtitle(['Adjusted Image (α=', string(alpha), ', β=', string(beta), ')']);
a = gca();
a.tight_limits = "on";
a.isoview = "on";
a.margins = [0.125 0.125 0.125 0.125];

// гістограма після корекції
subplot(2,3,6);
histplot(256, adjusted_img_vector);
xtitle('Adjusted Histogram');
xlabel('Intensity');
ylabel('Pixel Count');

show_window(f1);
show_window(f2);


//-----------------------третє вікно - обробка з шумами-----------------------------
f3 = scf(3);
f3.figure_name = "Noise Analysis";
f3.figure_size = [1000, 600];
f3.background = color("white");
clf(f3);

// додаємо різні типи шумів
gaussian_noise = imnoise(G_Img, 'gaussian');
sp_noise = imnoise(G_Img, 'salt & pepper');
speckle_noise = imnoise(G_Img, 'speckle');
filtered_sp = immedian(sp_noise, 3);

// гаусівський шум
subplot(2,3,1);
imshow(gaussian_noise);
xtitle('Gaussian Noise');
a = gca();
a.tight_limits = "on";
a.isoview = "on";
a.margins = [0.125 0.125 0.125 0.125];

// гістограма зображення з гаусівським шумом
subplot(2,3,4);
histplot(256, double(matrix(gaussian_noise,1,-1)));
xtitle('Gaussian Histogram');
xlabel('Intensity');
ylabel('Pixel Count');

// Salt & Pepper (імпульсний шум)
subplot(2,3,2);
imshow(sp_noise);
xtitle('Salt & Pepper');
a = gca();
a.tight_limits = "on";
a.isoview = "on";
a.margins = [0.125 0.125 0.125 0.125];

// Salt & Pepper - гістограма
subplot(2,3,5);
histplot(256, double(matrix(sp_noise,1,-1)));
xtitle('S&P Histogram');
xlabel('Intensity');
ylabel('Pixel Count');

// мультиплікативний шум
subplot(2,3,3);
imshow(speckle_noise);
xtitle('Speckle Noise');
a = gca();
a.tight_limits = "on";
a.isoview = "on";
a.margins = [0.125 0.125 0.125 0.125];

// гістограма мультиплікативного шуму
subplot(2,3,6);
histplot(256, double(matrix(speckle_noise,1,-1)));
xtitle('Speckle Histogram');
xlabel('Intensity');
ylabel('Pixel Count');

show_window(f3);

//----------------------четверте вікно: зображення з шумом + медіанний фільтр-----------------------
f4 = scf(4);
f4.figure_name = "Original Noises + Median Filter";
f4.figure_size = [1000, 600];
f4.background = color("white");
clf(f4);

// оригінальні зображення
subplot(2,3,1);
imshow(gaussian_noise);
xtitle('Gaussian Noise');
a = gca(); a.tight_limits = "on"; a.isoview = "on";

subplot(2,3,2);
imshow(sp_noise);
xtitle('Salt & Pepper Noise');
a = gca(); a.tight_limits = "on"; a.isoview = "on";

subplot(2,3,3);
imshow(speckle_noise);
xtitle('Speckle Noise');
a = gca(); a.tight_limits = "on"; a.isoview = "on";

// медіанний фільтр
subplot(2,3,4);
median_gaussian = immedian(gaussian_noise, 3);
imshow(median_gaussian);
xtitle('Median filter (Gaussian)');
a = gca(); a.tight_limits = "on"; a.isoview = "on";

subplot(2,3,5);
median_sp = immedian(sp_noise, 3);
imshow(median_sp);
xtitle('Median filter (S&P)');
a = gca(); a.tight_limits = "on"; a.isoview = "on";

subplot(2,3,6);
median_speckle = immedian(speckle_noise, 3);
imshow(median_speckle);
xtitle('Median filter (Speckle)');
a = gca(); a.tight_limits = "on"; a.isoview = "on";

//---------------------------п'яте вікно - фільтр усереднення-----------------------------
f5 = scf(5);
f5.figure_name = "Average Filter Results";
f5.figure_size = [1000, 600];
f5.background = color("white");
clf(f5);

// створення маски фільтра
h_avg = ones(3,3)/9;

subplot(2,3,1);
imshow(gaussian_noise);
xtitle('Gaussian Noise');
a = gca(); a.tight_limits = "on"; a.isoview = "on";

subplot(2,3,2);
imshow(sp_noise);
xtitle('S&P Noise');
a = gca(); a.tight_limits = "on"; a.isoview = "on";

subplot(2,3,3);
imshow(speckle_noise);
xtitle('Speckle Noise');
a = gca(); a.tight_limits = "on"; a.isoview = "on";

subplot(2,3,4);
avg_gaussian = uint8(conv2(double(gaussian_noise), h_avg, 'same'));
imshow(avg_gaussian);
xtitle('Average filter (Gaussian)');
a = gca(); a.tight_limits = "on"; a.isoview = "on";

subplot(2,3,5);
avg_sp = uint8(conv2(double(sp_noise), h_avg, 'same'));
imshow(avg_sp);
xtitle('Average filter (S&P)');
a = gca(); a.tight_limits = "on"; a.isoview = "on";

subplot(2,3,6);
avg_speckle = uint8(conv2(double(speckle_noise), h_avg, 'same'));
imshow(avg_speckle);
xtitle('Average filter (Speckle)');
a = gca(); a.tight_limits = "on"; a.isoview = "on";

//------------------------шосте вікно - гаусівський фільтр-------------------------
f6 = scf(6);
f6.figure_name = "Gaussian Filter Results";
f6.figure_size = [1000, 600];
f6.background = color("white");
clf(f6);

// Create Gaussian mask
h_gauss = [1 2 1; 2 4 2; 1 2 1]/16;

subplot(2,3,1);
imshow(gaussian_noise);
xtitle('Gaussian Noise');
a = gca(); a.tight_limits = "on"; a.isoview = "on";

subplot(2,3,2);
imshow(sp_noise);
xtitle('S&P Noise');
a = gca(); a.tight_limits = "on"; a.isoview = "on";

subplot(2,3,3);
imshow(speckle_noise);
xtitle('Speckle Noise');
a = gca(); a.tight_limits = "on"; a.isoview = "on";

subplot(2,3,4);
gauss_gaussian = uint8(conv2(double(gaussian_noise), h_gauss, 'same'));
imshow(gauss_gaussian);
xtitle('Gaussian filter (Gaussian)');
a = gca(); a.tight_limits = "on"; a.isoview = "on";

subplot(2,3,5);
gauss_sp = uint8(conv2(double(sp_noise), h_gauss, 'same'));
imshow(gauss_sp);
xtitle('Gaussian filter (S&P)');
a = gca(); a.tight_limits = "on"; a.isoview = "on";

subplot(2,3,6);
gauss_speckle = uint8(conv2(double(speckle_noise), h_gauss, 'same'));
imshow(gauss_speckle);
xtitle('Gaussian filter (Speckle)');
a = gca(); a.tight_limits = "on"; a.isoview = "on";

show_window(f4);
show_window(f5);
show_window(f6);
