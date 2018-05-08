 clear all;
%   close all;
 clc;
%  concatena_archivos(m); %concatena m archivos 
% open the file
% [filename, pathname] = uigetfile('*.*');
pathname = uigetdir('seleccione directorio');
% filename=[pathname filename]; % 'casa-u.TXT';
% fid = fopen(filename);

dire = dir([pathname '\' '*.mat']); %carga el directorio
nArch=round(length(dire)/1);

display('Concatena.m ... inicio carga archivos  ');
tic
j=0;
dati=[];
ti=[];

for i=1:nArch,    
   if length(dire(i).name) >16,
    datos = load([pathname '\'  dire(i).name]);
    if size(datos.a)~=[0,0]
        nchan=size(datos.a,2);
        if i==1,
            dati=datos.a;
        elseif (i>1 && (size(dati,2) == size(datos.a,2))),
            dati=[dati;datos.a];
        end
    end
    j=j+1;
    if (i ~= j)
     display([i j]);
    end
   end
end
display('fin carga datos');toc;
%  Fs=10.;
%  Fs=length(dati)/dati(end,1);
 Fs= 1/mean(diff(dati(:,1)));

t=dati(:,1);    %(0:1:length(dati)-1)/Fs;
y=find(pathname =='\');
% dat=dati(:,4);
% ind=find(diff( dat)>0.020);
% dat(ind+1)=dat(ind);
% dat1=dat;
%  ind1=find(diff( dat1 ) < -0.020);
% dat1(ind1+1)=dat1(ind1);
%  ind1=find(diff( dat1 ) < -0.020);
% dat1(ind1+1)=dat1(ind1);
figure;plot(dati(:,1),dati(:,2)/1000);grid on;title(['Fuerza en kp vs tiempo en s. Fsample  ', num2str(Fs,'%5.2f')]); 
figure;plot(dati(:,1),dati(:,3:5));grid on;title(['Aceleracion en m/s2 vs tiempo en s. Fsample  ', num2str(Fs,'%5.2f')]); 
