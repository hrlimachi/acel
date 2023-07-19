clc
frec = 100;
time = linspace(0,(length(x)-1)/frec,length(x));
total = sqrt(x.^2+y.^2+z.^2)./10;
subplot(2, 1, 1);
plot(time, x./10, 'b', time, y./10, 'r', time, z./10, 'g');
xlabel('Tiempo');
ylabel('Amplitud');
title('Señales Individuales');
legend('X', 'Y', 'Z');
grid on;
subplot(2, 1, 2);
plot(time, total, 'm');
xlabel('Tiempo');
ylabel('Amplitud');
title('Aceleracion Total...');
legend('Atotal=sqrt(X^2+Y^2+Z^2)');
grid on;

filename = 'data5';
nombreDirectorio='3_tres pasos';
rutaArchivo = fullfile(nombreDirectorio, strcat(filename,'.png'));
saveas(gcf, rutaArchivo);
rutaArchivo = fullfile(nombreDirectorio, strcat(filename,'.mat'));
save(rutaArchivo);