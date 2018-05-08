%borrar previos
clear;
clc;
COMM='COM6';             %declarar puerto COM
BAUDIOS=115200;          %ajustar tasa de baudios
delete(instrfind({'Port'},{COMM}));
%crear objeto serie
% s1 = serial('COM7','BaudRate',38400,'Terminator','CR/LF');
s1 = serial(COMM,'BaudRate',BAUDIOS,'Terminator','CR/LF');   %se crea el objeto serial
warning('off','MATLAB:serial:fscanf:unsuccessfulRead');
%abrir puerto
fopen(s1);               %se abre el puerto serial

% parámetros de medidas
tmax = 2; % tiempo de captura en s
% f = 80; % resultado experimental (comprobar)
f = 100; % resultado experimental (comprobar)


% inicializar
j=0;
% ejecutar bucle cronometrado
%tic
    a1 = fscanf(s1);%borra encabezados
    a2 = fscanf(s1);%borra encabezados
    a3 = fscanf(s1);%borra encabezados
    a4 = fscanf(s1);%borra encabezados
%------------------------------------------------------
 %-------crear directorio de archivos datos------------  
    Dire=datestr(now);
    ind=find(Dire==char(32));
    Dire(ind)='-';
    ind=find(Dire==char(58));
    Dire(ind)='-';
    mkdir(Dire);
%-----------------------------------------------------
tstart = tic;
while 1<2
    a=[];

i=1;
while i<tmax*f+1
   % t = toc;
    % leer del puerto serie
    %a = fscanf(s,'%d,%d')';
%     b = fscanf(s1,'%s,%s,%s,%s,%s,%s');
%     b = fscanf(s1,'%f,%f,%f,%f,%f,%f');
    b = fscanf(s1,'%f');
%     b = fscanf(s1,'%int16,%int16,%int16,%int16,%int16,%int16');
%     b = fscanf(s1);
    a=[a;b'];
    t(i)=toc(tstart);
    i = i+1;
end
% resultado del cronometro
j=j+1;
figure(1);plot(a(:,1),a(:,2));grid on;title(['Fuerza   ' int2str(j)]);ylim([-2000 10000]);drawnow;
figure(2);plot(a(:,1),a(:,3:5));grid on;title(['accel x y z  ' int2str(j)]);ylim([-20 10]);drawnow;

%----------------------------------------------------------------
%----crear directorio archivos datos-----------------------------
    file=datestr(now);
    ind=find(file==char(32));
    file(ind)='-';
    ind=find(file==char(58));
    file(ind)='-';
%     file(ind)='_';
    save([Dire '\' file],'t','a');
%     save(file,'Data','Fs','TSimple');
% file=date;
%-----------------------------------------------------------------
end
%% Limpiar puerto serie
fclose(s1);
delete(s1);
clear s1;

