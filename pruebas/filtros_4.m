clear
clc

rutaArchivo = '4_diezPasos';
filename = sprintf('data%d', 1); % 'data5';
archivoImportar = fullfile(rutaArchivo, strcat(filename,'.mat'));
load(archivoImportar);
for i=1:cantidadArchivos
    rutaArchivo = '4_diezPasos';
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
    
    % Especifica el nombre del directorio que deseas crear
    nombreDirectorioFiltro = fullfile(nombreDirectorio,filename);
    
    % Comprueba si el directorio ya existe
    if exist(nombreDirectorioFiltro, 'dir') == 7
        disp('El directorio ya existe');
    else
        % Crea el directorio
        mkdir(nombreDirectorioFiltro);
        disp('Directorio creado con éxito');
    end
    rutaArchivoFiltro=fullfile(nombreDirectorioFiltro, strcat(filename,'.png'));
    saveas(gcf, rutaArchivoFiltro);
    
    %frecCorte = 1;% 1 2 3 4 5 6
    for frecCorte=1:20
        resMul= 2*pi*frecCorte;
        numFiltro = [ resMul 0];
        denFiltro = [1 resMul];
        funTransfer = tf(numFiltro,denFiltro)
        %bode(funTransfer)
        zTransfor = c2d(funTransfer,0.02,'tustin')
        [num, den] = tfdata(zTransfor, 'v');
        yout=[0];
        yant=25;
        %xin=total(1);
        xant=25;
        
        
        for j=1:length(total)
            xin=total(j);
            yout(j)=-den(2)*yant + num(1)*xin + num(2)*xant;%0.5219*yant + 0.2391*xin + 0.2391*xant;%0.6828*yant + 0.1586*xin + 0.1586*xant;
            yant=yout(j);
            xant=xin;
        end
        
        timeAux=linspace(0,(length(yout)-1)/frec,length(yout));
        figure(2)
        plot(timeAux, yout);
        xlabel('Tiempo');
        ylabel('Amplitud');
        title('salida del filtro');
        legend('Yout');
        grid on;
        fileFrecName = sprintf('f%d', frecCorte);
        rutaArchivoFiltro=fullfile(nombreDirectorioFiltro, strcat(filename,'_',fileFrecName,'.png'));
        saveas(gcf, rutaArchivoFiltro);
        %rutaArchivoFiltro=fullfile(nombreDirectorioFiltro, strcat(filename,'_',fileFrecName,'.mat'));
        %save(rutaArchivoFiltro,'yout','total','time');
        
        youtF=[0];
        youtN1=0;
        youtN2=0;
        youtN3=0;
        youtN4=0;
        
        %xin=total(1);
        xN1=0;
        xN2=0;
        
        
        for j=1:length(yout)
            xin=yout(j);
            %yout(j)=-den(2)*yant + num(1)*xin + num(2)*xant;%0.5219*yant + 0.2391*xin + 0.2391*xant;%0.6828*yant + 0.1586*xin + 0.1586*xant;
            youtF(j)=3.546*youtN1 - 4.873*youtN2 + 3.071*youtN3 - 0.749*youtN4 + 0.01226*xN1 - 0.01451*xN2;
            youtN4=youtN3;
            youtN3=youtN2;
            youtN2=youtN1;
            youtN1=youtF(j);
            
            xN2=xN1;
            xN1=xin;
            timeAux=linspace(0,(length(youtF)-1)/frec,length(youtF));
            
        end
        figure(3)
        plot(timeAux, youtF);
        xlabel('Tiempo');
        ylabel('Amplitud');
        title('salida del filtro');
        legend('Yout');
        grid on;
        fileFrecName2 = sprintf('2f%d', frecCorte);
        rutaArchivoFiltro2=fullfile(nombreDirectorioFiltro, strcat(filename,'_',fileFrecName2,'.png'));
        saveas(gcf, rutaArchivoFiltro2);
        rutaArchivoFiltro=fullfile(nombreDirectorioFiltro, strcat(filename,'_',fileFrecName2,'.mat'));
        save(rutaArchivoFiltro,'yout','total','time');
    end
    
    
end

