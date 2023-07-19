clear
clc

rutaArchivo = '4_diezPasos';
i=2;
filename = sprintf('data%d', i); % 'data5';
archivoImportar = fullfile(rutaArchivo, strcat(filename,'.mat'));
load(archivoImportar);

figure(1)
subplot(2,1,1)
plot(time, x, 'b', time, y, 'r', time, z, 'g');
xlabel('Tiempo');
ylabel('Amplitud');
title(filename);
legend('X', 'Y', 'Z');
grid on;
subplot(2, 1, 2);
plot(time, total, 'm');
xlabel('Tiempo');
ylabel('Amplitud');
title('Aceleracion Total...');
legend('Atotal=sqrt(X^2+Y^2+Z^2)');
grid on;

frecCorte = 15;
resMul= 2*pi*frecCorte;
numFiltro = [ resMul];
denFiltro = [1 resMul];
funTransfer = tf(numFiltro,denFiltro)
%bode(funTransfer)
zTransfor = c2d(funTransfer,0.02,'tustin')
[num, den] = tfdata(zTransfor, 'v');
yout=[0];
yant=25;
%xin=total(1);
xant=25;


for i=1:length(total)
    xin=total(i);
    yout(i)=-den(2)*yant + num(1)*xin + num(2)*xant;%0.5219*yant + 0.2391*xin + 0.2391*xant;%0.6828*yant + 0.1586*xin + 0.1586*xant;
    yant=yout(i);
    xant=xin;
    timeAux=linspace(0,(length(yout)-1)/frec,length(yout));
    figure(2)
    plot(timeAux, yout);
    xlabel('Tiempo');
    ylabel('Amplitud');
    title('salida del filtro');
    legend('Yout');
    grid on;
end

