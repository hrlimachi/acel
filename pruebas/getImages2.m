% get datos youtF
clc
clear

frec = 20;

% Especificar la ruta del directorio
nombreDirectorio = '0_carrera'; 

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
    archivoImportar = fullfile(nombreDirectorio, strcat(filename,'.txt'));
% Importar los datos desde el archivo .txt omitiendo la primera fila
    data = importdata(archivoImportar);
    data = data.data;
% Extraer los vectores columna de los datos importados
    youtF = data(:, 1);

% Vector de tiempo
    time = linspace(0,(length(youtF)-1)/frec,length(youtF));
% graficar señales
    plot(time, youtF);
    xlabel('Tiempo');
    ylabel('Amplitud');
    title(filename);
    legend('youtF');
    grid on;
% guardar imagen y variables
    rutaArchivo = fullfile(nombreDirectorio, strcat(filename,'.png'));
    saveas(gcf, rutaArchivo);
    rutaArchivo = fullfile(nombreDirectorio, strcat(filename,'.mat'));
    save(rutaArchivo);
end
