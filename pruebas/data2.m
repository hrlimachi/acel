% clc
% frec = 100;
% time = linspace(0,(length(X)-1)/frec,length(X));
% plot(time,X,'b')
% hold on;
% plot(time,Y,'r')
% plot(time,Z,'g')

% filename = 'data5';
% nombreDirectorio='3_tres pasos';
% rutaArchivo = fullfile(nombreDirectorio, strcat(filename,'.txt'));
% % Importar los datos desde el archivo .txt omitiendo la primera fila
% data = importdata(rutaArchivo);
% data = data.data;
% 
% % Extraer los vectores columna de los datos importados
% x = data(:, 1);
% y = data(:, 2);
% z = data(:, 3);

% % Definir el número variable
% numero = 42;
% 
% % Utilizando sprintf
% str = sprintf('El número es: %d', numero);
% Especificar la ruta del directorio
directorio = '3_tres pasos';

% % Obtener la lista de archivos y carpetas dentro del directorio
% listaArchivos = dir(directorio);
% 
% % Filtrar solo los archivos (excluyendo carpetas y directorios especiales)
% archivos = listaArchivos(~[listaArchivos.isdir]);
% 
% % Contar la cantidad de archivos
% cantidadArchivos = numel(archivos);
% 
% % Mostrar el resultado
% disp(['La cantidad de archivos en el directorio es: ', num2str(cantidadArchivos)]);

% Especificar la ruta del directorio
directorio = '3_tres pasos';

% Especificar la extensión de archivo a contar
extension = '.txt';

% Obtener la lista de archivos y carpetas dentro del directorio
listaArchivos = dir(directorio);

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

% Mostrar el resultado
disp(['La cantidad de archivos ', extension, ' en el directorio es: ', num2str(cantidadArchivos)]);













