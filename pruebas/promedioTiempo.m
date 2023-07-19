%usar despues de filtros_pru4
clc
clear
i=1;
rutaArchivo = '4_diezPasos';
frecCorte = 10;
filename = sprintf('data%d', i); % 'data5';
fileFrecName2 = sprintf('2f%d', frecCorte);
nombreDirectorioFiltro = fullfile(rutaArchivo,filename); %4_diezPasos\data1
archivoImportar =fullfile(nombreDirectorioFiltro, strcat(filename,'_',fileFrecName2,'.mat')); %4_diezPasos\data1\data1_2f10.mat
load(archivoImportar);
promTime = [0];
for j=1:length(vectime)-12
    promTime(j)=vectime(2*j+1)-vectime(j*2-1)
    vectime
    promTime
end
1:2:length(vectime)-2
promTime' %0.45