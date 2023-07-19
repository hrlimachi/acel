%%%  aqui se unieron los 2 filtros en un bicle for y se realiza la cuenta de
%    pasos 

clear
clc

rutaArchivo = '0_carrera';
filename = sprintf('data%d', 1); % 'data5';
archivoImportar = fullfile(rutaArchivo, strcat(filename,'.mat'));
load(archivoImportar);
for i=1:cantidadArchivos
    disp('data'+ string(i));
    rutaArchivo = '0_carrera';
    filename = sprintf('data%d', i); % 'data5';
    archivoImportar = fullfile(rutaArchivo, strcat(filename,'.mat'));
    load(archivoImportar);
    
    % Especifica el nombre del directorio que deseas crear
    nombreDirectorioFiltro = fullfile(nombreDirectorio,filename); %0_carrera/data1
    
    % Comprueba si el directorio ya existe
    if exist(nombreDirectorioFiltro, 'dir') == 7
        disp('El directorio ya existe');
    else
        % Crea el directorio
        mkdir(nombreDirectorioFiltro);
        disp('Directorio creado con éxito');
    end
    %     rutaArchivoFiltro=fullfile(nombreDirectorioFiltro, strcat(filename,'.png'));
    %     saveas(gcf, rutaArchivoFiltro);
    
    %frecCorte = 1;% 1 2 3 4 5 6
    for frecCorte=10:10
        disp('   '+string(frecCorte)+' Hz');
        resMul= 2*pi*frecCorte;
        numFiltro = [ resMul ];%0];
        denFiltro = [1 resMul];
        funTransfer = tf(numFiltro,denFiltro);
        %bode(funTransfer)
        zTransfor = c2d(funTransfer,0.02,'tustin');
        [num, den] = tfdata(zTransfor, 'v');
        total=total-236.6871;
        yout=[0];
        yant=0;%25;
        xant=0;%25;
        youtF=[0];
        xin2=0;
        xN1=0;
        xN2=0;
        xN3=0;
        flag=true;
        pasos = 0;
        vectime = [0];
        for j=1:length(total)
            xin=total(j);
            yout(j)=-den(2)*yant + num(1)*xin + num(2)*xant;%0.5219*yant + 0.2391*xin + 0.2391*xant;%0.6828*yant + 0.1586*xin + 0.1586*xant;
           % xin2=yout(j);
            %youtF(j)=(xin2+xN1+xN2+xN3)/4;%3.546*youtN1 - 4.873*youtN2 + 3.071*youtN3 - 0.749*youtN4 + 0.01226*xN1 - 0.01451*xN2;
            
            yant=yout(j);
            xant=xin;
            
           % xN3=xN2;
           % xN2=xN1;
           % xN1=xin2;
            
           % if youtF(j) >= 350 && flag==true
           %     pasos=pasos+1
           %     flag=false;
           %     timeAux2=linspace(0,(length(youtF)-1)/frec,length(youtF));
           %     vectime(pasos)=timeAux2(length(timeAux2));
            end
            if youtF(j) < 0 && flag==false
                disp('habilitado')
                flag=true;
            end
        end
        
        timeAux=linspace(0,(length(youtF)-1)/frec,length(youtF));
        figure(1)%subplot(2,1,1)
        plot(timeAux, yout);
        xlabel('Tiempo');
        ylabel('Amplitud');
        title('salida del filtro');
        legend('Yout');
        grid on;
        %         fileFrecName = sprintf('f%d', frecCorte);
        %         rutaArchivoFiltro=fullfile(nombreDirectorioFiltro, strcat(filename,'_',fileFrecName,'.png'));
        %saveas(gcf, rutaArchivoFiltro);
        %subplot(2,1,2)
        figure(2)
        plot(timeAux, youtF);%F);
        xlabel('Tiempo');
        ylabel('Amplitud');
        title('salida del filtro');
        legend('YoutF');
        grid on;
        fileFrecName2 = sprintf('2f%d', frecCorte);
        rutaArchivoFiltro2=fullfile(nombreDirectorioFiltro, strcat(filename,'_',fileFrecName2,'.png'));
        saveas(gcf, rutaArchivoFiltro2);
        rutaArchivoFiltro=fullfile(nombreDirectorioFiltro, strcat(filename,'_',fileFrecName2,'.mat'));
        save(rutaArchivoFiltro,'yout','youtF','total','time','vectime');
    end
    
    
end
