% cuenta impares *final
clear
clc

rutaArchivo = '7_calle';
filename = sprintf('data%d', 1); % 'data5';
archivoImportar = fullfile(rutaArchivo, strcat(filename,'.mat'));
load(archivoImportar);
for i = 1 : cantidadArchivos
    
    disp('data'+ string(i));
    rutaArchivo = '7_calle';
    filename = sprintf('data%d', i); % 'data5';
    archivoImportar = fullfile(rutaArchivo, strcat(filename,'.mat'));
    load(archivoImportar);
    
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
     
        flag = true;
        pasos = 0;
        flagPasos = false;
        vectime = [0];
        pasosBluetooth=0;
        for j = 1:length(youtF)
            
            if youtF(j) >= 350 && flag==true
                pasos = pasos+1;
                flag = false;
                timeAux2 = linspace(0,(length(youtF)-1)/frec,length(youtF));
                vectime(pasos) = timeAux2(length(timeAux2));
                flagPasos=true;
            end
            if youtF(j) < 0 && flag==false
                disp('habilitado')
                flag=true;
            end
            if mod(pasos,2) == 1 && flagPasos
                mod(pasos,2);
                pasosBluetooth = pasosBluetooth + 1
                flagPasos = false;
            end
        
        timeAux = linspace(0, (length(youtF) - 1) / frec, length(youtF));
        
        plot(timeAux, youtF);
        xlabel('Tiempo');
        ylabel('Amplitud');
        title('salida del filtro');
        legend('YoutF');
        grid on;
        frecCorte=10;
        fileFrecName2 = sprintf('2f%d', frecCorte);
        rutaArchivoFiltro2 = fullfile(nombreDirectorioFiltro, strcat(filename, '_', fileFrecName2, '.png'));
        saveas(gcf, rutaArchivoFiltro2);
        rutaArchivoFiltro = fullfile(nombreDirectorioFiltro, strcat(filename, '_', fileFrecName2, '.mat'));
        save(rutaArchivoFiltro, 'youtF', 'time', 'vectime','pasos');
    end
    
    
end

