% get datos x y z
clc
clear

frec = 20;

% Especificar la ruta del directorio
nombreDirectorio = '8_6p'; 

% Especificar la extensión de archivo a contar
extension = '.txt';

% Obtener la lista de archivos y carpetas dentro del directorio
listaArchivos = dir(nombreDirectorio);

% Inicializar el contador
cantidadArchivos = 0;

% Recorrer la lista de archivos
for i = 1:length(listaArchivos)
    archivoActual = listaArchivos(i);
    
    % Verificar si el archivo es de la extensión especificada
    if ~archivoActual.isdir && endsWith(archivoActual.name, extension)
        cantidadArchivos = cantidadArchivos + 1;
    end
end
% bucle que recorrera  cada archivo .txt para su procesamiento
for i=1:cantidadArchivos
    filename = sprintf('data%d', i); % 'data5';
    archivoImportar = fullfile(nombreDirectorio, strcat(filename,'.txt')); % /8_6p/data1.txt
% Importar los datos desde el archivo .txt omitiendo la primera fila
    data = importdata(archivoImportar);
    data = data.data;
% Extraer los vectores columna de los datos importados
    x = data(:, 1)./1;
    y = data(:, 2)./1;
    z = data(:, 3)./1;
   % totalAcel= data(:,4);
% Vector de tiempo
    time = linspace(0,(length(x)-1)/frec,length(x));
% generar vector de aceleracion total
    total = sqrt(x.^2+y.^2+z.^2);
% graficar señales
  %  figure(1)
    subplot(2, 1, 1);
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
  %  figure(2)
  %  plot(time,totalAcel);
% guardar imagen y variables
    rutaArchivo = fullfile(nombreDirectorio, strcat(filename,'.png'));
    saveas(gcf, rutaArchivo);
    rutaArchivo = fullfile(nombreDirectorio, strcat(filename,'.mat'));
    save(rutaArchivo);
end
