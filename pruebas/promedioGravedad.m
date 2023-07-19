% promedio gravedad 236.6871

clear
clc

rutaArchivo = '0_gravedad';
filename = sprintf('data%d', 2); % 'data5';
archivoImportar = fullfile(rutaArchivo, strcat(filename,'.mat'));
load(archivoImportar);
promProm=[0];
 for i=1:cantidadArchivos
     disp('data'+ string(i));
     rutaArchivo = '0_gravedad';
     filename = sprintf('data%d', i); % 'data5';
     archivoImportar = fullfile(rutaArchivo, strcat(filename,'.mat'));
     load(archivoImportar);
     disp(mean(total));
     promProm(i)=mean(total);
 end
 mean(promProm)